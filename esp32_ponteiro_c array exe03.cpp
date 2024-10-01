char frase[] = "Arduino é uma plataforma aberta para criação de projetos eletrônicos.";
char *ptr = &frase[0];  // Ponteiro para o início da string

void setup() {
  Serial.begin(9600);

  int count = 0;  // Contador para caracteres 'a'

  // Percorrer a string usando o ponteiro
  while (*ptr != '\0') {  // '\0' marca o fim da string
    if (*ptr == 'a') {
      count++;
    }
    ptr++;  // Avança para o próximo caractere
  }

  // Imprimir o número de ocorrências de 'a'
  Serial.print("Número de ocorrências de 'a': ");
  Serial.println(count);
}

void loop() {
  // Não é necessário código no loop para este exercício
}
