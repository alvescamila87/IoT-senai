#define PORTA_ANALOGICA 35 // NÃO ESQUEÇA DE MUDAR SE USAR OUTRA PORTA
// EM SEU PROJETO!!
#define QUANTIDADE_AMOSTRAS 100 // NÚMERO LEITURA PARA FAZER A MÉDIA

void setup() {
// Initialize the serial communication
Serial.begin(115200);
analogReadResolution(10); // seta resolução conversor AD para 10 bits
}

void loop() {
int analogValue=0;
int i=0;
int somaAnalogValue=0;

for (i = 0; i < 99; i++)
{
// Read the analog value from GPIO 35 0...1023
analogValue = analogRead(PORTA_ANALOGICA);
somaAnalogValue += analogValue; // soma valores
delay(10);
}

analogValue = somaAnalogValue/QUANTIDADE_AMOSTRAS; // valor médio
Serial.print("Valor médio obtido: ");
Serial.println(analogValue);
// Add a delay to slow down the output in the Serial Monitor

// valor NTU

int NTU = (int) analogValue*analogValue*(-0.014287) + analogValue*4.6439 + 3000;
Serial.print("Valor em NTU: ");
Serial.println(NTU);
delay(1500);
}