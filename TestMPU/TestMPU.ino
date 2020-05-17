// (c) Michael Schoeffler 2017, http://www.mschoeffler.de

//  Register 25 – Sample Rate Divider: SMPRT_DIV = 0 -> 1kHz or 1ms
//  Register 27 – Gyroscope Configuration: GYRO_CONFIG. FS_SEL = 0 -> Full Scale Range = +-250º/s
//  Register 28 – Accelerometer Configuration: ACCEL_CONFIG. AFS_SEL = 0 -> Full Scale Range = +-2g
//  Registers 59 to 64 – Accelerometer Measurements
//  Register (Hex) Register (Decimal) 
//  3B 59 ACCEL_XOUT[15:8]
//  3C 60 ACCEL_XOUT[7:0]
//  3D 61 ACCEL_YOUT[15:8]
//  3E 62 ACCEL_YOUT[7:0]
//  3F 63 ACCEL_ZOUT[15:8]
//  40 64 ACCEL_ZOUT[7:0]
//  Registers 67 to 72 – Gyroscope Measurements
//  Register (Hex) Register (Decimal) 
//  43 67 GYRO_XOUT[15:8]
//  44 68 GYRO_XOUT[7:0]
//  45 69 GYRO_YOUT[15:8]
//  46 70 GYRO_YOUT[7:0]
//  47 71 GYRO_ZOUT[15:8]
//  48 72 GYRO_ZOUT[7:0]
//  Register 107 – Power Management 1: PWR_MGMT_1. TEMP_DIS = 1 by default.
//  Bit 7: DEVICE_RESET. All registers are set to zero but 107 and 117.

#include "Wire.h" // This library allows you to communicate with I2C devices.

const float GRAVITY = 9.81;
const int16_t MAX_SCALE = 0x7FFF;
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050.
// If AD0 pin is set to LOW, the I2C address will be 0x68.
// If AD0 pin is set to HIGH, the I2C address will be 0x69.

//int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
//int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
//int16_t temperature; // variables for temperature data

char tmp_str[7]; // temporary variable used in convert function
char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

float scaleAcc (int16_t acc){
  // Register 28 – Accelerometer Configuration: ACCEL_CONFIG. AFS_SEL = 0 -> Full Scale Range = +-2g
  return (float) 2 * acc * GRAVITY / MAX_SCALE;
}

float scaleGyro (int16_t gyro){
  // Register 27 – Gyroscope Configuration: GYRO_CONFIG. FS_SEL = 0 -> Full Scale Range = +-250º/s
  return (float) 250 * gyro / MAX_SCALE;
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(128); // Bit 7: DEVICE_RESET = 1
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void loop() {
  int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
  int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
  int16_t temperature; // variables for temperature data

  float accelerometerF_x, accelerometerF_y, accelerometerF_z;
  float gyroF_x, gyroF_y, gyroF_z;
  
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 14, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

  accelerometerF_x = scaleAcc(accelerometer_x);
  accelerometerF_y = scaleAcc(accelerometer_y);
  accelerometerF_z = scaleAcc(accelerometer_z);
  gyroF_x = scaleGyro(gyro_x);
  gyroF_y = scaleGyro(gyro_y);
  gyroF_z = scaleGyro(gyro_z);
  
  // print out data
  Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
  Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y));
  Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accelerometer_z));
  // the following equation was taken from the documentation [MPU-6000/MPU-6050 Register Map and Description, p.30]
  Serial.print(" | tmp = "); Serial.print(temperature/340.00+36.53);
  Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
  Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
  Serial.print(" | gZ = "); Serial.print(convert_int16_to_str(gyro_z));
  Serial.println();
  
  // print out data
  Serial.print("aX = "); Serial.print(accelerometerF_x);
  Serial.print(" | aY = "); Serial.print(accelerometerF_y);
  Serial.print(" | aZ = "); Serial.print(accelerometerF_z);
  Serial.print(" | gX = "); Serial.print(gyroF_x);
  Serial.print(" | gY = "); Serial.print(gyroF_y);
  Serial.print(" | gZ = "); Serial.print(gyroF_z);
  Serial.println();
  
  // delay
  delay(1000);
}
