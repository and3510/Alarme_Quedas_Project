// -> Credenciais:                                                      // Credenciais para conexao do arduino com o aplicativo blynk iot.
#define BLYNK_TEMPLATE_NAME         "and"                               // Nome do dispositivo no blynk
#define BLYNK_TEMPLATE_ID           "TMPL2rm1y8y-C"                     // ID do dispositibo no blynk
#define BLYNK_AUTH_TOKEN            "4D53tOZEShd8dD2qHES39xxkd7ZqNJhe"
#define som 2  // Codigo de Autenticaçao do dispositivo do blynk      



// -> Bibliotecas:
#include <Wire.h>                          // Wire --> Biblioteca permite que você se comunique com dispositivos I2C/TWI.
#include <BlynkSimpleEsp8266.h>            // BlynkEsp8266 --> Biblioteca que permite a comunicaçao do Arduino d1 (esp8266) com o Blynk aplicativo.
#include <MPU6050.h>                       // MPU6050 --> Biblioteca com as funçoes dos eixos do componente MPU6050, como MPU-6050 6-axis accelerometer/gyroscope.
#include <ESP8266WiFi.h>                   // ESP8266WIFI --> Biblioteca que conecta o esp8266 com o wifi.


// -> Autenticaçao,Nome da Rede e Senha da Rede:
char auth[] = "4D53tOZEShd8dD2qHES39xxkd7ZqNJhe";                 // O mesmo que o #define BLYNK_AUTH_TOKEN 
char ssid[] = "ORA_2.4G";                 
char pass[] = "86988134365";

MPU6050 mpu;                            // defini MPU6050 como mpu para utilizar com as funçoes do componente.
bool limitedequeda = true;              // variavel pra confirmar o limite de queda.
bool caindo = false;                    // variavel para confirmar se o objeto esta caindo.
unsigned long começodaqueda = 0;        // variavel que vai ser utilizada para calcular o o tempo de queda.
const unsigned long numero = 0;       // variavel constante usado para limite do tempo de queda.

// Setup -> Como vai começar o arduino
void setup() {        
  pinMode(som,OUTPUT);    
  digitalWrite(som,0);         
  Serial.begin(115200);               //  Saida para porta serial
  WiFi.begin(ssid, pass);             // Para conectar com a internet da rede local
  
// Teste de Conexao com a internet
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }

  Blynk.begin(auth, ssid, pass);                  // Para conectar com o blynk usando as credenciais anteriores

  Wire.begin();                                   // Inicia a comunicaçao com os componentes
  mpu.initialize();                               // Inicia a analise dos eixos do mpu6050

  if (!mpu.testConnection()) {                    // Tentativa de conexao com o compoenente,ate conectar com mpu6050
    Serial.println("MPU6050 conexao falhou.");     
    while (1);
  }

}


void loop() {
  Blynk.run();              //Rodar o blynk
  
  
  int16_t ax, ay, az;       // Variaveis para o acelerometro
  int16_t gx, gy, gz;       // Variaveis para o giroscopio

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);   // Colocando os eixos para cada variaveis corretamente 3 para aceleraçao e 3 para giroscopio
  
  // -> Divisao para conseguir valor exato do g dividindo os valores brutos dos eixos pela sensibilidade LSB/g escrita no datasheet:
  float accX = (float)ax / 2048.0; 
  float accY = (float)ay / 2048.0;
  float accZ = (float)az / 2048.0;

  // -> Calcular os ângulos de inclinação em graus ao longo dos eixos X, Y e Z com base em dados de aceleração nas coordenadas X, Y e Z.
  float girX = atan2(-accY, accZ) * 180.0 / PI;
  float girY = atan2(accX, sqrt(accY * accY + accZ * accZ)) * 180.0 / PI;
  float girZ = atan2(accZ, sqrt(accX * accX + accY * accY)) * 180.0 / PI;

  // -> Divisao para conseguir o valor exato do º/s dividindo os valores brutos dos eixos pela sensibilidade LSB/(º/s) escrita no datasheet:
  float girx = (float)gx / 65.5;
  float giry = (float)gy / 65.5;
  float girz = (float)gz / 65.5;

   Serial.print("Aceleração X: ");
   Serial.print(accX);
   Serial.print("   Aceleração Y: ");
   Serial.print(accY);
   Serial.print("   Aceleração Z: ");
   Serial.println(accZ);
  // Serial.print("   Girx: ");
  // Serial.print(girx);
  // Serial.print("   Giry: ");
  // Serial.print(giry);
  //Serial.print("   Girz: ");
  // Serial.println(girz);
  

  // Comunicaçao com as portas virtuais do blynk, print para o blynk:
  Blynk.virtualWrite(V5, accX);     
  Blynk.virtualWrite(V6, accY);     
  Blynk.virtualWrite(V7, accZ);     
  // Blynk.virtualWrite(V2, girx);     
  // Blynk.virtualWrite(V3, giry);    
  // Blynk.virtualWrite(V4, girz);     
  

  // Norma dos eixos x, y e z do acelerometro:
  float NORMxyz = sqrt(accX * accX + accY * accY + accZ * accZ);

  //Serial.print("Norma :");
  //Serial.println(NORMxyz);


  Blynk.virtualWrite(V1, NORMxyz);
  

  // Condiçoes para a detecçao de uma queda:
  if ((NORMxyz >= 13.0 || accX < -10.6 || (accX >=  -6.0 && accX <= -0.2) || accX >= 1.5 ) && limitedequeda) {
    //Serial.println("Objeto caindo !");
    Blynk.virtualWrite(V9,1);
    Blynk.virtualWrite(V8, "Movimentaçao brusca!");
    delay(2000);
    digitalWrite(som,1);
    delay(1500);
    digitalWrite(som,0);
    Blynk.virtualWrite(V8, "  ");
    Blynk.virtualWrite(V9,0);
    limitedequeda = false;
    caindo = true;
    // começodaqueda = millis();     // a funçao millis() inicia um cronometro apartir do valor da variavel começodaqueda que é 0
  }


  if ( ((accZ <= -5.0 || accZ >= 9) || (accX <= -11) || (accX >=  -6.0 && accX <= -0.5) || accX >= 2 ) && caindo ) { // (millis() - começodaqueda) >= numero) {
    //Serial.println("objeto caiu");
    Blynk.virtualWrite(V10,1);
    Blynk.virtualWrite(V8, "objeto caiu");
    delay(2000);
    caindo = true;
    Blynk.virtualWrite(V8, "  ");
    Blynk.virtualWrite(V10,0);
    
  }
  

  if (NORMxyz >= 7.0 && NORMxyz <= 8.5 && caindo) {
    //Serial.println("objeto no chao ");
    Blynk.virtualWrite(V8, "MPU estabilizado");
    delay(2000);
    Blynk.virtualWrite(V8, "  ");
    limitedequeda = true;
    caindo = false;
  }
  

delay(50);
}






