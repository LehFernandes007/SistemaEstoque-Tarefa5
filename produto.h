
#ifndef PRODUTO_H
#define PRODUTO_H

#include "categoria.h"

#define MAX_PRODUTOS 50

struct Produto
{
    int codigo;
    char nome[50];
    char prateleira;
    float preco;
    int quantidade;
    int disponivel;
    int codigoCategoria;
    int ativo;
};

int cadastrarProduto(struct Produto produtos[], int totalProdutos,
                     struct Categoria categorias[], int totalCategorias);

void listarProdutos(struct Produto produtos[], int totalProdutos,
                    struct Categoria categorias[], int totalCategorias);

void pesquisarProduto(struct Produto produtos[], int totalProdutos,
                      struct Categoria categorias[], int totalCategorias);

void exibirProduto(struct Produto produto,
                   struct Categoria categorias[], int totalCategorias);

int buscarPorCodigo(struct Produto produtos[], int totalProdutos, int codigo);

int buscarPorNome(struct Produto produtos[], int totalProdutos, char nome[]);

void alterarEstoque(struct Produto produtos[], int totalProdutos);

void removerProduto(struct Produto produtos[], int totalProdutos);

#endif

