#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "produto.h"
#include "categoria.h"

int carregarProdutos(struct Produto produtos[]);
int carregarCategorias(struct Categoria categorias[]);

void salvarProdutos(struct Produto produtos[], int totalProdutos);
void salvarCategorias(struct Categoria categorias[], int totalCategorias);

#endif
