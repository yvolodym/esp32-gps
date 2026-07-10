# CLAUDE.md

Diese Datei gibt Claude Code (claude.ai/code) Kontext für die Arbeit in diesem Repository.

## Projektüberblick

`esp32-gps` ist ein Hardwareprojekt (KiCad) für ein Akku-betriebenes GNSS-Empfänger-Board auf Basis
des ESP32. Die vom GNSS-Modul gelieferten Positionsdaten sollen über Bluetooth des ESP32 an ein
Endgerät (z. B. Smartphone/Laptop, Navigations-App) ausgelesen werden.

Aktueller Stand: Es existiert das vollständige KiCad-Hardwaredesign (Schaltplan + Layout). Firmware
für den ESP32 (Auslesen des GNSS-Moduls per UART, Weiterleitung der NMEA-Daten via Bluetooth SPP)
ist noch **nicht** Teil dieses Repos.

Projektsprache: Deutsch (Commits, Doku, Kommentare in Schaltplänen).

## Hardware-Architektur

Das Design besteht aus zwei Schaltplanblättern:

- `kicad/esp32-gps.kicad_sch` – Hauptplatine
  - **ESP32-PICO-V3** (Espressif SiP): MCU mit integriertem WLAN + Bluetooth Classic/BLE.
    Übernimmt Auslesen des GNSS-Moduls und die Bluetooth-Kommunikation.
  - **Ai-Thinker GP-01**: GNSS-Modul (GPS/BDS/GLONASS), SMD mit Castellated Pads, Anbindung
    über UART.
  - **CH340C**: USB-UART-Brücke für Programmierung/Debugging des ESP32 über USB.
  - Auto-Programming-Schaltung (BCW66G-Transistoren) für automatisches Reset/Boot über DTR/RTS
    beim Flashen.
  - Koax-Steckverbinder (`Conn_Coaxial_Small`) für die GNSS-Antenne.
  - Status-LEDs, Taster (Reset/Boot), Befestigungsbohrungen.
- `kicad/supply.kicad_sch` – Stromversorgung/Akkuladeteil
  - **NCR18650B**: Li-Ion-Akku (18650) als Energiespeicher.
  - **TP4056 + DW01A**: Laderegler mit Akku-Schutzbeschaltung (Über-/Tiefentladung,
    Überstrom), Ladeeingang über USB-C.
  - **LTC4412**: Ideal-Diode-Power-Path-Controller – schaltet automatisch zwischen
    USB-Versorgung und Akku um.
  - **AP2112K-3.3**: 3,3-V-LDO-Spannungsregler für die Logikversorgung.
  - **USBLC6-2P6**: ESD-Schutz am USB-C-Eingang.

KiCad-Version: 9.0. Externe Symbol-/Footprint-Bibliothek: `PCM_yvolodym` (siehe
`~/.local/share/kicad/9.0/3rdparty/...` bzw. das separate Repo `arduino/kicad-library`).

## Repository-Struktur

```
kicad/
  esp32-gps.kicad_pro   Projektdatei
  esp32-gps.kicad_sch   Hauptschaltplan (ESP32, GNSS, USB-UART)
  supply.kicad_sch      Schaltplan Stromversorgung/Ladeschaltung
  esp32-gps.kicad_pcb   Platinenlayout
  esp32-gps.kicad_prl   lokale Projekteinstellungen (nicht versionsrelevant)
  esp32-gps-backups/    KiCad-Autobackups (in .gitignore, nicht committen)
```

Es gibt aktuell keinen Firmware-/Software-Ordner. Sobald ESP32-Code hinzukommt, sollte er in
einem eigenen Verzeichnis (z. B. `firmware/`) mit eigener Doku abgelegt werden.

## Arbeiten mit diesem Repo

- Änderungen an Schaltplan/Layout erfolgen in KiCad; Claude Code selbst bearbeitet die
  `.kicad_sch`/`.kicad_pcb`-Dateien nicht manuell, sondern nutzt die vorhandenen
  **kicad-happy** Skills für Analyse, BOM, Fertigungsvorbereitung und Doku-Erzeugung, u. a.:
  - `kicad-happy:kicad` – Schaltplan-/Layout-Review, ERC/DRC, Netzverfolgung, BOM-Extraktion.
  - `kicad-happy:bom` – Bestückungsliste inkl. Distributor-Preisen (DigiKey/Mouser/LCSC/…).
  - `kicad-happy:jlcpcb` / `kicad-happy:pcbway` – Fertigungsvorbereitung, Bestellworkflow.
  - `kicad-happy:emc` – EMC-Vorab-Analyse (relevant wegen HF-Antennenanbindung des GNSS-Moduls).
  - `kicad-happy:kidoc` – Generierung von Hardware-Design-Dokumenten (HDD) aus dem Projekt.
- `esp32-gps-backups/` enthält automatische KiCad-Backups (ZIP) und ist per `.gitignore`
  ausgeschlossen – nicht versehentlich einchecken.
- Commits/PRs und Doku in diesem Repo auf Deutsch verfassen.

## Offene Punkte / nächste Schritte

- Firmware für den ESP32 (Arduino- oder ESP-IDF-Projekt): GNSS-UART auslesen (NMEA), Daten über
  Bluetooth SPP oder BLE bereitstellen.
- BOM/Fertigungsvorbereitung für das Board (siehe `kicad-happy:bom`).
- Antennen-/HF-Betrachtung für die GNSS-Anbindung (Koax-Anschluss).
