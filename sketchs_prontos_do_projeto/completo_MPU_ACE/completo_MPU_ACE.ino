#define som 2                              // pino 2 declarado como "som"


#include <Wire.h>                          // Wire --> Biblioteca permite que você se comunique com dispositivos I2C/TWI.
#include <MPU6050.h>                       // MPU6050 --> Biblioteca com as funçoes dos eixos do componente MPU6050, como MPU-6050 6-axis accelerometer/gyroscope.


MPU6050 mpu;                            // defini MPU6050 como mpu para utilizar com as funçoes do componente.


bool estavel = true;              // variavel pra confirmar o limite de queda.
bool mov_brusco = false;                   // variavel para confirmar se o objeto esta mov_brusco.
unsigned long comecobrusco = 0;
const unsigned long tempo = 4000;       // variavel constante usado para limite do tempo de queda.

// Setup -> Como vai começar o arduino
void setup() {        
pinMode(som,OUTPUT);                            // Tipo de pino
digitalWrite(som,0);                            // Buzzer inicia desligado                            // leitura da porta serial
Wire.begin();                                   // Inicia a comunicaçao com os componentes
mpu.initialize();                               // Inicia a analise dos eixos do mpu6050

if (!mpu.testConnection()) {                    // Tentativa de conexao com o compoenente,ate conectar com mpu6050                                                      // Printar na porta Serial que a conexao falhou
    while (1);                                    // repetir a tentativa apos a nao conexao
}

}

void loop() {                                                       // funçao que repete enquanto o dipsoitivo estiver ligado
int16_t ax, ay, az;                                                                 // Criando variaveis int de 16 bits
int16_t gx, gy, gz;          

mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);                                       // receber os valores do MPU-6050 e colocar nas variaveis

float accX = (float)ax / 2048.0;                                                    //Aceleraçao X
float accY = (float)ay / 2048.0;                                                    //Aceleraçao Y
float accZ = (float)az / 2048.0;                                                     //Aceleraçao Z

float NORMxyz = sqrt(accX * accX + accY * accY + accZ * accZ);                        //Norma dos vetores

if (mov_brusco) {                                                                                                 // verificando se ocorreu um movimento brusco     
  if ((millis() - comecobrusco) >= tempo) {                                                 // Se o cronometro passar de 4 segundos
    double angulo_Y = atan(accX / sqrt(accY * accY + accZ * accZ)) * (180.0 / PI);                                  // angulo Y 
    double angulo_Z = atan(accY / sqrt(accZ * accZ + accX * accX)) * (180.0 / PI);                                  // angulo Z

    if ((angulo_Y >= -56.0 && angulo_Y <= 10) || (angulo_Z >= 55.0 && angulo_Z <= 80.0)) {                     // Se a condiçao de queda detecta                                                                                      
      digitalWrite(som,1);                                                                                      // ligar o buzzer por apenas 1000 milissegundos
      delay(1000);
      digitalWrite(som,0);
      
      mov_brusco = false;                                                                               // Colocar o mov_bruco para falso para proximo movimento brusco
      comecobrusco = 0;                                                                              // reniciar o cronometro
    }
    else {
      mov_brusco = false;                                                                           // Colocar o mov_bruco para falso para proximo movimento brusco
      comecobrusco = 0;                                                                                    // reniciar o cronometro
    }
  }
}
else {
  if ((NORMxyz >= 12.0 || accX < -12.0 || (accX >= -5.00 && (accZ >= -5.0 && (accZ >= 5.0 && accY >= 1.3))) && 
    (accX <= -0.2 || accX >= 1.5) && estavel)) { 
    comecobrusco = millis();                                                                                                                         // liga o cronometro                                                                                                          // Printar Movimentaçao brusca
    
    digitalWrite(som, 1);                                                                                                                                       // Ligar o buzzer por apenas 200 milissegundos
    delay(200);
    digitalWrite(som, 0);
    
    mov_brusco = true;                                                                                                                                          // Deixar verdadeiro o mov_brusco para a primeira condiçao começar a detecçao da queda
    estavel = false;                                                                                                                                      // Impedir que a condiçao detecçao de movimento brusco ocorra antes da ativaçao da condiçao mov_brusco
  }
    

}

delay(50);                                                                                // delay 50 milissegundos 
}
