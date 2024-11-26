package edu.senai.br.projetosaiot;

import org.eclipse.paho.client.mqttv3.*;
import org.json.JSONObject;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import org.json.JSONArray;
import org.json.JSONException;

/**
 * PROJETO SENAI/SC S.A: IoT Sensores
 * 
 * Objetivo:
 * O objetivo é fornecer uma solução para monitoramento remoto da qualidade da água, 
 * coletando dados de diferentes sensores e transmitindo-os em tempo real.
 * 
 * Classe principal do aplicativo ProjetoSaIoT. 
 * Este aplicativo se conecta a um broker MQTT, inscreve-se em um tópico para receber dados de sensores 
 * (como distância, temperatura e turbidez), e fornece uma interface gráfica para exibir os dados dos sensores. 
 * Também permite salvar os dados recebidos em um banco de dados quando um botão é pressionado.
 * 
 * @autores Camila Alves, Davi Galvão, João C. Emídio
 * Data de criação: 26/11/2024
 */
public class ProjetoSaIoT {

    private static final String BROKER_URL = "tcp://localhost:1883";
    //private static final String BROKER_URL = "tcp://test.mosquitto.org:1883"; // Broker Mosquitto público  
    //private static final String BROKER_URL = "tcp://broker.hivemq.com"; // Broker 
    private static final String CLIENT_ID = "JavaGUIClient";
    private static final String TOPIC = "le_dados_qualidade_agua";
    private JFrame frame;
    private MqttClient mqttClient;
    private JTextField distanciaField;
    private JTextField temperaturaField;
    private JTextField turbidezField;
    private JTextField dataColetaField;
    private JButton button;
    private boolean isActivate;

    /**
     * Construtor que inicializa a interface gráfica (GUI) e configura o cliente MQTT.
     */
    public ProjetoSaIoT() {
        createGUI();
        setupMQTTClient();
    }

     /**
     * Verifica se o botão foi ativado e salva os dados no banco de dados se ativado.
     */
    private void checkButton() {        
        if (!isActivate) {
            System.out.println("Não salva no banco de dados");
            return;
        }

        try (Connection connection = ConexaoDB.getConnection()) {
            if (connection != null) {
                // Recupera os dados dos campos de entrada
                String dataColeta = dataColetaField.getText().trim();
                String distancia = distanciaField.getText().trim();
                String temperatura = temperaturaField.getText().trim();
                String turbidez = turbidezField.getText().trim();

                // Se algum campo estiver vazio, não salva
                if (distancia.isEmpty()) {}
                if (temperatura.isEmpty()) {}
                if (turbidez.isEmpty()) {}
                if (dataColeta.isEmpty()) {}
                
                // Consulta SQL para inserir dados
                String sql = "INSERT INTO coleta (dataColeta, distancia, temperatura, turbidez) VALUES (?, ?, ?, ?)";

                try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                    preparedStatement.setString(1, dataColeta);
                    preparedStatement.setString(2, distancia);
                    preparedStatement.setString(3, temperatura);
                    preparedStatement.setString(4, turbidez);
                    preparedStatement.executeUpdate();

                    System.out.println("Dados inseridos no banco.");
                } catch (SQLException ex) {
                    System.out.println("Erro ao conectar ao banco: " + ex.getMessage());
                }
            } else {
                System.out.println("Não foi possível conectar ao banco de dados.");
            }
        } catch (SQLException ex) {
            System.out.println("Erro ao conectar ao banco: " + ex.getMessage());
        }

    }

    /**
     * Cria e exibe a interface gráfica (GUI) do aplicativo.
     * A GUI contém campos de texto para exibir os dados dos sensores e um botão para iniciar a coleta de dados.
     */
    private void createGUI() {
        frame = new JFrame("MQTT Sensor Data");
        frame.setLayout(new GridBagLayout());

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);

        // DISTÂNCIA
        JLabel distanciaLabel = new JLabel("Distância (cm):");
        distanciaField = new JTextField(15);
        distanciaField.setEditable(false);

        // Adiciona o label distância
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.weightx = 1.0;
        frame.add(distanciaLabel, gbc);

        // Adiciona o text field distância
        gbc.gridx = 1;
        gbc.gridy = 0;
        gbc.weightx = 1;
        frame.add(distanciaField, gbc);

        //TEMPERATURA
        JLabel temperaturaLabel = new JLabel("Temperatura (ºC):");
        temperaturaField = new JTextField(15);
        temperaturaField.setEditable(false);

        // Adiciona o label temperatura
        gbc.gridx = 0;
        gbc.gridy = 3;
        gbc.weightx = 1;
        frame.add(temperaturaLabel, gbc);

        // Adiciona o text field temperatura
        gbc.gridx = 1;
        gbc.gridy = 3;
        gbc.weightx = 1;
        frame.add(temperaturaField, gbc);

        //TURBIDEZ
        JLabel turbidezLabel = new JLabel("Turbidez (uT):");
        turbidezField = new JTextField(15);
        turbidezField.setEditable(false);

        // Adiciona o label turbidez
        gbc.gridx = 0;
        gbc.gridy = 4;
        gbc.weightx = 1;
        frame.add(turbidezLabel, gbc);

        // Adiciona o text field turbidez
        gbc.gridx = 1;
        gbc.gridy = 4;
        gbc.weightx = 1;
        frame.add(turbidezField, gbc);

        //TIMESTAMP: DATA COLETA
        JLabel dataColetaLabel = new JLabel("Coletado em:");
        dataColetaField = new JTextField(15);
        dataColetaField.setEditable(false);

        // Adiciona o label timestamp
        gbc.gridx = 0;
        gbc.gridy = 5;
        gbc.weightx = 1;
        frame.add(dataColetaLabel, gbc);

        // Adiciona o text field timestamp
        gbc.gridx = 1;
        gbc.gridy = 5;
        gbc.weightx = 1;
        frame.add(dataColetaField, gbc);

        frame.setSize(500, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);

        // Botão para iniciar coleta
        button = new JButton("Coletar dados");

        // Adiciona o ActionListener ao botão;
        button.addActionListener((ActionEvent e) -> {
           isActivate = true;
        });

        // Configuração do botão
        gbc.gridx = 1;
        gbc.gridy = 6;
        gbc.gridwidth = 0;
        gbc.weightx = 1;
        frame.add(button, gbc);
    }

    /**
     * Configura o cliente MQTT para se conectar ao broker e se inscrever no tópico.
     * Quando os dados são recebidos, eles são processados e os respectivos campos são atualizados.
     */
    private void setupMQTTClient() {
        try {
            mqttClient = new MqttClient(BROKER_URL, CLIENT_ID);
            MqttConnectOptions connOpts = new MqttConnectOptions();
            connOpts.setCleanSession(true);
            connOpts.setAutomaticReconnect(true); // re-conexão automática
            connOpts.setKeepAliveInterval(30); // em segundos, ajuste conforme o necessário

            System.out.println("Connecting to broker: " + BROKER_URL);
            mqttClient.connect(connOpts);
            System.out.println("Connected");

            mqttClient.subscribe(TOPIC, (topic, message) -> {
                try {
                    String msg = new String(message.getPayload());
                    System.out.println("Payload recebido: " + msg);

                    // Trate o payload como um JSONArray
                    JSONArray jsonArray = new JSONArray(msg);  

                    // Processa cada objeto JSON no array
                    for (int i = 0; i < jsonArray.length(); i++) {
                        JSONObject jsonObject = jsonArray.getJSONObject(i);

                        // Verifique se o objeto contém a chave "value"
                        if (jsonObject.has("variable") && jsonObject.getString("variable").equals("valor_distancia")) {
                            String valorDistancia = jsonObject.getString("value");
                            String timestamp = jsonObject.getString("timestamp");

                            // Atualize o campo `distanciaField` com o valor encontrado
                            SwingUtilities.invokeLater(() -> {
                                distanciaField.setText(valorDistancia);
                                dataColetaField.setText(timestamp);
                            });
                        } else if (jsonObject.has("variable") && jsonObject.getString("variable").equals("valor_temperatura")) {
                            String valorTemperatura = jsonObject.getString("value");

                            // Atualize o campo `distanciaField` com o valor encontrado
                            SwingUtilities.invokeLater(() -> {
                                temperaturaField.setText(valorTemperatura);
                            });
                        } else if (jsonObject.has("variable") && jsonObject.getString("variable").equals("valor_turbidez")) {
                            String valorTurbidez = jsonObject.getString("value");

                            // Atualize o campo `distanciaField` com o valor encontrado
                            SwingUtilities.invokeLater(() -> {
                                turbidezField.setText(valorTurbidez);
                                checkButton(); // checa se o botão de coleta foi pressionado. Se foi, salva no DB;
                            });
                        } else {
                            System.out.println("Objeto JSON sem a chave 'value': " + jsonObject);
                        }
                    }
                } catch (JSONException e) {
                    System.out.println("Erro ao processar o payload: " + e.getMessage());
                }
            });

        } catch (MqttException me) {
            System.out.println("reason " + me.getReasonCode());
            System.out.println("msg " + me.getMessage());
            System.out.println("localizated " + me.getLocalizedMessage());
            System.out.println("cause " + me.getCause());
            System.out.println("exception " + me);
            me.printStackTrace();
        }
    }

    /**
     * Método principal que inicializa o aplicativo.
     * @param args Argumentos da linha de comando (não usados neste caso).
     */
    public static void main(String[] args) {
        SwingUtilities.invokeLater(ProjetoSaIoT::new);
    }
}
