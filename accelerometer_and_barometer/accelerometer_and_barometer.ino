#include <Adafruit_BMP085.h>
#include <Wire.h>

float ax, ay, az;
float alt, pres, temp;

Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(9600);
  initADXL345();
  if (!bmp.begin()) {
    Serial.println("Sensor not connected!");
    while (1);
  }
}

void loop() {
  getAccel(&ax, &ay, &az);
  alt = bmp.readAltitude();
  pres = bmp.readPressure();
  temp = bmp.readTemperature();

  Serial.print(ax);
  Serial.print(" ");
  Serial.print(ay);
  Serial.print(" ");
  Serial.print(az);
  Serial.print(" ");
  Serial.print(alt);
  Serial.print(" ");
  Serial.print(temp);
  Serial.print(" ");
  Serial.println(pres);
}
