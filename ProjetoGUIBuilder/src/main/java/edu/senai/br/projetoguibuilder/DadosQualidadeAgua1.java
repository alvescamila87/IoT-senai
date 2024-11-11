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

public class DadosQualidadeAgua1 extends JFrame {

    // Caixas de texto
    private JTextField temperaturaField;
    private JTextField distanciaField;
    private JTextField turbidezField;

    public DadosQualidadeAgua1() {
        // Configurações da janela
        setTitle("Dados qualidade da água");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(400, 200);
        setLocationRelativeTo(null); // Centralizar a janela

        // Definindo layout com grid 4 linhas e 3 colunas
        setLayout(new GridLayout(4, 3, 5, 5)); // 4 linhas, 3 colunas, espaçamento de 5px

        // Primeira linha: Temperatura
        JLabel temperaturaLabel = new JLabel("Temperatura:");
        temperaturaField = new JTextField("25.5"); // Valor dummy com 1 casa decimal
        JButton historicoTemperaturaBtn = new JButton("Histórico");
        historicoTemperaturaBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                criarHistorico();
            }
        });

        add(temperaturaLabel);
        add(temperaturaField);
        add(historicoTemperaturaBtn);

        // Segunda linha: Distância
        JLabel distanciaLabel = new JLabel("Distância:");
        distanciaField = new JTextField("100"); // Valor dummy como inteiro
        JButton historicoDistanciaBtn = new JButton("Histórico");
        historicoDistanciaBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                criarHistorico();
            }
        });

        add(distanciaLabel);
        add(distanciaField);
        add(historicoDistanciaBtn);

        // Terceira linha: Turbidez
        JLabel turbidezLabel = new JLabel("Turbidez:");
        turbidezField = new JTextField("50"); // Valor dummy como inteiro
        JButton historicoTurbidezBtn = new JButton("Histórico");
        historicoTurbidezBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                criarHistorico();
            }
        });

        add(turbidezLabel);
        add(turbidezField);
        add(historicoTurbidezBtn);

        // Quarta linha: Botão Conectar
        JButton conectarBtn = new JButton("Conectar");
        conectarBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                Conectar();
            }
        });

        // Adicionar o botão Conectar ocupando as 3 colunas
        add(new JLabel()); // Label vazio para ajustar layout
        add(conectarBtn);
        add(new JLabel()); // Label vazio para ajustar layout
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
                new DadosQualidadeAgua1().setVisible(true);
            }
        });
    }
}

