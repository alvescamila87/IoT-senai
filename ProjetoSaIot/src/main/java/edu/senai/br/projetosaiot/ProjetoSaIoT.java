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

    public ProjetoSaIoT() {
        createGUI();
        setupMQTTClient();
    }

    private void createGUI() {
        frame = new JFrame("MQTT Sensor Data");
        frame.setLayout(new GridBagLayout());

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);

        JLabel distanciaLabel = new JLabel("Distância (cm):");
        distanciaField = new JTextField(10);
        distanciaField.setEditable(false);

        // Adiciona o label
        gbc.gridx = 0;
        gbc.gridy = 0;
        frame.add(distanciaLabel, gbc);

        // Adiciona o text field
        gbc.gridx = 1;
        frame.add(distanciaField, gbc);

        frame.setSize(300, 100);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
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
            System.out.println("loc " + me.getLocalizedMessage());
            System.out.println("cause " + me.getCause());
            System.out.println("excep " + me);
            me.printStackTrace();
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(ProjetoSaIoT::new);
    }
}
