const int PINO_TRIG = 4; // Pino D4 conectado ao TRIG do HC-SR04
const int PINO_ECHO = 2; // Pino D2 conectado ao ECHO do HC-SR04
const int PINO_LED = 5;  // Pino D5 conectado ao LED

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  pinMode(PINO_TRIG, OUTPUT); // Configura o pino TRIG como saída
  pinMode(PINO_ECHO, INPUT);  // Configura o pino ECHO como entrada
  pinMode(PINO_LED, OUTPUT);  // Configura o pino LED como saída
}

void loop() {
  digitalWrite(PINO_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PINO_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PINO_TRIG, LOW);
  
  long duracao = pulseIn(PINO_ECHO, HIGH); // Mede o tempo de resposta do ECHO
  float distancia = (duracao * 0.0343) / 2; // Calcula a distância usando a velocidade do som (aproximadamente 343 m/s)
  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Condições para fazer o LED piscar conforme a distância
  if (distancia <= 50 && distancia > 4) {
    // Mapeia a distância para o intervalo de piscar o LED
    // 4 cm -> 500 ms, 50 cm -> 100 ms
    int intervalo = map(distancia, 4, 50, 500, 100);
    
    // Pisca o LED
    digitalWrite(PINO_LED, HIGH); // Liga o LED
    delay(intervalo);
    digitalWrite(PINO_LED, LOW);  // Desliga o LED
    delay(intervalo);
    
  } else if (distancia <= 4) {
    // Liga o LED constante quando menor ou igual a 4 cm
    digitalWrite(PINO_LED, HIGH);
  } else {
    // Desliga o LED se for maior que 50 cm
    digitalWrite(PINO_LED, LOW);
  }

  delay(50); // Pequeno delay para evitar leituras muito rápidas
}
