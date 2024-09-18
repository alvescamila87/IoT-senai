
const int PINO_TRIG = 4; // Pino D4 conectado ao TRIG do HC-SR04
const int PINO_ECHO = 2; // Pino D2 conectado ao ECHO do HC-SR047
//INCLUSÃO DO LED
const int PINO_LED = 5; // Pino D5 conectado ao LED

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
  float distancia = (duracao * 0.0343) / 2;// Calcula a distância usando a velocidade do som (aproximadamente 343 m/s)
  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.println(" cm");
  
  if (distancia <= 10) // quando estiver menor ou igual a 10 cm enviará um alerta. ** Valor editável para a distância preferir.
  {
    digitalWrite(PINO_LED, HIGH); // Acende o LED se a distância for menor ou igual a 10 cm
  } else {
    digitalWrite(PINO_LED, LOW);  // Desliga o LED caso contrário
  }
  
  delay(1000); // Aguarda 1 segundo antes de fazer a próxima leitura
}