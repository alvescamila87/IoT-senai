
float preco = 10.90;
float *ptr = &preco;

void setup() {  
  Serial.begin(9600);

  Serial.print("Valor de preço: ");
  Serial.println(preco);

  Serial.print("Valor de preço através do ponteiro: ");
  Serial.println(*ptr);

  *ptr = 99.99;
  Serial.print("Novo valor de preço: ");
  Serial.println(preco);
}

void loop() {
  // Código principal repetido (vazio neste exemplo)
}
