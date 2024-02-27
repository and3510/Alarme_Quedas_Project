const int botaoPin = 4; // Pino digital onde o botão está conectado
const int ledPin = 2;
const int som = 3;  // Pino digital onde o LED está conectado
const int ledPin2 = 5;
boolean estadoLED = false; // Variável para armazenar o estado do LED

void setup() {
  pinMode(botaoPin, INPUT_PULLUP); // Configura o pino do botão como entrada com pull-up interno
  pinMode(ledPin, OUTPUT);         // Configura o pino do LED como saída
  digitalWrite(ledPin, LOW);      // Desliga o LED inicialmente
  pinMode(som,OUTPUT);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin2, HIGH);
}

void loop() {
  int estadoBotao = digitalRead(botaoPin); // Lê o estado do botão (HIGH ou LOW)

  // Verifica se o botão foi pressionado
  if (estadoBotao == LOW) {
    // Inverte o estado do LED
    estadoLED = !estadoLED;
    if (estadoLED==true) {
      digitalWrite(ledPin,1);
      digitalWrite(som,1);
      digitalWrite(ledPin2,0);
      delay(250);}
    else {
      digitalWrite(ledPin,0);
      digitalWrite(som,0);
      digitalWrite(ledPin2,1);
      
      delay(250);
    }
    } // Liga ou desliga o LED com base no estado
    
  }
