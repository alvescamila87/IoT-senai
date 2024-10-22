
package edu.senai.br.jdbc.entities;

/**
 *
 * @author camila_alves3
 */
public class Filme {
    
    private int id;
    private String titulo;
    private int ano;
    private String diretor;
    private int categoria_id;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getTitulo() {
        return titulo;
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public int getAno() {
        return ano;
    }

    public void setAno(int ano) {
        this.ano = ano;
    }

    public String getDiretor() {
        return diretor;
    }

    public void setDiretor(String diretor) {
        this.diretor = diretor;
    }

    public int getCategoria_id() {
        return categoria_id;
    }

    public void setCategoria_id(int categoria_id) {
        this.categoria_id = categoria_id;
    }

    @Override
    public String toString() {
        return "Filme{" + "id=" + id + ", titulo=" + titulo + ", ano=" + ano + ", diretor=" + diretor + ", categoria_id=" + categoria_id + '}';
    }

    public Filme(int id, String titulo, int ano, String diretor, int categoria_id) {
        this.id = id;
        this.titulo = titulo;
        this.ano = ano;
        this.diretor = diretor;
        this.categoria_id = categoria_id;
    }
}
