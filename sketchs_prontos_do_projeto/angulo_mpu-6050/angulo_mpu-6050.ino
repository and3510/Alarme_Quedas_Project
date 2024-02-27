#include <Wire.h>
#include <MPU6050_tockn.h>

MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(115200);

  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  Serial.println("Calibração concluída. Agitando o sensor...");
  delay(2000);
}

void loop() {
  mpu6050.update();
  float pitch = mpu6050.getAngleX();
  float roll = mpu6050.getAngleY();
  float yaw = mpu6050.getAngleZ();

  Serial.print("Pitch: ");
  Serial.print(pitch);
  Serial.print("   Roll: ");
  Serial.print(roll);
  Serial.print("   Yaw: ");
  Serial.println(yaw);

  delay(100); 
}
