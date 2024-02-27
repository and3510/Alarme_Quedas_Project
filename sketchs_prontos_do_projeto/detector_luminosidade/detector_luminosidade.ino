#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Mude os valores caso precisem ser diferentes
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int pinoLDR = A0; // Pino analógico A0 para o sensor LDR
const int pinoLED = 13; // Pino digital 13 para o LED
const int pinoBUZZ = 7;



void setup() {
  // Inicializa a comunicação serial
  Serial.begin(9600);

  // Define o pino do LED como saída
  pinMode(pinoLED, OUTPUT);
  pinMode(pinoBUZZ, OUTPUT);

  lcd.init();
  lcd.backlight();
}

void loop() {
  lcd.clear();
  lcd.print("- A -");
  lcd.setCursor(0,1);
  lcd.print("fim do setup()" );
  // Lê o valor analógico do sensor LDR
  int valorLDR = analogRead(pinoLDR);

  // Imprime o valor lido na porta serial
  Serial.print("Valor LDR: ");
  Serial.println(valorLDR);

  // Se o valor lido for menor que 500, acende o LED
  if (valorLDR < 60) {
    digitalWrite(pinoLED, LOW);
    digitalWrite(pinoBUZZ, HIGH);
    
  } else {
    // Se o valor lido for maior ou igual a 500, apaga o LED
    digitalWrite(pinoLED, HIGH);
    digitalWrite(pinoBUZZ, LOW);
  }

  // Aguarda 100 milissegundos antes de repetir o loop
  delay(100);
}