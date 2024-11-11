package edu.senai.br.projetoguibuilder;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class DadosQualidadeAguaOficialGBLayout extends JFrame {

    // Caixas de texto
    private JTextField temperaturaField;
    private JTextField distanciaField;
    private JTextField turbidezField;

    public DadosQualidadeAguaOficialGBLayout() {
        // Configurações da janela
        setTitle("Dados qualidade da água");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setMinimumSize(new Dimension(500, 200)); 
        setResizable(false);
        setLocationRelativeTo(null); // Centralizar a janela

        // Painel principal com GridBagLayout
        JPanel mainPanel = new JPanel(new GridBagLayout());
        mainPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20)); // Margem de 20px

        // Constraints do GridBagLayout
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.fill = GridBagConstraints.HORIZONTAL;  // Expandir componentes horizontalmente
        gbc.insets = new Insets(5, 5, 5, 5);  // Espaçamento entre os componentes

        // Ajustar tamanho da fonte
        Font labelFont = new Font("Arial", Font.PLAIN, 16);
        Font buttonFont = new Font("Arial", Font.BOLD, 14);
        Font textFieldFont = new Font("Arial", Font.PLAIN, 14);

        // Primeira linha: Temperatura
        JLabel temperaturaLabel = new JLabel("Temperatura:");
        temperaturaLabel.setFont(labelFont);
        temperaturaField = new JTextField("25.5", 8);
        temperaturaField.setFont(textFieldFont);
        
        JButton historicoTemperaturaBtn = new JButton("Histórico");
        historicoTemperaturaBtn.setFont(buttonFont);
        historicoTemperaturaBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                criarHistorico();
            }
        });

        // Adicionar componentes da linha Temperatura
        gbc.gridx = 0; // Coluna 0
        gbc.gridy = 0; // Linha 0
        mainPanel.add(temperaturaLabel, gbc);

        gbc.gridx = 1; // Coluna 1
        mainPanel.add(temperaturaField, gbc);

        gbc.gridx = 2; // Coluna 2
        mainPanel.add(historicoTemperaturaBtn, gbc);

        // Segunda linha: Distância
        JLabel distanciaLabel = new JLabel("Distância:");
        distanciaLabel.setFont(labelFont);
        distanciaField = new JTextField("100", 8);
        distanciaField.setFont(textFieldFont);

        JButton historicoDistanciaBtn = new JButton("Histórico");
        historicoDistanciaBtn.setFont(buttonFont);
        historicoDistanciaBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                criarHistorico();
            }
        });

        // Adicionar componentes da linha Distância
        gbc.gridx = 0;
        gbc.gridy = 1;
        mainPanel.add(distanciaLabel, gbc);

        gbc.gridx = 1;
        mainPanel.add(distanciaField, gbc);

        gbc.gridx = 2;
        mainPanel.add(historicoDistanciaBtn, gbc);

        // Terceira linha: Turbidez
        JLabel turbidezLabel = new JLabel("Turbidez:");
        turbidezLabel.setFont(labelFont);
        turbidezField = new JTextField("50", 8);
        turbidezField.setFont(textFieldFont);

        JButton historicoTurbidezBtn = new JButton("Histórico");
        historicoTurbidezBtn.setFont(buttonFont);
        historicoTurbidezBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                criarHistorico();
            }
        });

        // Adicionar componentes da linha Turbidez
        gbc.gridx = 0;
        gbc.gridy = 2;
        mainPanel.add(turbidezLabel, gbc);

        gbc.gridx = 1;
        mainPanel.add(turbidezField, gbc);

        gbc.gridx = 2;
        mainPanel.add(historicoTurbidezBtn, gbc);

        // Quarta linha: Botão Conectar
        JButton conectarBtn = new JButton("Conectar");
        conectarBtn.setFont(buttonFont);
        conectarBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Conectar();
            }
        });

        // O botão Conectar deve estar centralizado
        gbc.gridx = 0;
        gbc.gridy = 3;
        gbc.gridwidth = 3;  // O botão ocupará 3 colunas
        gbc.anchor = GridBagConstraints.CENTER;  // Centralizar o botão
        mainPanel.add(conectarBtn, gbc);

        // Adicionar o painel ao frame
        add(mainPanel);

        pack(); // Ajustar o frame ao conteúdo
    }

    // Função associada aos botões Histórico
    private void criarHistorico() {
        JOptionPane.showMessageDialog(this, "Exibindo histórico...");
    }

    // Função associada ao botão Conectar
    private void Conectar() {
        JOptionPane.showMessageDialog(this, "Conectado ao sistema!");
    }

    public static void main(String[] args) {
        // Criando e exibindo a janela
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new DadosQualidadeAguaOficialGBLayout().setVisible(true);
            }
        });
    }
}
