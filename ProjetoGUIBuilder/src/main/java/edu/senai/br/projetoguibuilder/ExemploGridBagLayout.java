/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package edu.senai.br.projetoguibuilder;

import javax.swing.*;
import java.awt.*;

public class ExemploGridBagLayout extends JFrame {
    private JPanel panel;
    private JLabel[] labels;
    private JTextField[] textFields;
    private JButton button;

    ExemploGridBagLayout() {
        panel = new JPanel(new GridBagLayout());
        labels = new JLabel[5];
        textFields = new JTextField[5];
        button = new JButton("Enviar");

        String[] fieldNames = {"Nome:", "Sobrenome:", "Idade:", "Endereço:", "Cidade:"};

        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);  // Adiciona margens
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.weighty = 0.0;

        // Configuração dos labels e textFields
        for (int i = 0; i < 5; i++) {
            labels[i] = new JLabel(fieldNames[i]);
            textFields[i] = new JTextField(10);

            gbc.gridx = i * 2;
            gbc.gridy = 0;
            gbc.weightx = 0.0;
            panel.add(labels[i], gbc);

            gbc.gridx = i * 2 + 1;
            gbc.weightx = 0.2;
            panel.add(textFields[i], gbc);
        }

        // Configuração do button
        gbc.gridx = 0;
        gbc.gridy = 1;
        gbc.gridwidth = 10;  // Span across all columns
        gbc.weightx = 1.0;
        gbc.weighty = 0.0;
        gbc.fill = GridBagConstraints.NONE;
        //gbc.fill = GridBagConstraints.HORIZONTAL;  // Preencher a largura

        gbc.anchor = GridBagConstraints.CENTER;
        panel.add(button, gbc);

        // Adiciona um componente "invisível" para preencher o espaço vertical extra
        gbc.gridy = 2;
        gbc.weighty = 1.0;
        gbc.fill = GridBagConstraints.BOTH;
        panel.add(Box.createVerticalGlue(), gbc);

        /*
        Classe Box para ajustar layouts
        */
        add(panel);

        // Configurações da janela
        setTitle("Formulário de Cadastro");
        setSize(800, 150);  // Increased width to accommodate all fields
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new ExemploGridBagLayout().setVisible(true));
    }
}

