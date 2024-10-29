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
    
    public void deletarTabelaCategoria() throws SQLException {
        String sql = "DELETE FROM Categoria;";
        try (Connection conn = ConexaoDB.getConnection(); PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.executeUpdate();
        }
    }
    
    public void setAutoIncrementeOneTabelaCategoria() throws SQLException {
        String sql = "ALTER TABLE Categoria AUTO_INCREMENT=1;";
        try (Connection conn = ConexaoDB.getConnection(); PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.executeUpdate();
        }
    }
}
