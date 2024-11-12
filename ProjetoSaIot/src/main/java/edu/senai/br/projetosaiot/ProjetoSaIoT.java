package edu.senai.br.projetosaiot;

/**
 *
 * @author Giovanni L. Rozza
 * https://github.com/jfree/jfreechart 
 * https://eclipse.dev/paho/
 */
import org.eclipse.paho.client.mqttv3.*;
import org.json.JSONObject;
import javax.swing.*;
import java.awt.*;
import org.json.JSONArray;
import org.json.JSONException;

public class ProjetoSaIoT {

    private static final String BROKER_URL = "tcp://localhost:1883";
    //private static final String BROKER_URL = "tcp://test.mosquitto.org:1883"; // Broker Mosquitto público    
    private static final String CLIENT_ID = "JavaGUIClient";
    private static final String TOPIC = "le_dados_qualidade_agua";
    private JFrame frame;
    private MqttClient mqttClient;
    private JTextField distanciaField;
    private JTextField temperaturaField;
    private JTextField turbidezField;
    private JButton button;    

    public ProjetoSaIoT() {
        createGUI();
        setupMQTTClient();
    }

    private void createGUI() {
        frame = new JFrame("MQTT Sensor Data");
        frame.setLayout(new GridBagLayout());

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);

        // DISTÂNCIA
        JLabel distanciaLabel = new JLabel("Distância (cm):");
        distanciaField = new JTextField(10);
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
        temperaturaField = new JTextField(10);
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
        turbidezField = new JTextField(10);
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

        frame.setSize(600, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
        
        // Botão Iniciar coleta
        button = new JButton("Iniciar coleta");
        
        // Adiciona o ActionListener ao botão
    button.addActionListener((ActionEvent e) -> {
        // Cria a conexão com o banco de dados
        ConexaoDB conexaoDB = new ConexaoDB();
        Connection conn = conexaoDB.getConnection();
        
        // Verifica se a conexão foi bem-sucedida
        if (conn != null) {
            // Aqui você pode executar operações no banco, como inserir dados, fazer consultas, etc.
            System.out.println("Conexão com o banco estabelecida. Você pode realizar operações no banco.");

            // Exemplo de como você pode salvar os dados recebidos de MQTT no banco de dados:
            String distancia = distanciaField.getText();
            String temperatura = temperaturaField.getText();
            String turbidez = turbidezField.getText();

            // Exemplo simples de SQL (não segura, apenas para fins ilustrativos)
            String sql = "INSERT INTO dados_sensor (distancia, temperatura, turbidez) VALUES (?, ?, ?)";

            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, distancia);
                stmt.setString(2, temperatura);
                stmt.setString(3, turbidez);
                stmt.executeUpdate();
                System.out.println("Dados inseridos no banco.");
            } catch (SQLException ex) {
                System.out.println("Erro ao inserir dados: " + ex.getMessage());
            }

            // Fechar a conexão
            conexaoDB.closeConnection(conn);
        } else {
            System.out.println("Não foi possível conectar ao banco de dados.");
        }
    });
        
        // Configuração do botão
        gbc.gridx = 1;
        gbc.gridy = 5;
        gbc.gridwidth = 0;
        gbc.weightx = 1;
        frame.add(button, gbc);
    }

    private void setupMQTTClient() {
        try {
            mqttClient = new MqttClient(BROKER_URL, CLIENT_ID);
            MqttConnectOptions connOpts = new MqttConnectOptions();
            connOpts.setCleanSession(true);

            System.out.println("Connecting to broker: " + BROKER_URL);
            mqttClient.connect(connOpts);
            System.out.println("Connected");

            mqttClient.subscribe(TOPIC, (topic, message) -> {
                try {
                    String msg = new String(message.getPayload());
                    System.out.println("Payload recebido: " + msg);

                    JSONArray jsonArray = new JSONArray(msg);  // Trate o payload como um JSONArray

                    // Itere pelos objetos dentro do array
                    for (int i = 0; i < jsonArray.length(); i++) {
                        JSONObject jsonObject = jsonArray.getJSONObject(i);

                        // Verifique se o objeto contém a chave "value"
                        if (jsonObject.has("value")) {
                            String valor = jsonObject.getString("value");

                            // Atualize o campo `distanciaField` com o valor encontrado
                            SwingUtilities.invokeLater(() -> {
                                distanciaField.setText(valor);
                                temperaturaField.setText(valor);
                                turbidezField.setText(valor);
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

    public static void main(String[] args) {
        SwingUtilities.invokeLater(ProjetoSaIoT::new);
    }
}
