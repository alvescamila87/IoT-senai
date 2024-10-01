void setup() {
  // Inicializa a comunicação serial
  Serial.begin(9600);

  // Declaração de um array
  int arr[5] = {10, 20, 30, 40, 50};

  // Declarar um ponteiro para o array
  int *ptr = arr;  // ou int *ptr = &arr[0]; (ambas formas são equivalentes)

  // Acessando os elementos do array usando o ponteiro
  Serial.println("Acessando os elementos do array usando o ponteiro:");
  for (int i = 0; i < 5; i++) {
    Serial.print("Elemento ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(*(ptr + i));  // ptr + i aponta para arr[i]
  }

  // Modificando os elementos do array usando o ponteiro
  for (int i = 0; i < 5; i++) {
    *(ptr + i) += 5;  // Aumenta cada elemento em 5
  }

  // Imprimindo os valores modificados do array
  Serial.println("\nElementos do array após a modificação:");
  for (int i = 0; i < 5; i++) {
    Serial.print("Elemento ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(arr[i]);
  }
}

void loop() {
  // Código principal repetido (vazio neste exemplo)
}
