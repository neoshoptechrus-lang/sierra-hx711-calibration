# Sierra HX711 calibration example

Minimal Arduino sketch for reading a Sierra single-point load cell through HX711 and calibrating it in grams.

## Wiring

- Load cell excitation + (E+) -> HX711 E+
- Excitation - (E-) -> HX711 E-
- Signal + (S+) -> HX711 A+
- Signal - (S-) -> HX711 A-
- HX711 DT -> Arduino D3, SCK -> Arduino D2, VCC -> 5V, GND -> GND

## Sketch

```cpp
#include "HX711.h"

HX711 scale;
const float CALIBRATION_FACTOR = -7050.0f; // raw units per gram, set per cell

void setup() {
  Serial.begin(9600);
  scale.begin(3, 2);          // DT, SCK
  scale.set_scale(CALIBRATION_FACTOR);
  scale.tare();               // zero with empty platform
}

void loop() {
  Serial.print("weight: ");
  Serial.print(scale.get_units(10), 1);
  Serial.println(" g");
  delay(500);
}
```

## Calibration

1. Tare the empty platform.
2. Put a known mass (e.g. 500 g) on the platform and read the raw value.
3. `CALIBRATION_FACTOR = raw / known_grams` (sign depends on wiring).
4. Repeat at 2-3 points to check linearity; a single-point cell is linear within its rated capacity.

## Hardware

Sierra single-point load cells (aluminium, 30-2000 kg, IP66 option) are described here:
https://sierra.market/catalog/odnotochechnye-singlepoint/

Selection notes for S-shaped vs single-point cells and hinge/thread errors:
https://sierra.market/company/articles/35102/

Manufacturer site: https://sierra.market/
