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

public class FormularioCadastro extends JFrame {

    public FormularioCadastro() {
        setTitle("Formulário de Cadastro");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new JPanel(new GridBagLayout());
        GridBagConstraints constraints = new GridBagConstraints();

        // Labels e campos de texto
        JLabel nomeLabel = new JLabel("Nome:");
        JTextField nomeField = new JTextField(20);
        JLabel emailLabel = new JLabel("Email:");
        JTextField emailField = new JTextField(30);
        JLabel senhaLabel = new JLabel("Senha:");
        JPasswordField senhaField = new JPasswordField(20);

        // Botões
        JButton cadastrarButton = new JButton("Cadastrar");
        JButton limparButton = new JButton("Limpar");

        // Configurando as constraints para cada componente
        // Primeira linha: Nome
        constraints.gridx = 0;
        constraints.gridy = 0;
        constraints.anchor = GridBagConstraints.LINE_END; // Alinha o label à direita
        panel.add(nomeLabel, constraints);

        constraints.gridx = 1;
        constraints.gridy = 0;
        constraints.fill = GridBagConstraints.HORIZONTAL; // Ocupa toda a largura disponível
        panel.add(nomeField, constraints);

        // Segunda linha: Email
        constraints.gridx = 0;
        constraints.gridy = 1;
        constraints.anchor = GridBagConstraints.LINE_END;
        panel.add(emailLabel, constraints);

        constraints.gridx = 1;
        constraints.gridy = 1;
        constraints.fill = GridBagConstraints.HORIZONTAL;
        panel.add(emailField, constraints);

        // Terceira linha: Senha
        constraints.gridx = 0;
        constraints.gridy = 2;
        constraints.anchor = GridBagConstraints.LINE_END;
        panel.add(senhaLabel, constraints);

        constraints.gridx = 1;
        constraints.gridy = 2;
        constraints.fill = GridBagConstraints.HORIZONTAL;
        panel.add(senhaField, constraints);

        // Quarta linha: Botões
        constraints.gridx = 0;
        constraints.gridy = 3;
        constraints.gridwidth = 2; // Ocupa duas colunas
        constraints.anchor = GridBagConstraints.CENTER;
        panel.add(cadastrarButton, constraints);

        constraints.gridx = 0;
        constraints.gridy = 4;
        constraints.gridwidth = 2;
        constraints.anchor = GridBagConstraints.CENTER;
        panel.add(limparButton, constraints);

        add(panel);
        pack();
        setVisible(true);
    }

    public static void main(String[] args) {
        new FormularioCadastro();
    }
}