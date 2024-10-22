package edu.senai.br.jdbc.entities;

/**
 *
 * @author camila_alves3
 */
public class Categoria {
    
    private int id;
    private String nome;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    @Override
    public String toString() {
        return "Categoria{" + "id=" + id + ", nome=" + nome + '}';
    }

    public Categoria(int id, String nome) {
        this.id = id;
        this.nome = nome;
    }
    
    
    
    
    
}
