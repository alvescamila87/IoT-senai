
package edu.senai.br.jdbc;

import edu.senai.br.jdbc.dao.CategoriaDAO;
import edu.senai.br.jdbc.entities.Categoria;
import java.sql.SQLException;

/**
 *
 * @author camila_alves3
 */
public class Jdbc {

    public static void main(String[] args) {
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
            
        } catch (SQLException e){
            System.err.println("Algo errado aconteceu com a manipulação do DB");            
        }
    }
}
