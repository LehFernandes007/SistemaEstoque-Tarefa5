#ifndef CATEGORIA_H
#define CATEGORIA_H

#define MAX_CATEGORIAS 20

struct Categoria
{
    int codigo;
    char nome[30];
};

int cadastrarCategoria(struct Categoria categorias[], int total);

void listarCategorias(struct Categoria categorias[], int total);

int buscarCategoriaPorCodigo(struct Categoria categorias[],
                            int total, int codigo);

#endif
