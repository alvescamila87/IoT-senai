/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package edu.senai.br.projetoguibuilder;

/**
 *
 * @author Acer
 */
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class DadosQualidadeAguaOficialGrid extends JFrame {

    // Caixas de texto
    private JTextField temperaturaField;
    private JTextField distanciaField;
    private JTextField turbidezField;

    public DadosQualidadeAguaOficialGrid() {
        // Configurações da janela
        setTitle("Dados qualidade da água");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setMinimumSize(new Dimension(500, 200)); // Aumente a largura para 500px ou mais conforme necessário
        setResizable(false);
        //setSize(400, 200);
        setLocationRelativeTo(null); // Centralizar a janela

        // Definir margens com um JPanel adicional
        JPanel mainPanel = new JPanel(new GridLayout(4, 3, 5, 5)); // Grid 4 linhas e 3 colunas
        mainPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20)); // Margem de 20px em todas as direções

        // Ajustar tamanho da fonte (aumento de cerca de 30%)
        Font labelFont = new Font("Arial", Font.PLAIN, 16);  // Aumenta a fonte dos labels
        Font buttonFont = new Font("Arial", Font.BOLD, 14);  // Aumenta a fonte dos botões
        Font textFieldFont = new Font("Arial", Font.PLAIN, 14); // Aumente conforme necessário (14 é um exemplo)

        // Primeira linha: Temperatura
        JLabel temperaturaLabel = new JLabel("Temperatura:");
        temperaturaLabel.setFont(labelFont); // Definindo fonte maior
        temperaturaField = new JTextField("25.5", 8); // Campo de texto com largura ajustada
        temperaturaField.setFont(textFieldFont);
        temperaturaField.setPreferredSize(new Dimension(80, 20)); // Reduz altura e largura
        JButton historicoTemperaturaBtn = new JButton("Histórico");
        historicoTemperaturaBtn.setFont(buttonFont); // Aumentar fonte do botão
        historicoTemperaturaBtn.setPreferredSize(new Dimension(80, 20)); // Reduz altura e largura
        historicoTemperaturaBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                criarHistorico();
            }
        });

        mainPanel.add(temperaturaLabel);
        mainPanel.add(temperaturaField);
        mainPanel.add(historicoTemperaturaBtn);

        // Segunda linha: Distância
        JLabel distanciaLabel = new JLabel("Distância:");
        distanciaLabel.setFont(labelFont);
        distanciaField = new JTextField("100", 8);
        distanciaField.setFont(textFieldFont);
        distanciaField.setPreferredSize(new Dimension(80, 20));      
        JButton historicoDistanciaBtn = new JButton("Histórico");
        historicoDistanciaBtn.setFont(buttonFont);
        historicoDistanciaBtn.setPreferredSize(new Dimension(80, 20));
        historicoDistanciaBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                criarHistorico();
            }
        });

        mainPanel.add(distanciaLabel);
        mainPanel.add(distanciaField);
        mainPanel.add(historicoDistanciaBtn);

        // Terceira linha: Turbidez
        JLabel turbidezLabel = new JLabel("Turbidez:");
        turbidezLabel.setFont(labelFont);
        turbidezField = new JTextField("50", 8);
        turbidezField.setPreferredSize(new Dimension(80, 20));
        turbidezField.setFont(textFieldFont);
        JButton historicoTurbidezBtn = new JButton("Histórico");
        historicoTurbidezBtn.setFont(buttonFont);
        historicoTurbidezBtn.setPreferredSize(new Dimension(80, 20));
        historicoTurbidezBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                criarHistorico();
            }
        });

        mainPanel.add(turbidezLabel);
        mainPanel.add(turbidezField);
        mainPanel.add(historicoTurbidezBtn);

        // Quarta linha: Botão Conectar
        JButton conectarBtn = new JButton("Conectar");
        conectarBtn.setFont(buttonFont); // Aumentar fonte do botão
        conectarBtn.setPreferredSize(new Dimension(80, 20));
        conectarBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Conectar();
            }
        });

        // Adicionar o botão Conectar ocupando as 3 colunas
        mainPanel.add(new JLabel()); // Label vazio para ajustar layout
        mainPanel.add(conectarBtn);
        mainPanel.add(new JLabel()); // Label vazio para ajustar layout

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
                new DadosQualidadeAguaOficialGrid().setVisible(true);
            }
        });
    }
}

