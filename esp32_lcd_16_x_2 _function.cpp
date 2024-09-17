/*
 * Programa de Teste Abrangente para Display LCD I2C
 * 
 * Descrição:
 * Este programa demonstra várias funcionalidades de um display LCD 16x2 com interface I2C,
 * incluindo impressão de texto, efeitos visuais e manipulação de cursor.
 * 
 * Hardware:
 * - ESP32 (ou Arduino compatível)
 * - Display LCD 16x2 com interface I2C (endereço padrão: 0x27)
 * 
 * Conexões:
 * - SDA: GPIO 22
 * - SCL: GPIO 23
 * 
 * Funções:
 * - Hello(): Exibe uma mensagem de boas-vindas no display
 * - Flash(): Demonstra o ligar/desligar do display
 * - Blink(): Demonstra o piscar do cursor
 * - AutoScroll(): Demonstra a funcionalidade de rolagem automática do texto
 * - dirText(): Demonstra a mudança de direção do texto (esquerda para direita e vice-versa)
 * 
 * Bibliotecas necessárias:
 * - Wire.h (incluída no Arduino IDE)
 * - LiquidCrystal_I2C.h (https://github.com/johnrickman/LiquidCrystal_I2C)
 * 
 * Notas:
 * - Este código foi originalmente criado por Gustavo Murta (11/abril/2018) para o Blog Eletrogate
 * - Adaptado e expandido por Giovanni Rozza
 * 
 * Última atualização: 16.09.2024
 */


#include <LiquidCrystal_I2C.h>


// Uso de cristal liquido 16x2 com a interface I2C
// 0x27 endereço I2C do display
// 16 colunas, 02 linhas
LiquidCrystal_I2C lcd(0x27, 16, 2); // definindo o LCD - 16 colunas e 2 linhas

int thisChar = 0 ; 

void setup()
{
  Wire.begin(22, 23); // SDA 22 e SCL 23              
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

}

void Hello ()                     // imprimindo mensagem
{
  Serial.println("Hello!");  
  lcd.setCursor(0, 0);            // selecionando coluna 0 e linha 0
  lcd.print("Blog ELETROGATE");   // print da mensagem
  lcd.setCursor(2, 1);            // selecionando coluna 2 e linha 1
  lcd.print("Guia do LCD");       // Print da mensagem
  delay(1000);                    // atraso de 1 segundo
}

void Flash ()
{
  Serial.println("Flashing display");  
  lcd.noDisplay();                // desliga display
  delay(1000);                    // atraso de meio segundo
  lcd.display();                  // liga display
  delay(1000);                    // atraso de meio segundo
  lcd.clear();                    // limpa a tela
  delay(1000);                    // atraso de 1 segundo
}

void Blink ()                     // teste do cursor
{
  Serial.println("Blinking display");  
  lcd.noBlink();                  // apaga cursor
  delay(1000);                    // atraso de 1 segundo
  lcd.blink();                    // acende cursor
  delay(1000);                    // atraso de 1 segundo
  lcd.clear();                    // limpa a tela
  delay(1000);                    // atraso de 1 segundo
}

void AutoScroll ()                // teste de rolagem de mensagem
{
  
Serial.println("Rolagem Automática");
  lcd.clear();  // Limpa o display antes de começar 
  // Configuração para autoscroll
  lcd.setCursor(0, 1);  // Move para a segunda linha
  lcd.autoscroll();  // Ativa o autoscroll

  // Imprime caracteres com autoscroll
  for (thisChar = 0; thisChar < 10; thisChar++)
  {
    lcd.print(thisChar);
    delay(500);  // Aumento do delay para melhor visualização
  }

  lcd.noAutoscroll();  // Desativa o autoscroll
  delay(1000);  // Pausa para visualizar o resultado final
}

void dirText ()                   // teste de direcao de mensagem
{
    Serial.println("Direção da mensagem");  
  lcd.clear();                    // limpa a tela
  lcd.cursor();                   // liga o cursor
  lcd.setCursor(10, 0);           // selecionando coluna 10 e linha 1
  for (thisChar = 1; thisChar < 10; thisChar++)     // imprime de 1 a 9
  {
    lcd.rightToLeft();            // imprime da direita para a esquerda
    lcd.print(thisChar);          // imprime o numero
    delay(350);                   // atraso de 350 ms
  }
  for (thisChar = 1; thisChar < 10; thisChar++)     // imprime de 1 a 9
  {
    lcd.leftToRight();            // imprime da esquerda para a direita
    lcd.print(thisChar);          // imprime o numero
    delay(350);                   // atraso de 350 ms
  }
  lcd.noCursor();                 // desliga o cursor
}

void loop()
{
  Hello ();         // imprimindo mensagem
  Flash ();         // piscando a mensagem
  Blink ();         // teste do cursor
  AutoScroll ();    // teste de rolagem de mensagem
  dirText ();       // teste de direcao de mensagem
  delay(1000);      // atraso de 1 segundo
}