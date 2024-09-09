
/*
 * Projeto: Busca Binária com Geração de Valores Não Uniformes
 * Autor: Giovanni Rozza
 * 
 * Descrição:
 * Este código implementa um algoritmo de busca binária em um array de números 
 * reais gerados de forma não uniforme. O array possui TAMANHO_ARRAY elementos ordenados 
 * e é preenchido com valores gerados a partir de uma função logarítmica, garantindo 
 * que os valores sejam únicos e com duas casas decimais. A busca binária é aplicada 
 * para encontrar um valor específico no array e o tempo de execução do algoritmo 
 * é calculado.
 * 
 * Funções:
 * - gerarNumeroNaoUniforme(int i): Gera um número real distribuído de forma não 
 *   uniforme a partir do índice `i`, arredondando o valor para 2 casas decimais.
 * 
 * - binarySearch(double arr[], int size, double target): Realiza uma busca binária 
 *   em um array ordenado de números reais. Retorna o índice onde o valor `target` 
 *   foi encontrado, ou -1 se o valor não estiver presente no array.
 * 
 * - setup(): Inicializa a comunicação serial, gera o array de 4000 números não 
 *   uniformes, e executa a busca binária para um valor alvo, imprimindo o índice 
 *   encontrado e o tempo de execução da busca.
 * 
 * - loop(): Não utilizado neste projeto.
 * 
 * Componentes:
 * - Arduino (qualquer placa compatível)
 * - Interface Serial para monitorar o resultado da busca e o tempo de execução.
 * 
 * Instruções:
 * - Suba o código no Arduino.
 * - O resultado da busca e o tempo de execução serão exibidos no monitor serial.
 * 
 * Observações:
 * - O valor alvo pode ser ajustado diretamente no código.
 * - O array gerado é impresso e comparado com precisão de 2 casas decimais, 
 *   portanto, não haverá discrepância durante a busca binária, já que todos os 
 *   valores no array e o valor alvo são arredondados para essa mesma precisão.
 * 
 */

#include <Arduino.h>
#define TAMANHO_ARRAY 4000

double gerarNumeroNaoUniforme(int i);
int binarySearch(int arr[], int size, double target);
void setup();
void loop();
double myArray[TAMANHO_ARRAY] ;

void setup() {
  Serial.begin(115200);
 
  int size = sizeof(myArray) / sizeof(myArray[0]);
  double previousValue = -1.0;

  // Gera os TAMANHO_ARRAY números com uma distribuição não uniforme e única, com 2 casas decimais
  for (int i = 0; i < size; i++) {
    double value = gerarNumeroNaoUniforme(i);

    // Se o valor gerado for igual ou menor ao anterior, incrementa até que seja único
    if (value <= previousValue) {
      value = previousValue + 0.01; // Incrementa em 0.01 para garantir unicidade
    }

    myArray[i] = value;
    previousValue = value; // Atualiza o valor anterior
  }

  //double target = myArray[300];   // escolho como alvo array na posição i=300;
  double target = 57104.27;  //valor encontrado no indice 300
  
  // Imprime o array gerado com 2 casas decimais
  for (int i = 0; i < size; i++) {
    Serial.println(myArray[i], 8); // Imprime com 2 casas decimais
  }

  // Captura o tempo antes de executar o algoritmo
  unsigned long startTime = micros();
  
  int result = binarySearch(myArray, size, target);
  
  // Captura o tempo após a execução do algoritmo
  unsigned long endTime = micros();

  // Calcula o tempo de execução
  unsigned long executionTime = endTime - startTime;

  Serial.print("Tempo de execução em microssegundos :");
  Serial.println(executionTime);

  Serial.print("Valor encontrado em myArray[300] :");
  Serial.println(myArray[300] );

  if (result != -1) {
    Serial.print("Valor encontrado no índice ");
    Serial.print(result);
    Serial.print(" : ");
    Serial.println(myArray[result]);
  } else {
    Serial.println("Elemento não encontrado");
  }
  double d1 = 57104.27017375;
  double d2 = 57104.27;
  
  Serial.print("d1 ");  
  Serial.println(d1,8);
  Serial.print("d2 ");  
  Serial.println(d2,8);
}

void loop() {
  // Não precisa de implementação no loop
} 

int binarySearch(double arr[], int size, double target) {
  int left = 0;
  int right = size - 1;
  Serial.print("Tamanho array :");
  Serial.println(size);
  Serial.print("Target :");
  Serial.println(target);
  

  while (left <= right) {
    int mid = left + (right - left) / 2;

    // Verifica se o target está no meio
    if (arr[mid] == target) {

      Serial.print("mid :");
      Serial.println(mid);
      Serial.print("arr[mid] :");
      Serial.println(arr[mid],10);
      Serial.print("target :");
      Serial.println(target,10);
      return mid;
    }

    // Se o target for maior, ignore a metade esquerda
    if (arr[mid] < target) {
      left = mid + 1;
    }
    // Se o target for menor, ignore a metade direita
    else {
      right = mid - 1;
    }
  }

  return -1;  // Retorna -1 se o elemento não for encontrado
}

 // Função personalizada que gera um número distribuído de forma não uniforme com 2 casas decimais
double gerarNumeroNaoUniforme(int i) {

  double escala = 10000.0; // Ajuste a escala para controlar a distribuição
  double valor = escala * log(2 + i);
  //valor = round(valor * 100.0) / 100.0;

  return valor;
}