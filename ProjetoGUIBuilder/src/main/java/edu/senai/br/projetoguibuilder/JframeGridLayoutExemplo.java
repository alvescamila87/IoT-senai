package edu.senai.br.projetoguibuilder;

import java.awt.GridLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

public class JframeGridLayoutExemplo extends JFrame {

    private JPanel panel = new JPanel();
    private JLabel label = new JLabel("Nome:");
    private JTextField textField = new JTextField(10); // 10 é o tamanho da caixa de texto
    private JButton button = new JButton("Enviar");

    JframeGridLayoutExemplo() {

        JPanel panel = new JPanel(new GridLayout(2, 2)); // 2 linhas, 2 colunas
        JLabel label = new JLabel("Nome:");
        JTextField textField = new JTextField(10);
        JButton button = new JButton("Enviar");

        panel.add(label);      // Primeira célula (linha 1, coluna 1)
        panel.add(textField);  // Segunda célula (linha 1, coluna 2)
        panel.add(button);     // Terceira célula (linha 2, coluna 1)

        add(panel);

        // Configurações da janela
        setTitle("Minha Janela GridLayout");
        
        setSize(500, 400); // Define o tamanho da janela
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Fecha o programa ao fechar a janela
        setLocationRelativeTo(null); // Centralizar a janela
        setVisible(true); // Torna a janela visível
    }
    
    public static void main(String[] args) {
    SwingUtilities.invokeLater(() -> new JframeGridLayoutExemplo().setVisible(true));
}


    /*
    public static void main(String[] args) {
        // Criando e exibindo a janela
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new JframeGridLayoutExemplo().setVisible(true);
            }
        });
    }
    */
    
    /*
      public static void main(String[] args) {
        new JframeGridLayoutExemplo().setVisible(true);
    }
     */

}
