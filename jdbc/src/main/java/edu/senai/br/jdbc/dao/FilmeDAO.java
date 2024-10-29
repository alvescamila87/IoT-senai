
package edu.senai.br.jdbc.dao;
import edu.senai.br.jdbc.ConexaoDB;
import edu.senai.br.jdbc.entities.Filme;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

/**
 *
 * @author camila_alves3
 */
public class FilmeDAO {
    
    // Create
    public void inserirFilme(Filme filme) throws SQLException {
        String sql = "INSERT INTO Filme (titulo) values (?)";
        try (Connection connection = ConexaoDB.getConnection();
                PreparedStatement preparedStatement = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {            
                preparedStatement.setString(1, filme.getTitulo());
                preparedStatement.executeUpdate();
                
                // Capturar o ID gerado automaticamente
                try (ResultSet generatedKeys = preparedStatement.getGeneratedKeys()) {
                    if(generatedKeys.next()) {
                        filme.setId(generatedKeys.getInt(1)); // Definir o ID no objeto Filme
                    } else {
                        throw new SQLException("Falha ao inserir filme, nenhum ID gerado.");
                    }
                }
                
        }
    }
    
}
