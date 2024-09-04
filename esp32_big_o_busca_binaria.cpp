#include <Arduino.h>
#define TAMANHO_ARRAY 12000

/**
 * @file binary_search_example.ino
 * @brief Implementação de uma busca binária em um array usando a plataforma Arduino.
 * 
 * Este código executa uma busca binária em um array pré-definido de 12000 elementos para encontrar
 * um valor alvo. O tempo de execução do algoritmo é calculado e exibido no console serial.
 * 
 * @author Giovanni Rozza
 * @date 10.08.2024
 */

/**
 * @brief Realiza uma busca binária em um array ordenado.
 * 
 * Esta função realiza a busca binária em um array previamente ordenado procurando um valor alvo.
 * Se o valor for encontrado, o índice do elemento é retornado. Caso contrário, a função retorna -1.
 * 
 * @param arr[] Array onde a busca será realizada (deve estar ordenado).
 * @param size Tamanho do array.
 * @param target Valor a ser buscado no array.
 * @return int Retorna o índice do elemento encontrado ou -1 se o elemento não for encontrado.
 */
int binarySearch(float arr[], int size, float target);
float myArray[TAMANHO_ARRAY];

/**
 * @brief Função de configuração do Arduino.
 * 
 * Esta função inicializa a comunicação serial, define um array de inteiros, gera números,
 * realiza a busca binária, calcula o tempo de execução e exibe os resultados no console serial.
 */
void setup();

/**
 * @brief Função principal do loop do Arduino.
 * 
 * Não há implementação necessária nesta função para este exemplo.
 */
void loop();

void setup() {
  Serial.begin(115200);
  
  int size = sizeof(myArray) / sizeof(myArray[0]);

  float previousValue = -1.0;

  // Gera os 12000 números com uma distribuição não uniforme e única, com 2 casas decimais
  for (int i = 0; i < size; i++) {
    float value = gerarNumeroNaoUniforme(i);

    // Se o valor gerado for igual ou menor ao anterior, incrementa até que seja único
    if (value <= previousValue) {
      value = previousValue + 0.01; // Incrementa em 0.01 para garantir unicidade
    }

    myArray[i] = value;
    previousValue = value; // Atualiza o valor anterior
  }

  // Imprime o array gerado com 2 casas decimais
  for (int i = 0; i < size; i++) {
    Serial.println(myArray[i], 2); // Imprime com 2 casas decimais
  }

  // Define o valor alvo para busca (um valor no final do array)
  float target = myArray[size-100];   

  // Captura o tempo antes de executar o algoritmo
  unsigned long startTime = micros();

  int result = binarySearch(myArray, size, target);

  // Captura o tempo após a execução do algoritmo
  unsigned long endTime = micros();

  // Calcula o tempo de execução
  unsigned long executionTime = endTime - startTime;

  Serial.print("Tempo de execução em microssegundos :");
  Serial.println(executionTime);

  if (result != -1) {
    Serial.print("Elemento encontrado no índice: ");
    Serial.println(result);
    Serial.print("Valor encontrado no índice ");
    Serial.print(result);
    Serial.print(" : ");
    Serial.println(myArray[result]);
  } else {
    Serial.println("Elemento não encontrado");
  }
   
}

void loop() {
  // Não precisa de implementação no loop
}

/**
 * @brief Função de busca binária.
 * 
 * Esta função realiza a busca binária em um array ordenado para encontrar o índice de um valor alvo.
 * 
 * @param arr[] Array onde a busca será realizada (deve estar ordenado).
 * @param size Tamanho do array.
 * @param target Valor a ser buscado no array.
 * @return int Retorna o índice do elemento encontrado ou -1 se o elemento não for encontrado.
 */
int binarySearch(float arr[], int size, float target) {
  int left = 0;
  int right = size - 1;

  while (left <= right) {
    int mid = left + (right - left) / 2;

    if (arr[mid] == target) {
      return mid; // Retorna o índice do elemento encontrado
    }
    if (arr[mid] < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  return -1; // Retorna -1 se o elemento não for encontrado
}

/**
 * @brief Função personalizada que gera um número distribuído de forma não uniforme com 2 casas decimais.
 * 
 * @param i Índice usado para gerar o número.
 * @return float Valor gerado.
 */
float gerarNumeroNaoUniforme(int i) {
  float escala = 10000.0; // Ajuste a escala para controlar a distribuição
  return (float)(escala * log(2 + i));
}
