void setup() {  
  Serial.begin(9600);

  int arr[10] = {10, 20, 30, 40, 50};

  int *ptr = &arr[0];

  Serial.print("Acessando os elementos do array pelo ponteiro:");
  for(int i = 0; i < 5; i++){
    Serial.print("Elemento:");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(*(ptr + i));
  }

  for(int i; i < 5; i++){
    *(ptr + i) += 10;
  }

  Serial.println("\nImprimindo os valores do array pós modificação:");
  for(int i = 0; i < 5; i++){
    Serial.print("Elemento:");
    Serial.print(i);
    Serial.print(" = ");
    Serial.println(arr[i]);
  }
}

void loop() {
  // Código principal repetido (vazio neste exemplo)
}
