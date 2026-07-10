#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_log.h"

// UART-Verbindung zum GNSS-Modul (Ai-Thinker GP-01, UART0/TX0-RX0).
// Siehe kicad/esp32-gps.kicad_sch: Netze GPS_TX / GPS_RX.
#define GPS_UART_PORT      UART_NUM_2
#define GPS_UART_RX_PIN    25  // ESP32 IO25 <- GP-01 TX0 (Netz GPS_TX)
#define GPS_UART_TX_PIN    26  // ESP32 IO26 -> GP-01 RX0 (Netz GPS_RX)
#define GPS_UART_BAUD_RATE 9600
#define GPS_UART_RX_BUF_SIZE 1024

static const char *TAG = "gps";

static void gps_uart_init(void)
{
    const uart_config_t uart_config = {
        .baud_rate = GPS_UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    ESP_ERROR_CHECK(uart_driver_install(GPS_UART_PORT, GPS_UART_RX_BUF_SIZE, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(GPS_UART_PORT, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(GPS_UART_PORT, GPS_UART_TX_PIN, GPS_UART_RX_PIN,
                                  UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
}

// Liest Bytes vom GNSS-UART, sammelt sie zeilenweise (NMEA-Sätze enden mit \r\n)
// und gibt jede vollständige Zeile per ESP_LOGI aus.
static void gps_uart_task(void *arg)
{
    uint8_t byte;
    char line[128];
    size_t line_len = 0;

    while (1) {
        int read = uart_read_bytes(GPS_UART_PORT, &byte, 1, pdMS_TO_TICKS(1000));
        if (read <= 0) {
            continue;
        }

        if (byte == '\n') {
            if (line_len > 0 && line[line_len - 1] == '\r') {
                line_len--;
            }
            line[line_len] = '\0';
            if (line_len > 0) {
                ESP_LOGI(TAG, "%s", line);
            }
            line_len = 0;
            continue;
        }

        if (line_len < sizeof(line) - 1) {
            line[line_len++] = (char)byte;
        } else {
            // Zeile zu lang (kein gueltiger NMEA-Satz) - verwerfen und neu beginnen.
            line_len = 0;
        }
    }
}

void app_main(void)
{
    gps_uart_init();
    ESP_LOGI(TAG, "GPS-UART auf UART%d initialisiert (RX=IO%d, TX=IO%d, %d Baud)",
             GPS_UART_PORT, GPS_UART_RX_PIN, GPS_UART_TX_PIN, GPS_UART_BAUD_RATE);

    xTaskCreate(gps_uart_task, "gps_uart_task", 4096, NULL, 10, NULL);
}
