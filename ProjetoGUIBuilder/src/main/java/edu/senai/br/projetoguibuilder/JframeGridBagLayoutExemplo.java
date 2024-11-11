package edu.senai.br.projetoguibuilder;

import javax.swing.*;
import java.awt.*;

public class JframeGridBagLayoutExemplo extends JFrame {
    private JPanel panel;
    private JLabel label;
    private JTextField textField;
    private JButton button;

    JframeGridBagLayoutExemplo() {
        panel = new JPanel(new GridBagLayout());
        label = new JLabel("Nome:");
        textField = new JTextField(15);
        button = new JButton("Enviar");

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);  // Adiciona margens
        gbc.fill = GridBagConstraints.HORIZONTAL;

        // Configuração do label
        gbc.gridx = 0;
        gbc.gridy = 0;
        panel.add(label, gbc);

        // Configuração do textField
        gbc.gridx = 1;
        gbc.gridy = 0;
        gbc.weightx = 1.0;
        panel.add(textField, gbc);

        // Configuração do button
        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.gridwidth = 2;
        gbc.weightx = 0;
        panel.add(button, gbc);

        add(panel);

        // Configurações da janela
        setTitle("Minha Janela com GridBagLayout");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new JframeGridBagLayoutExemplo().setVisible(true));
    }
}