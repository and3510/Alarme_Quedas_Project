#define som 13
#define button 3


// -> Bibliotecas:
#include <Wire.h>                          // Wire --> Biblioteca permite que você se comunique com dispositivos I2C/TWI.
#include <MPU6050.h>                       // MPU6050 --> Biblioteca com as funçoes dos eixos do componente MPU6050, como MPU-6050 6-axis accelerometer/gyroscope.


MPU6050 mpu;                            // defini MPU6050 como mpu para utilizar com as funçoes do componente.
byte valorBotao;
byte ValorBotaoAnterior;
bool ledLigado = false;
bool som1 = false;
bool button1 = false;
bool limitedequeda = true;              // variavel pra confirmar o limite de queda.
bool caindo = false;                    // variavel para confirmar se o objeto esta caindo.
//unsigned long começodaqueda = 0;        // variavel que vai ser utilizada para calcular o o tempo de queda.
//const unsigned long numero = 0;       // variavel constante usado para limite do tempo de queda.

// Setup -> Como vai começar o arduino
void setup() {    
  pinMode(button,INPUT_PULLUP);
  pinMode(button,1);
  pinMode(som,OUTPUT);    
  digitalWrite(som,0);         
  Serial.begin(9600);
  Wire.begin();                                   // Inicia a comunicaçao com os componentes
  mpu.initialize();                               // Inicia a analise dos eixos do mpu6050

  if (!mpu.testConnection()) {                    // Tentativa de conexao com o compoenente,ate conectar com mpu6050
    Serial.println("MPU6050 conexao falhou.");     
    while (1);
  }

}

void loop() {
  
  
  int16_t ax, ay, az;       // Variaveis para o acelerometro
  int16_t gx, gy, gz;       // Variaveis para o giroscopio

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);   // Colocando os eixos para cada variaveis corretamente 3 para aceleraçao e 3 para giroscopio
  
  // -> Divisao para conseguir valor exato do g dividindo os valores brutos dos eixos pela sensibilidade LSB/g escrita no datasheet:
  float accX = (float)ax / 2045.0; 
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
  //Blynk.virtualWrite(V5, accX);     
  //Blynk.virtualWrite(V6, accY);     
  //Blynk.virtualWrite(V7, accZ);     
  // Blynk.virtualWrite(V2, girx);     
  // Blynk.virtualWrite(V3, giry);    
  // Blynk.virtualWrite(V4, girz);     
  

  // Norma dos eixos x, y e z do acelerometro:
  float NORMxyz = sqrt(accX * accX + accY * accY + accZ * accZ);

  Serial.print("Norma :");
  Serial.println(NORMxyz);


  //Blynk.virtualWrite(V1, NORMxyz);
  

  // Condiçoes para a detecçao de uma queda:
  if ((NORMxyz >= 13.0 || accX < -12.0 || ((accX >=  -5.00 && (accZ >= -5.0 && accZ >=5.0 ))  && accX <= -0.2) || accX >= 1.5 ) && limitedequeda) {
    Serial.println("Movimentaçao brusca!");
    //Blynk.virtualWrite(V9,1);
    //Blynk.virtualWrite(V8, "Movimentaçao brusca!");
    delay(2000);
    digitalWrite(som,1);
    som1 = true;
    //Blynk.virtualWrite(V8, "  ");
    //Blynk.virtualWrite(V9,0);
    limitedequeda = false;
    caindo = true;
    button1 = true;
    // começodaqueda = millis();     // a funçao millis() inicia um cronometro apartir do valor da variavel começodaqueda que é 0
  }

  while (som1 == true) {
  millis();
  int buttonVal = digitalRead(button);
  Serial.println(buttonVal);

  if (buttonVal = 0 && millis() >= 500) {
    Serial.println("Botão pressionado");
    if (buttonVal) {
      ledLigado = !ledLigado;
    }
    
    if (button1 && caindo) {
      Serial.println("MPU estabilizado");
      digitalWrite(som, LOW);  // Desliga o som (supondo que LOW desliga)
      som1 = false;
      button1 = false;
      buttonVal = true;
      //Blynk.virtualWrite(V8, "MPU estabilizado");
      delay(2000);
      //Blynk.virtualWrite(V8, "  ");
      limitedequeda = true;
      caindo = false;
      break;
    }

  } else {
    Serial.println("Botão não pressionado");
    
    // Aqui você pode adicionar lógica para ligar o som, se necessário
  }
delay(1000);
}
      
    
    
      

     
      
    


    //if ( ((accZ <= -5.0 || accZ >= 9) || (accX <= -11) || (accX >=  -6.0 && accX <= -0.5) || accX >= 2 ) && caindo ) { // (millis() - começodaqueda) >= numero) {
      //Serial.println("objeto caiu");
      //Blynk.virtualWrite(V10,1);
      //Blynk.virtualWrite(V8, "objeto caiu");
      //delay(2000);
      //caindo = true;
      //Blynk.virtualWrite(V8, "  ");
      //Blynk.virtualWrite(V10,0);
      
    //}
  


  
delay(50);
}






