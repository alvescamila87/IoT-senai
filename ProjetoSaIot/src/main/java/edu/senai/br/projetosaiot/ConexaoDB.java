package edu.senai.br.projetosaiot;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

/**
 *
 * @author camila_alves3
 */
public class ConexaoDB {
    
    private static final String URL = "jdbc:mysql://localhost:3306/projeto_iot_sa";
    private static final String USER = "root";
    private static final String PASSWORD = "";
    
    public static Connection getConnection() throws SQLException {
        return DriverManager.getConnection(URL, USER, PASSWORD);
    }
    
}
