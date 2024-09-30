int num = 25; // variavel normal
int *ptr = &num; //Ponteiro para 'num'

void setup() {
  Serial.begin(9600);

  Serial.print("Valor de num: ");
  Serial.println(num); //Imprime o valor direto

  Serial.print("Valor através do ponteiro: ");
  Serial.println(*ptr); //Imprime o valor através do ponteiro

  *ptr = 50; // Modifica o valor de 'num' através do ponteiro
  Serial.print("Novo valor de num: ");
  Serial.println(num); // Imprime o novo valor de 'num'

  Serial.print("Endereço de memória de via ptr: ");
  Serial.println((uintptr_t)ptr,HEX);

  Serial.print("Endereço de memória de num: ");
  Serial.println((uintptr_t)&num,HEX);
}

void loop() {
}
