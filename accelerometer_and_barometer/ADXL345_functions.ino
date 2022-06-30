void initADXL345 (void) {
  Wire.begin(); // Initiate the Wire library
  Wire.beginTransmission(0x53); // Start communicating with the device (ADXL345 I2C address)
  Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D
  Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable 
  Wire.endTransmission();
  delay(10);
}
void getRawAccel(int16_t* ax, int16_t* ay, int16_t* az) {
  Wire.beginTransmission(0x53); // ADXL345 I2C address
  Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(0x53, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  *ax = ( Wire.read()| Wire.read() << 8); // X-axis value
  *ay = ( Wire.read()| Wire.read() << 8); // Y-axis value
  *az = ( Wire.read()| Wire.read() << 8); // Z-axis value
}
int twosComplementToInt(int16_t input) { // takes a 16 bit 2s complement integer and 
  return (input >= 32768) ? (int)(-(~input + 1)) : (int)input;
}
void getAccel(float* ax, float* ay, float* az) {
  int16_t ax1, ay1, az1;
  getRawAccel(&ax1, &ay1, &az1);
  *ax = twosComplementToInt(ax1)/256.0;
  *ay = twosComplementToInt(ay1)/256.0;
  *az = twosComplementToInt(az1)/256.0;
}
