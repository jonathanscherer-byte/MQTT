// Arduino Uno - Controle de LED via MQTT
// Conecte um LED ao pino 13 com resistor de 220Ω

const int LED_PIN = 13;
String inputString = "";
boolean stringComplete = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(9600);
  Serial.println("Arduino pronto para receber comandos MQTT");
}

void loop() {
  // Verifica se há dados disponíveis na porta serial
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }

  // Processa o comando recebido
  if (stringComplete) {
    inputString.trim(); // Remove espaços e quebras de linha
    
    if (inputString == "1") {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED LIGADO");
    } 
    else if (inputString == "0") {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED DESLIGADO");
    }
    else if (inputString == "STATUS") {
      // Responde com o estado atual do LED
      if (digitalRead(LED_PIN) == HIGH) {
        Serial.println("1");
      } else {
        Serial.println("0");
      }
    }
    
    inputString = "";
    stringComplete = false;
  }
}