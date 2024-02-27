#define BLYNK_TEMPLATE_NAME         "and"
#define BLYNK_TEMPLATE_ID           "TMPL2rm1y8y-C"
#define BLYNK_AUTH_TOKEN            "4D53tOZEShd8dD2qHES39xxkd7ZqNJhe"
#define som 2
#define botaoPin 3



#include <Wire.h>
#include <BlynkSimpleEsp8266.h>
#include <MPU6050.h>
#include <ESP8266WiFi.h>

char auth[] = "4D53tOZEShd8dD2qHES39xxkd7ZqNJhe";
char ssid[] = "ORA_2.4G";
char pass[] = "86988134365";

MPU6050 mpu;
bool limitedequeda = true;
bool caindo = false;
unsigned long começodaqueda = 0;
const unsigned long numero = 200;

void setup() {
  pinMode(som, OUTPUT);
  

  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  pinMode(botaoPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(botaoPin), botaoAcionado, RISING);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }

  Blynk.begin(auth, ssid, pass);
  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 conexao falhou.");
    while (1);
  }
}

void loop() {
  Blynk.run();
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  float accX = (float)ax / 16384.0;
  float accY = (float)ay / 16384.0;
  float accZ = (float)az / 16384.0;

  float NORMxyz = sqrt(accX * accX + accY * accY + accZ * accZ);

  Blynk.virtualWrite(V5, accX);
  Blynk.virtualWrite(V6, accY);
  Blynk.virtualWrite(V7, accZ);
  Blynk.virtualWrite(V1, NORMxyz);



  if (NORMxyz < 0.2 && limitedequeda) {
    Serial.println("Objeto caindo!");
    Blynk.virtualWrite(V9, 1);
    Blynk.virtualWrite(V8, "Objeto caindo!");
    delay(2000);
    digitalWrite(som, 1);
    Blynk.virtualWrite(V8, "  ");
    Blynk.virtualWrite(V9, 0);
    limitedequeda = false;
    caindo = true;
    começodaqueda = millis();
  }


  if (caindo && (millis() - começodaqueda) >= numero) {
    Serial.println("objeto caiu");
    Blynk.virtualWrite(V10, 1);
    Blynk.virtualWrite(V8, "objeto caiu");
    caindo = false;
    Blynk.virtualWrite(V8, "  ");
    Blynk.virtualWrite(V10, 0);
  }

  if (NORMxyz >= 0.9 && NORMxyz <= 1.1 && !limitedequeda) {
    Serial.println("objeto em repouso");
    Blynk.virtualWrite(V8, "objeto em repouso");
    delay(2000);
    Blynk.virtualWrite(V8, "  ");
    limitedequeda = true;
    caindo = false;
  }

  void botaoAcionado();
  delay(50);
}


void botaoAcionado() {
static bool estado = HIGH;
static unsigned long delayEstado;


   if ( (millis() - delayEstado) > 100 ) {
     estado = !estado;
     delayEstado = millis();
   }
    digitalWrite(som,estado);
}
