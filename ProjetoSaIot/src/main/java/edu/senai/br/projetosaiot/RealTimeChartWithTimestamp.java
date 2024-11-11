/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package edu.senai.br.projetosaiot;

/**
 *
 * @author Acer
 */
import java.awt.BasicStroke;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.DateAxis;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import javax.swing.*;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;
import org.jfree.chart.plot.XYPlot;

public class RealTimeChartWithTimestamp extends JFrame {

    private XYSeries series;
    private static final int WINDOW_SIZE = 20; // Tamanho da janela móvel (20 pontos)

    public RealTimeChartWithTimestamp(String title) {
        super(title);

        // Criando a série de dados
        series = new XYSeries("Temperatura");
        XYSeriesCollection dataset = new XYSeriesCollection(series);

        // Criando o gráfico de linha
        JFreeChart chart = ChartFactory.createXYLineChart(
                "Temperatura em Tempo Real", // Título do gráfico
                "Tempo",                     // Eixo X
                "Temperatura (°C)",          // Eixo Y
                dataset,                     // Dataset
                PlotOrientation.VERTICAL,    // Orientação do gráfico
                true,                        // Exibir legenda
                true,                        // Exibir tooltips
                false                        // URLs
        );

        // Configurando o formato do eixo X para exibir apenas horas:minutos:segundos
        DateAxis axis = new DateAxis("Tempo");
        axis.setDateFormatOverride(new SimpleDateFormat("HH:mm:ss"));
        chart.getXYPlot().setDomainAxis(axis);
        
        // Configurando a espessura da linha
        XYPlot plot = chart.getXYPlot();
        plot.getRenderer().setSeriesStroke(0, new BasicStroke(2.0f)); // Espessura da linha 2.0f


        // Configurando o painel do gráfico
        ChartPanel chartPanel = new ChartPanel(chart);
        chartPanel.setPreferredSize(new java.awt.Dimension(800, 600));
        setContentPane(chartPanel);

        // Agendando atualizações de dados
        Timer timer = new Timer();
        timer.scheduleAtFixedRate(new TimerTask() {
            @Override
            public void run() {
                atualizarDadosSensor(); // Simula a leitura de um novo dado do sensor
            }
        }, 0, 1000); // Atualiza a cada 1 segundo (1000 ms)
    }

    // Simula a atualização de dados do sensor e atualiza o gráfico
    private void atualizarDadosSensor() {
        Random rand = new Random();
        double temperatura = 20 + rand.nextDouble() * 10; // Simula temperatura entre 20 e 30°C
        Date now = new Date(); // Pega o timestamp atual

        // Adicionando novo valor à série com timestamp
        series.add(now.getTime(), temperatura);

        // Mantendo a janela móvel
        if (series.getItemCount() > WINDOW_SIZE) {
            series.remove(0); // Remove o dado mais antigo para manter a janela
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            RealTimeChartWithTimestamp example = new RealTimeChartWithTimestamp("Gráfico em Tempo Real");
            example.pack();
            example.setVisible(true);
            example.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        });
    }
}
