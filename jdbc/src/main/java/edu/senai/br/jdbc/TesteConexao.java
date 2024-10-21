package edu.senai.br.jdbc;

import java.sql.Connection;
import java.sql.SQLException;

/**
 *
 * @author camila_alves3
 */
public class TesteConexao {
    public static void main(String[] args) {
        Connection conexao = null;
        try {
            // Obtém a conexão com o banco de dados
            conexao = ConexaoDB.getConnection();
            System.out.println("Conexão ao banco de dados bem sucedida");
            conexao.close();
        } catch (SQLException e) {
            System.out.println("Erro ao conectar ao banco de dados: " + e.getMessage());
        }  
        
        
    }
}
