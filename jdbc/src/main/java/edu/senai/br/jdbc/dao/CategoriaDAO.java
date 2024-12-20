package edu.senai.br.jdbc.dao;

import edu.senai.br.jdbc.ConexaoDB;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import edu.senai.br.jdbc.entities.Categoria;
import java.util.ArrayList;
import java.util.List;

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
    
     // Buscar por ID
     public Categoria buscarCategoriaPorId(int id) throws SQLException {
        String sql = "SELECT * FROM Categoria WHERE id = ?";
        try (Connection conn = ConexaoDB.getConnection(); PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setInt(1, id);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return new Categoria(rs.getInt("id"), rs.getString("nome"));
            }
        }
        return null;
    }
     
     // Buscar por Nome
     public Categoria buscarCategoriaPorNome(String nome) throws SQLException {
         String sql = "SELECT * FROM Categoria WHERE nome = ?";
         try (Connection conn = ConexaoDB.getConnection(); PreparedStatement stmt = conn.prepareStatement(sql)) {
             stmt.setString(1, nome);
             ResultSet rs = stmt.executeQuery();
             if(rs.next()) {
                 return new Categoria(rs.getInt("id"), rs.getString("nome"));
             }
         }
         return null;
     }
    
     // Listar
    public List<Categoria> listarCategorias() throws SQLException {
        String sql = "SELECT * FROM Categoria";
        List<Categoria> categorias = new ArrayList<>();
        try (Connection conn = ConexaoDB.getConnection(); 
                PreparedStatement stmt = conn.prepareStatement(sql); 
                ResultSet rs = stmt.executeQuery()) {
            while (rs.next()) {
                categorias.add(new Categoria(rs.getInt("id"), rs.getString("nome")));
            }
        }    
        return categorias;
    }
    
    // Update
    public void atualizarCategoria(Categoria categoria) throws SQLException {
        String sql = "UPDATE Categoria SET nome = ? WHERE id = ?";
        try (Connection connection = ConexaoDB.getConnection();
                PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, categoria.getNome());
            preparedStatement.setInt(2, categoria.getId());
            preparedStatement.executeUpdate();            
        }
    }
    
    // Delete 
    public void deletarCategoria(int id) throws SQLException {
        String sql = "DELETE FROM Categoria WHERE id = ?";
        try (Connection conn = ConexaoDB.getConnection(); 
            PreparedStatement preparedStatement = conn.prepareStatement(sql)) {
            preparedStatement.setInt(1, id);
            preparedStatement.executeUpdate();
        }
    }
    
}
