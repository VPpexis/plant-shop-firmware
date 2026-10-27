# Plant Shop Firmware Archive

ATmega328P and ESP8266 / NodeMCU sketches recovered from Google Drive for **IoT-based Plant Guide, Inventory and Billing System for a Plant Shop**, a 2022 Computer Engineering design project at Mapúa University.

The project pairs a barcode-scanning handheld device with a plant-shop application and Firebase. The ATmega328P reads the barcode and operation inputs and drives the LCD. The ESP8266 handles the Wi-Fi and Firebase side of the archived workflow.

**This is a historical source archive.** Sketch names, including `Final` and version numbers, come from Drive; they do not establish a tested release or a guaranteed compatible device pair. The final report contains later firmware listings that differ from these files.

## Related application

- [VPpexis/DesignProjectApp](https://github.com/VPpexis/DesignProjectApp) — the Flutter application fork
- [ckdirecto/DesignProjectApp](https://github.com/ckdirecto/DesignProjectApp) — original app repository

This repository contains firmware only. There is no ESP32 implementation: the original Wi-Fi controller was an **ESP8266**. ESP32 appears in the report as a future recommendation.

## Archived sketches

Each sketch is kept in a matching Arduino sketch directory. Variants from the root `Design` folder and its `Design Codes` subfolder are stored separately because identically named files have different contents.

| Location | Original sketch | Purpose |
| --- | --- | --- |
| `atmega328p/root-final/` | `FLS_CLAUDEE_ARDUINO__Final_` | Earlier ATmega328P variant |
| `atmega328p/root-final-v2/` | `FLS_CLAUDEE_ARDUINO__Final_v2` | Root-folder v2 variant |
| `atmega328p/design-codes-final-v2/` | `FLS_CLAUDEE_ARDUINO__Final_v2` | Distinct v2 copy in Design Codes |
| `esp8266/root-final/` | `FLS_CLAUDEE_NODEMCU__FINAL_` | Earlier FirebaseArduino variant |
| `esp8266/root-final-v4/` | `FLS_CLAUDEE_NODEMCU__FINAL_V4` | Root-folder v4 FirebaseArduino variant |
| `esp8266/design-codes-final-v4/` | `FLS_CLAUDEE_NODEMCU__FINAL_V4` | Distinct v4 copy in Design Codes |
| `esp8266/design-codes-final-v2/` | `FLS_CLAUDEE_NODEMCU__FINAL_v2` | Firebase_ESP_Client / messaging experiment |
| `experiments/lcd-module/` | `Design_LCDMODTest` | Early LCD and button-input experiment |

See [docs/sources.json](docs/sources.json) for each Drive file ID, source URL, original timestamps, local path, and SHA-256 hashes. Folder labels describe provenance, not chronological compatibility.

## Hardware and libraries

The documented device uses an ATmega328P, ESP8266 / NodeMCU, barcode scanner, 20×4 I²C LCD, and an external button-encoder circuit. It supports View, Add, Remove, and Pay inputs. Checkout prepares the order and bill; customers pay at the cashier.

| Sketch family | Dependencies visible in the source |
| --- | --- |
| ATmega328P | Arduino AVR support, SoftwareSerial, LiquidCrystal_I2C |
| ESP8266 FirebaseArduino variants | ESP8266 Arduino core, FirebaseArduino, ArduinoJson, ESP8266HTTPClient, SoftwareSerial |
| ESP8266 Firebase_ESP_Client variant | ESP8266 Arduino core, Firebase_ESP_Client and its bundled token/RTDB helpers, SoftwareSerial |
| LCD experiment | LiquidCrystal_I2C, Wire |

The original library versions and board configurations are not pinned. Different LiquidCrystal_I2C libraries expose different initialization APIs (`begin()` versus `init()`); use the variant expected by the sketch. FirebaseArduino and Firebase_ESP_Client are separate library families and cannot be substituted without adapting the code.

## Open and configure a sketch

1. Install Arduino IDE and board support appropriate to the target: an ATmega328P-compatible AVR target or the ESP8266 NodeMCU target. Do not select an ESP32 board for these sketches.
2. Install the dependencies for the chosen variant. This archive does not prescribe a verified library-version combination.
3. Open the `.ino` file inside its matching sketch directory.
4. For an ESP8266 sketch, copy the adjacent `secrets.example.h` to `secrets.h`, then supply your own Wi-Fi and Firebase development configuration.
5. Check the schematic, actual board pinout, UART connections, logic levels, baud rates, and selected programmer before connecting hardware.
6. Verify the sketch in the IDE before uploading. Compare the selected ATmega328P and ESP8266 variants' message protocol and database paths with the app.

In the ATmega328P v2 files, `SoftwareSerial(5, 6)` runs at 9600 baud and the hardware serial port at 115200 baud; encoder inputs use pins 2–4. These are source-code settings, not a substitute for the circuit schematic.

## Configuration handling

Original Wi-Fi credentials, Firebase configuration, tokens, and an embedded private key have been removed from the imported sketches and replaced by `#include "secrets.h"`. Each ESP8266 variant includes a placeholder template listing the symbols it needs. `secrets.h`, PEM files, and private-key files are ignored by Git.

Use a separate development Firebase project and your own accounts. Historical service-account keys or database credentials must not be copied into commits. The auxiliary PEM file in Drive and the report's credential-bearing appendices are not imported.

Apart from configuration extraction and whitespace normalization, the sketches retain their archived program logic. See [docs/archive-notes.md](docs/archive-notes.md) for limitations that matter when restoring them.

## Validation status

The import was checked for matching sketch/folder names, source provenance, file hashes, configuration removal, and ignored secret-file paths. No Arduino toolchain or hardware test was run during archival. The files are not presented as build-verified or ready to flash.

## Team and provenance

**Marie Krystine D. Anticuando · Claudee Khiarra R. Directo · Van Philip M. Panugan**
BS Computer Engineering, Mapúa University — May 2022
Design adviser and client: Engr. Analyn N. Yumang

Recovered from the team's [Design folder](https://drive.google.com/drive/folders/1xj-aS-xiI1TtIt0Fd7cpNC9XyxRr583X). Source links may require Drive access. Original Drive files remain unchanged.

This archive does not assert a new license over the recovered team code or redistribute the third-party Arduino libraries.
