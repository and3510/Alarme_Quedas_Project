#define som 2
#define botaoPin 3



#include <Wire.h>
#include <MPU6050.h>


MPU6050 mpu;
bool limitedequeda = true;
bool caindo = false;
unsigned long começodaqueda = 0;
const unsigned long numero = 200;

void setup() {
  pinMode(som, OUTPUT);
  

  Serial.begin(9600);

  pinMode(botaoPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(botaoPin), botaoAcionado, RISING);

  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 conexao falhou.");
    while (1);
  }
}

void loop() {

  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  float accX = (float)ax / 16384.0;
  float accY = (float)ay / 16384.0;
  float accZ = (float)az / 16384.0;

  float NORMxyz = sqrt(accX * accX + accY * accY + accZ * accZ);




  if (NORMxyz < 0.2 && limitedequeda) {
    Serial.println("Objeto caindo!");

    delay(2000);
    digitalWrite(som, 1);

    limitedequeda = false;
    caindo = true;
    começodaqueda = millis();
  }


  if (caindo && (millis() - começodaqueda) >= numero) {
    Serial.println("objeto caiu");

    caindo = false;

  }

  if (NORMxyz >= 0.9 && NORMxyz <= 1.1 && !limitedequeda) {
    Serial.println("objeto em repouso");

    delay(2000);

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
