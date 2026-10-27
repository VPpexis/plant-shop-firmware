# Restoring the archived firmware

## Source selection

Eight `.ino` files were recovered from the Drive `Design`, `Design Codes`, and `Design Code` folders. Duplicate filenames were retained in different provenance directories because their contents differ. No variant is labeled as the canonical or latest functional release.

The root ATmega328P `Final_v2` file has a later Drive modification timestamp than the similarly named copy in `Design Codes`. That timestamp alone is not evidence of a newer working implementation. Later code in the final PDF is outside this Drive-only import.

The library folder, plant-image assets, report PDF, and auxiliary PEM file are not bundled. Dependencies are listed by sketch family in the README; exact original versions remain unknown.

## Import changes

- Normalized CRLF line endings to LF and trimmed trailing whitespace.
- Moved hard-coded ESP8266 configuration definitions into ignored `secrets.h` files, with safe `secrets.example.h` templates committed instead.
- Removed the original private-key literal from the Firebase_ESP_Client variant using the same configuration mechanism.
- Preserved sketch filenames, version variants, comments, and remaining program logic.

`sources.json` records hashes of the original bytes and the sanitized archive. Different hashes are expected where configuration or whitespace changed. Original source bytes are not committed.

## Known limitations

- `experiments/lcd-module/Design_LCDMODTest` contains undefined LED identifiers and an extra closing brace. It is an unfinished experiment and requires repair before compilation.
- The ATmega328P root `Final_v2` Pay branch writes the cart-ID request character `c`, while the ESP8266 v4 files handle checkout under `p`. Do not assume those variants implement checkout together without reconciliation.
- The sketches include blocking delays, fixed character buffers, and serial parsing that need review before reuse.
- ATmega328P variants display plant-care values from local arrays. This differs from a simple interpretation in which every LCD field is fetched from Firebase.
- Database paths and operation messages differ across the Drive variants, the app repository, and the later PDF listings. Review the whole workflow before choosing a pair.
- ESP8266 and ATmega328P board settings, wiring, and the original library versions are not fully captured by the source alone.

These limitations are documented rather than silently repaired so that the archive remains traceable to Drive. Modernization and functional fixes should be made as separately reviewed changes.
