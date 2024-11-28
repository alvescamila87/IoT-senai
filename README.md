# PROJETO SA - IoT Sensores com ESP32

## Objetivo:
Este código é um sistema de monitoramento e envio de dados de sensores ambientais (temperatura, distância e turbidez) para um broker MQTT. 
Ele utiliza um ESP32 para se conectar a uma rede Wi-Fi, obter dados dos sensores e publicar os resultados em um tópico MQTT. 
O código é responsável por coletar dados de temperatura, distância e turbidez da água e enviar esses dados periodicamente a um broker MQTT.
Data de criação: 26/11/2024
 
### Classe principal do aplicativo ProjetoSaIoT. 
Este aplicativo se conecta a um broker MQTT, inscreve-se em um tópico para receber dados de sensores 
(como distância, temperatura e turbidez), e fornece uma interface gráfica para exibir os dados dos sensores. 
Também permite salvar os dados recebidos em um banco de dados quando um botão é pressionado.

## Links do projeto
* [Link 1 - Netbeans](https://github.com/alvescamila87/IoT-senai/tree/main/ProjetoSaIot)
* [Link 2 - Wokwi](https://github.com/alvescamila87/IoT-senai/blob/main/esp32_projeto_iot_sa_wokwi_documentado.cpp)

## Imagens:
* Prompt Java Swing FX:
  
![image](https://github.com/user-attachments/assets/cc205a9f-a05a-46b3-ae58-f145e9142c00)

* Sensores
  
![image](https://github.com/user-attachments/assets/8b6f26c2-4e7d-484b-bb1b-1bb8b0340679)
![image](https://github.com/user-attachments/assets/94acd593-a35b-4f16-b57d-e5eb424f7530)

* Netbeans
  
![image](https://github.com/user-attachments/assets/37ced9ac-6146-4287-aff4-df6254546ef6)

* MQTT Protocol:
  
![image](https://github.com/user-attachments/assets/4a21cf83-4604-4888-80bc-c9917f20acb0)

```json
// comando para enviar os 3 valores de uma vez

mosquitto_pub -h localhost -t le_dados_qualidade_agua -m "[{\"variable\":\"valor_distancia\",\"unit\":\"cm\",\"value\":\"234\",\"timestamp\":\"2024-11-11 20:28:29\"},{\"variable\":\"valor_temperatura\",\"unit\":\"graus celsius\",\"value\":\"234\",\"timestamp\":\"2024-11-11 20:28:29\"},{\"variable\":\"valor_turbidez\",\"unit\":\"NTU\",\"value\":\"234\",\"timestamp\":\"2024-11-11 20:28:29\"}]"

// comando para enviar somente distancia

mosquitto_pub -h localhost -t le_dados_qualidade_agua_cdj -m "[{\"variable\":\"valor_distancia\",\"unit\":\"cm\",\"value\":\"200\",\"timestamp\":\"2024-11-26 22:21:29\"}]"

// comando para enviar somente temperatura  

mosquitto_pub -h localhost -t le_dados_qualidade_agua_cdj -m "[{\"variable\":\"valor_temperatura\",\"unit\":\"oC\",\"value\":\"20.8\",\"timestamp\":\"2024-11-26 22:22:29\"}]"

// comando para enviar somente turbidez

mosquitto_pub -h localhost -t le_dados_qualidade_agua_cdj -m "[{\"variable\":\"valor_turbidez\",\"unit\":\"NTU\",\"value\":\"1077\",\"timestamp\":\"2024-11-26 22:23:29\"}]"
```

* Banco de dados:
  
![image](https://github.com/user-attachments/assets/681ad98d-0260-49f8-8442-015715989cbd)
![image](https://github.com/user-attachments/assets/fea72028-bd7e-4242-8461-1b7406d4051e)
![image](https://github.com/user-attachments/assets/a8ac979d-1a82-4634-a716-5ba4ad0144ea)
![image](https://github.com/user-attachments/assets/ec25017d-1e76-4619-a7c7-2fc82f67ffa3)
![image](https://github.com/user-attachments/assets/757018e2-1e9f-41d8-9c00-fc7268ebe218)

* VSCode:
  
![image](https://github.com/user-attachments/assets/1eff3e19-8b2b-4a42-9f71-351f677e3903)

* Arduino (ESP32)

![image](https://github.com/user-attachments/assets/94cdf279-98b4-45e2-a798-808712a73c38)



## Autores
* Camila Alves
* Davi Galvão
* João C. Emídio
