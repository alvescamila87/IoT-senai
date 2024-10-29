
package edu.senai.br.jdbc;

import edu.senai.br.jdbc.dao.CategoriaDAO;
import edu.senai.br.jdbc.entities.Categoria;
import java.sql.SQLException;
import java.util.List;

/**
 *
 * @author camila_alves3
 */
public class Jdbc {

    public static void main(String[] args) throws SQLException {
        try {
            CategoriaDAO categoriaDAO = new CategoriaDAO();
            
            // Criar algumas categorias
            Categoria categoria1 = new Categoria(0, "Suspense");
            Categoria categoria2 = new Categoria(0, "Drama");
            Categoria categoria3 = new Categoria(0, "Ação");
            Categoria categoria4 = new Categoria(0, "Romance");
            
            //Inserir as categorias no banco
            categoriaDAO.inserirCategoria(categoria1);
            categoriaDAO.inserirCategoria(categoria2);
            categoriaDAO.inserirCategoria(categoria3);
            categoriaDAO.inserirCategoria(categoria4);
            
            // Buscar categoria por ID
            Categoria categoriaPesquisada = categoriaDAO.buscarCategoriaPorId(1);
            System.out.println("ID: " + (categoriaPesquisada != null ? categoria1.getNome() : "Não entrada"));
            
            // Busca categoria por ID não existente
            categoriaPesquisada = categoriaDAO.buscarCategoriaPorId(100);
            System.out.println("ID: " + (categoriaPesquisada != null ? categoria1.getNome() : "Não encontrada"));            
            
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
