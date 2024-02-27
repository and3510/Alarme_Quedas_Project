#define brusco 2
#define queda 5

// -> Bibliotecas:
#include <Wire.h>                          // Wire --> Biblioteca permite que você se comunique com dispositivos I2C/TWI.
#include <MPU6050.h>                       // MPU6050 --> Biblioteca com as funçoes dos eixos do componente MPU6050, como MPU-6050 6-axis accelerometer/gyroscope.


MPU6050 mpu;                            // defini MPU6050 como mpu para utilizar com as funçoes do componente.
bool limitedequeda = true;              // variavel pra confirmar o limite de queda.
bool caindo = false;                   // variavel para confirmar se o objeto esta caindo.
unsigned long comecodaqueda = 0;
const unsigned long numero = 1500;       // variavel constante usado para limite do tempo de queda.
extern volatile unsigned long timer0_millis;
// Setup -> Como vai começar o arduino
void setup() {        
  pinMode(queda,OUTPUT);
  digitalWrite(queda,0);
  pinMode(brusco,OUTPUT);    
  digitalWrite(brusco,0);         
  Serial.begin(9600);
  Wire.begin();                                   // Inicia a comunicaçao com os componentes
  mpu.initialize();                               // Inicia a analise dos eixos do mpu6050

  if (!mpu.testConnection()) {                    // Tentativa de conexao com o compoenente,ate conectar com mpu6050
    Serial.println("MPU6050 conexao falhou.");     
    while (1);
  }

}

void loop() {
  
  int16_t ax, ay, az;       
  int16_t gx, gy, gz;       

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);   
  
  float accX = (float)ax / 2048.0; 
  float accY = (float)ay / 2048.0;
  float accZ = (float)az / 2048.0;

  

  //float girX = atan2(-accY, accZ) * 180.0 / PI;
  //float girY = atan2(accX, sqrt(accY * accY + accZ * accZ)) * 180.0 / PI;
  //float girZ = atan2(accZ, sqrt(accX * accX + accY * accY)) * 180.0 / PI;

  //float girx = (float)gx / 65.5;
  //float giry = (float)gy / 65.5;
  //float girz = (float)gz / 65.5;

   //Serial.print("Aceleração X: ");
   //Serial.print(accX);
   //Serial.print("   Aceleração Y: ");
   //Serial.print(accY);
   //Serial.print("   Aceleração Z: ");
   //Serial.println(accZ);
   //Serial.print("   Girx: ");
   //Serial.print(girx);
   //Serial.print("   Giry: ");
   //Serial.print(giry);
   //Serial.print("   Girz: ");
   //Serial.println(girz);
   //Serial.print("   Angulo y : ");
   //Serial.print(pitch);
   //Serial.print("   Angulo z : ");
   //Serial.println(rott);
  

  // Norma dos eixos x, y e z do acelerometro:
  float NORMxyz = sqrt(accX * accX + accY * accY + accZ * accZ);

  //Serial.print("Norma :");
  //Serial.println(NORMxyz);


  //Blynk.virtualWrite(V1, NORMxyz);
  

  // Condiçoes para a detecçao de uma queda:
  if ((NORMxyz >= 12.0 || accX < -12.0 || (accX >=  -5.00 && (accZ >= -5.0 && (accZ >=5.0 && accY >= 1.3 )))  && (accX <= -0.2 || accX >= 1.5) && limitedequeda)) {
    comecodaqueda = millis();
    Serial.println("Movimentaçao brusca!");
    //Blynk.virtualWrite(V9,1);
    //Blynk.virtualWrite(V8, "Movimentaçao brusca!");
    digitalWrite(brusco,1);
    delay(1000);
    digitalWrite(brusco,0);
    caindo = true;

    //Blynk.virtualWrite(V8, "  ");
    //Blynk.virtualWrite(V9,0);
    limitedequeda = false;
    caindo = true;
          
    //Blynk.virtualWrite(V10,1);
    //Blynk.virtualWrite(V8, "objeto caiu");
    //delay(2000);
    //digitalWrite(queda,0)
    //caindo = true;
    //Blynk.virtualWrite(V8, "  ");
    //Blynk.virtualWrite(V10,0);
    //Serial.print("   Angulo y : ");
    //Serial.print(pitch1);
    //Serial.print("   Angulo z : ");
    //Serial.println(rott1);
    //Serial.println("Analisando");
    
  }
  else {
    caindo = false;
    limitedequeda= true;

  }

  if (( millis() - comecodaqueda) >= 4000 ){
  double pitch = atan(accX / sqrt(accY * accY + accZ * accZ)) * (180.0 / PI);
  double rott  = atan(accY / sqrt(accZ* accZ + accX * accX)) * (180.0 / PI);
  Serial.println(pitch);
  if (((pitch >= -56.0 && pitch <= 10) || (rott >= 55.0 && rott <= 80.0))) {
    Serial.println("objeto caiu");
    digitalWrite(queda,1);
    delay(500);
    digitalWrite(queda,0);
    limitedequeda = true;
    caindo = false;
    delay(1000);
    noInterrupts();
    timer0_millis = 0;
    interrupts();
    Serial.println(timer0_millis);
    

    
  }  
  else{
    Serial.println("OK");
    limitedequeda = true;
    caindo = false;
    noInterrupts();
    timer0_millis = 0;
    interrupts();
    Serial.println(timer0_millis);

    }
  }


delay(50);
}







