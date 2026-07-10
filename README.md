# esp32-gps

Akku-betriebenes GNSS-Empfänger-Board auf Basis des **ESP32**. Ein GNSS-Modul (GPS/BDS/GLONASS)
liefert die Positionsdaten, der ESP32 liest sie über UART aus und stellt sie per **Bluetooth**
für andere Geräte (z. B. Smartphone, Laptop, Navigationssoftware) bereit.

> Aktueller Stand: vollständiges KiCad-Hardwaredesign (Schaltplan + Platinenlayout). Die
> ESP32-Firmware (ESP-IDF) liest das GNSS-Modul per UART aus und gibt die NMEA-Sätze aktuell
> im Log aus; die Weiterleitung per Bluetooth folgt als nächster Schritt.

## Features

- **ESP32-PICO-V3** als zentrale MCU (WLAN + Bluetooth Classic/BLE integriert)
- **Ai-Thinker GP-01** GNSS-Modul (GPS/BDS/GLONASS) mit externer Antenne (Koax-Anschluss)
- **USB-C** für Programmierung (über integrierten CH340C USB-UART-Wandler) und zum Laden
- **Li-Ion-Akkubetrieb** (18650) mit Lade-IC TP4056, Akkuschutz (DW01A) und automatischer
  Umschaltung zwischen USB- und Akkuversorgung (LTC4412 Ideal-Diode-Power-Path)
- 3,3-V-Logikversorgung über AP2112K-3.3-LDO, ESD-Schutz am USB-Eingang

## Hardware

| Schaltplan | Inhalt |
|---|---|
| `kicad/esp32-gps.kicad_sch` | ESP32-PICO-V3, GNSS-Modul GP-01, USB-UART (CH340C), Antennenanschluss |
| `kicad/supply.kicad_sch` | Akku, Ladeschaltung, Power-Path, 3,3-V-Regler |
| `kicad/esp32-gps.kicad_pcb` | Platinenlayout |

Erstellt mit KiCad 9. Verwendete Zusatzbibliothek: [`yvolodym/kicad-libraries`](https://github.com/yvolodym).

## Firmware

ESP-IDF-Projekt (Framework-Version 6.0.2), Ziel-Chip `esp32`. Initialisiert UART2 auf den
Pins, die im Schaltplan als `GPS_TX`/`GPS_RX` verdrahtet sind (IO25/IO26), liest die NMEA-Sätze
des GP-01 zeilenweise ein und gibt sie per `ESP_LOGI` aus.

```
main/
  main.c          UART-Init + Log-Ausgabe der NMEA-Sätze
  CMakeLists.txt
CMakeLists.txt     Projekt-Root (ESP-IDF)
sdkconfig.defaults
```

Bauen/Flashen:

```sh
. $IDF_PATH/export.sh
idf.py set-target esp32
idf.py build
idf.py -p /dev/ttyUSB0 flash monitor
```

## Repo-Struktur

```
kicad/
  esp32-gps.kicad_pro   Projektdatei
  esp32-gps.kicad_sch   Hauptschaltplan
  supply.kicad_sch      Stromversorgung/Ladeschaltung
  esp32-gps.kicad_pcb   Platinenlayout
main/                   ESP-IDF-Firmware (GNSS-UART, aktuell Log-Ausgabe)
```

## Status / Roadmap

- [x] Schaltplan (MCU, GNSS, USB, Stromversorgung)
- [x] Platinenlayout
- [x] Firmware: GNSS-UART auslesen, NMEA-Sätze im Log ausgeben
- [ ] Bestückungsliste (BOM) / Fertigungsvorbereitung
- [ ] Firmware: NMEA-Daten per Bluetooth (SPP/BLE) bereitstellen
- [ ] Gehäuse

## Mitwirken

Projektsprache ist Deutsch – Commits, Issues und Doku bitte auf Deutsch verfassen.

Weitere Hinweise für die Arbeit mit Claude Code an diesem Projekt siehe [`CLAUDE.md`](./CLAUDE.md).

## Lizenz

Dieses Projekt steht unter der [CERN Open Hardware Licence Version 2 - Strongly Reciprocal
(CERN-OHL-S-2.0)](./LICENSE), einer verbreiteten Copyleft-Lizenz für offene Hardwareprojekte.
