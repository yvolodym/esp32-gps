# esp32-gps

Akku-betriebenes GNSS-Empfänger-Board auf Basis des **ESP32**. Ein GNSS-Modul (GPS/BDS/GLONASS)
liefert die Positionsdaten, der ESP32 liest sie über UART aus und stellt sie per **Bluetooth**
für andere Geräte (z. B. Smartphone, Laptop, Navigationssoftware) bereit.

> Aktueller Stand: vollständiges KiCad-Hardwaredesign (Schaltplan + Platinenlayout). Die
> ESP32-Firmware ist noch nicht Teil dieses Repos.

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

## Repo-Struktur

```
kicad/
  esp32-gps.kicad_pro   Projektdatei
  esp32-gps.kicad_sch   Hauptschaltplan
  supply.kicad_sch      Stromversorgung/Ladeschaltung
  esp32-gps.kicad_pcb   Platinenlayout
```

## Status / Roadmap

- [x] Schaltplan (MCU, GNSS, USB, Stromversorgung)
- [x] Platinenlayout
- [ ] Bestückungsliste (BOM) / Fertigungsvorbereitung
- [ ] ESP32-Firmware (GNSS-UART → Bluetooth)
- [ ] Gehäuse

## Mitwirken

Projektsprache ist Deutsch – Commits, Issues und Doku bitte auf Deutsch verfassen.

Weitere Hinweise für die Arbeit mit Claude Code an diesem Projekt siehe [`CLAUDE.md`](./CLAUDE.md).

## Lizenz

Dieses Projekt steht unter der [CERN Open Hardware Licence Version 2 - Strongly Reciprocal
(CERN-OHL-S-2.0)](./LICENSE), einer verbreiteten Copyleft-Lizenz für offene Hardwareprojekte.
