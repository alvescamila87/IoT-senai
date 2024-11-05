
package edu.senai.br.jdbc;

import edu.senai.br.jdbc.dao.CategoriaDAO;
import edu.senai.br.jdbc.dao.CleanDataTableDAO;
import edu.senai.br.jdbc.dao.FilmeDAO;
import edu.senai.br.jdbc.entities.Categoria;
import edu.senai.br.jdbc.entities.Filme;
import java.sql.SQLException;
import java.util.List;

/**
 *
 * @author camila_alves3
 */
public class Jdbc {

    public static void main(String[] args) throws SQLException {
        try {
            // Instanciar
            CategoriaDAO categoriaDAO = new CategoriaDAO();
            FilmeDAO filmeDAO = new FilmeDAO();
            CleanDataTableDAO cleanDB = new CleanDataTableDAO();
            
            // Clean table
            cleanDB.deletarTabelaCategoria();
            cleanDB.setAutoIncrementeOneTabelaCategoria();
            cleanDB.deletarTabelaFilme();
            cleanDB.setAutoIncrementOneTabelaFilme();
            
            // Criar algumas categorias
            Categoria categoria1 = new Categoria(0, "Suspense");
            Categoria categoria2 = new Categoria(0, "Drama");
            Categoria categoria3 = new Categoria(0, "Ação");
            Categoria categoria4 = new Categoria(0, "Romance");
            
            // Criar alguns filmes
            Filme filme1 = new Filme(0, "Prisoners", 2013, "Denis Villeneuve", 1);
            Filme filme2 = new Filme(0, "Ordinary Angels", 2024, "Jon Gunn", 2);
            Filme filme3 = new Filme(0, "Top Gun: Maverick", 2023, "Joseph Kosinski", 7);
            Filme filme4 = new Filme(0, "The Bodyguard", 1992, "Mick Jackson", 4);
            
            //Inserir as categorias no banco
            categoriaDAO.inserirCategoria(categoria1);
            categoriaDAO.inserirCategoria(categoria2);
            categoriaDAO.inserirCategoria(categoria3);
            categoriaDAO.inserirCategoria(categoria4);
            
            //Inserir os filmes no banco
            filmeDAO.inserirFilme(filme1);
            filmeDAO.inserirFilme(filme2);
            filmeDAO.inserirFilme(filme3);
            filmeDAO.inserirFilme(filme4);
            
            // Buscar categoria por ID
            Categoria categoriaPesquisada = categoriaDAO.buscarCategoriaPorId(1);
            System.out.println("ID: " + (categoriaPesquisada != null ? categoria1.getNome() : "Categoria não encontrada"));
            
            // Busca categoria por ID não existente
            categoriaPesquisada = categoriaDAO.buscarCategoriaPorId(100);
            System.out.println("ID: " + (categoriaPesquisada != null ? categoria1.getNome() : "Ctegoria não encontrada"));

            // Busca filme por ID
            Filme filmePesquisado = filmeDAO.buscaFilmePorId(1);
            System.out.println("ID: " + (filmePesquisado != null ? filme1.getTitulo() : "Filme não encontrado"));
            
            // Buscar filme por ID não existente
            filmePesquisado = filmeDAO.buscaFilmePorId(100);
            System.out.println("ID: " + (filmePesquisado != null ? filme1.getTitulo() : "Filme não encontrado"));
            
            // Listar categorias
            List<Categoria> categorias = categoriaDAO.listarCategorias();
            System.out.println(categorias);
            for(Categoria categoria : categorias) {
                System.out.println("ID: " + categoria.getId() + ", Nome: " + categoria.getNome());
            }
            
            // Atualizar categoria 
            categoria1.setNome("Ação com Suspense");
            categoriaDAO.atualizarCategoria(categoria3);
            System.out.println("Categoria ID: " + categoria3.getId() + " atualizada para: " + categoria3.getNome());
            
            // Deletar categoria
            categoriaDAO.deletarCategoria(3);
            System.out.println("Categoria com ID: 4 foi deleteda.");
            
        } catch (SQLException e) {
            System.err.println("Algo errado aconteceu com a manipulação do DB");            
        }    
        
       
    }
}
