#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::endl;
using std::string;
using std::cout;
using std::cin;
using std::getline; 

// Definição da classe Autor,
class Autor {
    std::string nome;

public:
    Autor(const std::string& n) : nome(n) {}

    // Método para obter o nome do autor.
    const std::string& get_nome() const {
        return nome;
    }
};

// Definição da classe Livro
class Livro {
    std::string titulo;
    std::vector<Autor*> autores; 
    int paginas; 

public:
    // Construtor da classe Livro.
    Livro(const std::string& tit, int pag)
        : titulo(tit), paginas(pag) {}

    // Métodos para obter informações sobre o livro.
    const std::string& get_titulo() const {
        return titulo;
    }

    int get_paginas() const {
        return paginas;
    }

    const std::vector<Autor*>& get_autores() const {
        return autores;
    }

    // Método para adicionar um autor ao livro.
    void adicionar_autor(Autor* autor) {
        autores.push_back(autor);
    }

    // Método para remover um autor do livro.
    void remover_autor(const std::string& nomeAutor) {
        // Usa a função remove_if do algoritmo para encontrar e remover o autor.
        auto it = std::remove_if(autores.begin(), autores.end(), [&nomeAutor](Autor* autor) {
            return autor->get_nome() == nomeAutor;
        });
        // Após a remoção, os elementos removidos são "apagados" do vetor.
        autores.erase(it, autores.end());
    }
    virtual ~Livro(){} // Destrutor virtual da classe Livro.
    virtual void print_info() const = 0; // Função virtual pura para impressão de informações do livro.
};

// Definição da classe LivroFisico
class LivroFisico : public Livro {
    string tipo_de_papel; // Tipo de papel do livro físico.

public:
    // Construtor da classe LivroFisico.
    LivroFisico(const std::string& tit, int pag, const string& tipo)
        : Livro(tit, pag), tipo_de_papel(tipo) {}

    // Método para imprimir informações do livro físico.
    void print_info() const override {
        cout << "Livro físico: " << endl;
        cout << "Título: " << get_titulo() << endl;
        cout << "Páginas: " << get_paginas() << endl;
        cout<< "Tipo de papel: "<< tipo_de_papel<<endl;
        cout << "Autores: ";
        for (auto& autor : get_autores()) {
            cout << autor->get_nome() <<endl;
        }      
    }
};

// Definição da classe LivroDigital
class LivroDigital : public Livro {
    string formato_do_arquivo; // Formato do arquivo do livro digital.

public:
    // Construtor da classe LivroDigital.
    LivroDigital(const std::string& tit, int pag, const string& tipo)
        : Livro(tit, pag), formato_do_arquivo(tipo) {}

    // Método para imprimir informações do livro digital.
    void print_info() const override {
        cout << "Livro Digital: " << endl;
        cout << "Título: " << get_titulo() << endl;
        cout << "Páginas: " << get_paginas() << endl;
        cout<<" Formato do arquivo: "<<formato_do_arquivo<<endl;
        cout << "Autores: ";
        for (auto& autor : get_autores()) {
            cout << autor->get_nome() << " ";
        }
        cout << endl;
    }
};

// Definição da classe Biblioteca
class Biblioteca {
    std::vector<Livro*> livros; 

public:
    // Método para adicionar um livro à biblioteca.
    void adicionar_livro(Livro* livro) {
        livros.push_back(livro);
    }

    // Método para remover um livro da biblioteca.
    void remover_livro(const std::string& tituloLivro) {
        // Usa a função erase com remove_if para remover o livro da biblioteca.
        livros.erase(std::remove_if(livros.begin(), livros.end(), [&tituloLivro](Livro* livro) {
            return livro->get_titulo() == tituloLivro;
        }), livros.end());
    }

    ~Biblioteca(){}

    // Método para imprimir informações de todos os livros da biblioteca.
    void print_info(){
        for(auto& num: livros){
            num->print_info();
        }
    }
};


int main() {
    // Criando biblioteca.
    Biblioteca biblioteca;

    char escolha;


    while (true) {
        // Exibe o menu de opções.
        cout << "===== Menu =====" << endl;
        cout << "1. Adicionar Livro Físico" << endl;
        cout << "2. Adicionar Livro Digital" << endl;
        cout << "3. Remover Livro" << endl;
        cout << "4. Listar Livros" << endl;
        cout << "5. Sair" << endl;
        cout << "Escolha uma opção: ";

        // Obtém a escolha do usuário.
        cin >> escolha;
        cin.ignore(); 

        // Executa a opção escolhida pelo usuário.
        switch (escolha) {
            case '1': {
                string titulo;
                // Obtém informações para adicionar um livro físico.
                cout << "Digite o título do livro físico: ";
                getline(cin, titulo);

                int paginas;
                cout << "Digite o número de páginas: ";
                cin >> paginas;
                cin.ignore(); 

                string tipo_papel;
                cout << "Digite o tipo de papel: ";
                getline(cin, tipo_papel);

                // Cria um objeto LivroFisico e adiciona à biblioteca.
                LivroFisico* livro = new LivroFisico(titulo, paginas, tipo_papel);

                int num_autores;
                cout << "Quantos autores deseja adicionar ao livro? ";
                cin >> num_autores;
                cin.ignore(); 

                // Adiciona os autores ao livro.
                for (int i = 0; i < num_autores; ++i) {
                    string nome_autor;
                    cout << "Digite o nome do autor " << i + 1 << ": ";
                    getline(cin, nome_autor);
                    Autor* autor = new Autor(nome_autor);
                    livro->adicionar_autor(autor);
                }

                // Adiciona o livro à biblioteca.
                biblioteca.adicionar_livro(livro);
                cout << "Livro físico adicionado com sucesso!" << endl;
                break;
            }
            case '2': {
                string titulo;
                // Obtém informações para adicionar um livro digital.
                cout << "Digite o título do livro digital: ";
                getline(cin, titulo);

                int paginas;
                cout << "Digite o número de páginas: ";
                cin >> paginas;
                cin.ignore(); 

                string formato_arquivo;
                cout << "Digite o formato do arquivo: ";
                getline(cin, formato_arquivo);

                // Cria um objeto LivroDigital e adiciona à biblioteca.
                LivroDigital* livro = new LivroDigital(titulo, paginas, formato_arquivo);

                int num_autores;
                cout << "Quantos autores deseja adicionar ao livro? ";
                cin >> num_autores;
                cin.ignore(); 

                // Adiciona os autores ao livro.
                for (int i = 0; i < num_autores; ++i) {
                    string nome_autor;
                    cout << "Digite o nome do autor " << i + 1 << ": ";
                    getline(cin, nome_autor);
                    Autor* autor = new Autor(nome_autor);
                    livro->adicionar_autor(autor);
                }

                // Adiciona o livro à biblioteca.
                biblioteca.adicionar_livro(livro);
                cout << "Livro digital adicionado com sucesso!" << endl;
                break;
            }
            case '3': {
                string titulo;
                // Obtém o título do livro a ser removido.
                cout << "Digite o título do livro a ser removido: ";
                getline(cin, titulo);
                // Remove o livro da biblioteca.
                biblioteca.remover_livro(titulo);
                cout << "Livro removido com sucesso!" << endl;
                break;
            }
            case '4': {
                // Lista todos os livros da biblioteca.
                cout << "===== Livros na Biblioteca =====" << endl;
                biblioteca.print_info();
                break;
            }
            case '5': {
                // Encerra o programa.
                cout << "Obrigado por usar a biblioteca. Até mais!" << endl;
                return 0;
            }
            default: {
                // Mensagem de opção inválida.
                cout << "Opção inválida! Tente novamente." << endl;
                break;
            }
        }
    }

    return 0;
}
