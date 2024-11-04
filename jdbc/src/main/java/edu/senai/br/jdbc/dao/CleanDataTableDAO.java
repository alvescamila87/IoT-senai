package edu.senai.br.jdbc.dao;

import edu.senai.br.jdbc.ConexaoDB;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

/**
 *
 * @author camila_alves3
 */
public class CleanDataTableDAO {   
    
    // Categoria
    public void deletarTabelaCategoria() throws SQLException {
        String sql = "DELETE FROM Categoria;";
        try (Connection conn = ConexaoDB.getConnection(); PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.executeUpdate();
        }
    }
    
    // Categoria
    public void setAutoIncrementeOneTabelaCategoria() throws SQLException {
        String sql = "ALTER TABLE Categoria AUTO_INCREMENT=1;";
        try (Connection conn = ConexaoDB.getConnection(); PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.executeUpdate();
        }
    }
    
    // Filme
    public void deletarTabelaFilme() throws SQLException {
        String sql = "DELETE FROM Filme";
        try (Connection connection = ConexaoDB.getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.executeUpdate();
        }
    }
    
    // Filme
    public void setAutoIncrementOneTabelaFilme() throws SQLException {
        String sql = "ALTER TABLE Filme AUTO_INCREMENT=1;";
        try (Connection connection = ConexaoDB.getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.executeUpdate();
        }
    }
}
