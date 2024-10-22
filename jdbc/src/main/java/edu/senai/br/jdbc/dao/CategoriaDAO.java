package edu.senai.br.jdbc.dao;

import edu.senai.br.jdbc.ConexaoDB;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import edu.senai.br.jdbc.entities.Categoria;

/**
 *
 * @author camila_alves3
 */
public class CategoriaDAO {
    
    // Create
    public void inserirCategoria(Categoria categoria) throws SQLException {
        String sql = "INSERT INTO Categoria (nome) VALUES (?)";
        try (Connection conn = ConexaoDB.getConnection(); PreparedStatement stmt = conn.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
            stmt.setString(1, categoria.getNome());
            stmt.executeUpdate();

            // Capturar o ID gerado automaticamente
            try (ResultSet generatedKeys = stmt.getGeneratedKeys()) {
                if (generatedKeys.next()) {
                    categoria.setId(generatedKeys.getInt(1));  // Definir o ID no objeto Categoria
                } else {
                    throw new SQLException("Falha ao inserir categoria, nenhum ID gerado.");
                }
            }

        }
    }
    
}
