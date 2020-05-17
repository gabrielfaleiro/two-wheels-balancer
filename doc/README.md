# Documentation

REFERENCES: 
- https://learn.adafruit.com/all-about-stepper-motors/types-of-steppers
- https://learn.adafruit.com/all-about-stepper-motors/driving-a-stepper

## Stepper motors

Note: changing one coil cable order changes the direction of the motor

- Seagate 15PM-M001-01 (Bipolar - 4 wires)
  - 200 steps per revolution
  - coil 1 (red-blue): 30.6 ohms
  - coil 2 (white-yellow): 30.5 ohms
  - 3D CAD: https://grabcad.com/library/15pm-m001-01-stepper-motor-1
  - red - blue 29 ohms
  - yellow - white 29 ohms
  - Movement order, test with 5V: clockwise movement, invert to turn to the other direction

  Spinning sense: right hand rule in shaft direction
  |A1 |A2 |B1 |B2 |
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

  Spinning sense: left hand rule in shaft direction
  | X2 shield | wire |
  | A1  | red     |
  | A2  | grey    |
  | GND | black   |
  | B1  | orange  |
  | B2  | brown   |

- Tixar (Unipolar - 5 wires)
  - 200 steps per revolution
  - coil 1:
    - blue: 6.0 ohms to black
    - orange: 6.0 ohms to black
  - coil 2:
    - red: 6.0 ohms to black
    - yellow: 6.0 ohms to black
  - black: common (GND)
  - Arduino Motor Shield L293D connection

  Spinning sense: right hand rule in shaft direction
  | X2 shield | wire |
  | A1  | blue    |
  | A2  | orange  |
  | GND | black   |
  | B1  | red     |
  | B2  | yellow  |

- 4SPM-24D6ZA 18DEC91MA (Unipolar - 6 wires)
  - 7.5 DEG 12.5 Ohm
  - 48 steps per revolution
  - coil 1:
    - yellow: 12.6 ohms to red
    - red: middle coil
    - orange: 12.8 ohms to red
  - coil 2:
    - brown: 12.6 ohms to white
    - white: middle coil
    - black: 12.8 ohms to white
  - black: common (GND)
  - Arduino Motor Shield L293D connection

  Spinning sense: left hand rule in shaft direction
  | X2 shield | wire  |
  | A1  | yellow      |
  | A2  | orange      |
  | GND | red + white |
  | B1  | brown       |
  | B2  | black       |

## Gyro & Accelerometers

- REF: https://www.mschoeffler.de/2017/10/05/tutorial-how-to-use-the-gy-521-module-mpu-6050-breakout-board-with-the-arduino-uno/
- REF: https://create.arduino.cc/projecthub/Nicholas_N/how-to-use-the-accelerometer-gyroscope-gy-521-6dfc19
- REF: http://wiki.epalsite.com/index.php?title=MPU6050_Gyro%26Accelerometer
  - MPU-6050 Datasheet: http://wiki.epalsite.com/images/4/41/MPU6050_Datasheet.pdf
  - MPU-6050 Memory Map: https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf

Register 25 – Sample Rate Divider: SMPRT_DIV = 0 -> 1kHz or 1ms
Register 27 – Gyroscope Configuration: GYRO_CONFIG. FS_SEL = 0 -> Full Scale Range = +-250º/s
Register 28 – Accelerometer Configuration: ACCEL_CONFIG. AFS_SEL = 0 -> Full Scale Range = +-2g
Registers 59 to 64 – Accelerometer Measurements
Register (Hex) Register (Decimal) 
3B 59 ACCEL_XOUT[15:8]
3C 60 ACCEL_XOUT[7:0]
3D 61 ACCEL_YOUT[15:8]
3E 62 ACCEL_YOUT[7:0]
3F 63 ACCEL_ZOUT[15:8]
40 64 ACCEL_ZOUT[7:0]
Registers 67 to 72 – Gyroscope Measurements
Register (Hex) Register (Decimal) 
43 67 GYRO_XOUT[15:8]
44 68 GYRO_XOUT[7:0]
45 69 GYRO_YOUT[15:8]
46 70 GYRO_YOUT[7:0]
47 71 GYRO_ZOUT[15:8]
48 72 GYRO_ZOUT[7:0]
Register 107 – Power Management 1: PWR_MGMT_1. TEMP_DIS = 1 by default.
Bit 7: DEVICE_RESET. All registers are set to zero but 107 and 117.

## Bluetooth

- REF: http://www.martyncurrey.com/arduino-with-hc-05-bluetooth-module-at-mode/


## Arduino Motor Shield L293D

REFERENCES:
- https://create.arduino.cc/projecthub/electropeak/arduino-l293d-motor-driver-shield-tutorial-c1ac9b
- https://github.com/adafruit/Adafruit-Motor-Shield-library
- https://lastminuteengineers.com/l293d-motor-driver-shield-arduino-tutorial/
  - https://lastminuteengineers.com/l293d-motor-driver-shield-arduino-tutorial/#driving-stepper-motors-with-l293d-shield
- https://cdn-learn.adafruit.com/downloads/pdf/adafruit-motor-shield.pdf
