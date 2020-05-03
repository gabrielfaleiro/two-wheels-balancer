# Documentation

REFERENCES: 
- https://learn.adafruit.com/all-about-stepper-motors/types-of-steppers
- https://learn.adafruit.com/all-about-stepper-motors/driving-a-stepper

## Stepper motors

- Seagate 15PM-M001-01 (Bipolar - 4 wires)
  - 3D CAD: https://grabcad.com/library/15pm-m001-01-stepper-motor-1
  - red - blue 29 ohms
  - yellow - white 29 ohms
  - Movement order, test with 5V: clockwise movement, invert to turn to the other direction

| r | b | w | y |
| + | - |   |   |
|   |   | - | + |
| - | + |   |   |
|   |   | + | - |

- 6Z281B (Unipolar - 5 wires)
  - 96 steps per revolution
  - coil 1:
    - brown: 4 (50.5 ohms to black)
    - orange: 2 (48.8 ohms to black)
  - coil 2:
    - red: 1 (50.5 ohms to black)
    - grey: 3 (50.5 ohms to black)
  - black: common (GND)
  - Arduino Motor Shield L293D connection

| X2 shield | wire |
| A1  | red     |
| A2  | grey    |
| GND | black   |
| B1  | orange  |
| B2  | brown   |

## Arduino Motor Shield L293D

REFERENCES:
- https://create.arduino.cc/projecthub/electropeak/arduino-l293d-motor-driver-shield-tutorial-c1ac9b
- https://github.com/adafruit/Adafruit-Motor-Shield-library
- https://lastminuteengineers.com/l293d-motor-driver-shield-arduino-tutorial/
  - https://lastminuteengineers.com/l293d-motor-driver-shield-arduino-tutorial/#driving-stepper-motors-with-l293d-shield
- https://cdn-learn.adafruit.com/downloads/pdf/adafruit-motor-shield.pdf
