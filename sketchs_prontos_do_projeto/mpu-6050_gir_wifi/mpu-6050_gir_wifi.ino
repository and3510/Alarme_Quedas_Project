#define BLYNK_TEMPLATE_ID           "TMPL2rm1y8y-C"
#define BLYNK_TEMPLATE_NAME         "and"
#define BLYNK_AUTH_TOKEN            "4D53tOZEShd8dD2qHES39xxkd7ZqNJhe"

#include <Wire.h>
#include <BlynkSimpleEsp8266.h>
#include <MPU6050_tockn.h>
#include <ESP8266WiFi.h>

char auth[] = "4D53tOZEShd8dD2qHES39xxkd7ZqNJhe";
char ssid[] = "ORA_2.4G";                 
char pass[] = "86988134365";

MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }

  Blynk.begin(auth, ssid, pass);

  // Inicialize o MPU6050 e calibre-o
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  Serial.println("Inicialização concluída");
}

void loop() {
  Blynk.run();

  mpu6050.update();
  float pitch = mpu6050.getAngleX();
  float roll = mpu6050.getAngleY();
  float yaw = mpu6050.getAngleZ();

  // Converter radianos para graus
  pitch = pitch * 180.0 / M_PI;
  roll = roll * 180.0 / M_PI;
  yaw = yaw * 180.0 / M_PI;

  Blynk.virtualWrite(V2, pitch);
  Blynk.virtualWrite(V3, roll);
  Blynk.virtualWrite(V4, yaw);

  Serial.print(pitch);


  delay(100);  // Ajuste o intervalo de leitura conforme necessário
}
