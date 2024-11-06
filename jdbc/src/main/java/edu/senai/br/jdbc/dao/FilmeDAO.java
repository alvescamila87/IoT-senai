package edu.senai.br.jdbc.dao;

import edu.senai.br.jdbc.ConexaoDB;
import edu.senai.br.jdbc.entities.Filme;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author camila_alves3
 */
public class FilmeDAO {

    // Create filme
    public void inserirFilme(Filme filme) throws SQLException {
        String sql = "INSERT INTO Filme (titulo, ano, diretor, categoria_id) values (?, ?, ?, ?)";
        try (Connection connection = ConexaoDB.getConnection(); PreparedStatement preparedStatement = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
            preparedStatement.setString(1, filme.getTitulo());
            preparedStatement.setInt(2, filme.getAno());
            preparedStatement.setString(3, filme.getDiretor());
            preparedStatement.setInt(4, filme.getCategoria_id());
            preparedStatement.executeUpdate();

            // Capturar o ID gerado automaticamente e demais informações
            try (ResultSet generatedKeys = preparedStatement.getGeneratedKeys()) {
                if (generatedKeys.next()) {
                    filme.setId(generatedKeys.getInt(1)); // Definir o ID no objeto Filme
                    filme.setTitulo(filme.getTitulo());
                    filme.setAno(filme.getAno());
                    filme.setDiretor(filme.getDiretor());
                    filme.setCategoria_id(filme.getCategoria_id());
                } else {
                    throw new SQLException("Falha ao inserir filme, nenhum ID gerado.");
                }
            }

        }
    }

    // Get filme por ID
    public Filme buscaFilmePorId(int id) throws SQLException {
        String sql = "SELECT * FROM Filme WHERE id = ?";
        try (Connection connection = ConexaoDB.getConnection(); PreparedStatement statement = connection.prepareStatement(sql)) {
            statement.setInt(1, id);
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                return new Filme(
                        resultSet.getInt("id"),
                        resultSet.getString("titulo"),
                        resultSet.getInt("ano"),
                        resultSet.getString("diretor"),
                        resultSet.getInt("categoria_id")
                );
            }
        }
        return null;
    }

    // Get filmes
    public List<Filme> listarFilmes() throws SQLException {
        String sql = "SELECT * FROM Filme";
        List<Filme> filmes = new ArrayList<>();
        try (Connection connection = ConexaoDB.getConnection(); PreparedStatement statement = connection.prepareStatement(sql); ResultSet resultSet = statement.executeQuery()) {
            while (resultSet.next()) {
                filmes.add(new Filme(
                        resultSet.getInt("id"),
                        resultSet.getString("titulo"),
                        resultSet.getInt("ano"),
                        resultSet.getString("diretor"),
                        resultSet.getInt("categoria_id")
                ));
            }
        }
        return filmes;
    }
    
    // Update filmes
    public void atualizarFilme(Filme filme) throws SQLException {
        String sql = "UPDATE Filme SET titulo = ?, ano = ?, diretor = ?, categoria_id = ? WHERE id = ?;";
        try (Connection connection = ConexaoDB.getConnection(); 
                PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, filme.getTitulo());
            preparedStatement.setInt(2, filme.getAno());
            preparedStatement.setString(3, filme.getDiretor());
            preparedStatement.setInt(4, filme.getCategoria_id());
            preparedStatement.setInt(5, filme.getId());
            preparedStatement.executeUpdate();           
        }
    }

}
