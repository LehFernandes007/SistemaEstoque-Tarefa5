
#include <stdio.h>
#include <string.h>
#include "arquivo.h"

void salvarCategorias(struct Categoria categorias[], int totalCategorias)
{
    FILE *arquivo;
    int i;

    arquivo = fopen("categorias.txt", "w");

    if (arquivo == NULL)
    {
        printf("\nErro ao salvar categorias.\n");
        return;
    }

    for (i = 0; i < totalCategorias; i++)
    {
        fprintf(arquivo, "%d;%s\n",
                categorias[i].codigo,
                categorias[i].nome);
    }

    fclose(arquivo);
}

int carregarCategorias(struct Categoria categorias[])
{
    FILE *arquivo;
    int total = 0;

    arquivo = fopen("categorias.txt", "r");

    if (arquivo == NULL)
        return 0;

    while (total < MAX_CATEGORIAS &&
           fscanf(arquivo, "%d;%29[^\n]\n",
                  &categorias[total].codigo,
                  categorias[total].nome) == 2)
    {
        total++;
    }

    fclose(arquivo);
    return total;
}

void salvarProdutos(struct Produto produtos[], int totalProdutos)
{
    FILE *arquivo;
    int i;

    arquivo = fopen("produtos.txt", "w");

    if (arquivo == NULL)
    {
        printf("\nErro ao salvar produtos.\n");
        return;
    }

    for (i = 0; i < totalProdutos; i++)
    {
        fprintf(arquivo, "%d;%s;%c;%.2f;%d;%d;%d;%d\n",
                produtos[i].codigo,
                produtos[i].nome,
                produtos[i].prateleira,
                produtos[i].preco,
                produtos[i].quantidade,
                produtos[i].quantidade > 0 ? 1 : 0,
                produtos[i].codigoCategoria,
                produtos[i].ativo);
    }

    fclose(arquivo);
}

int carregarProdutos(struct Produto produtos[])
{
    FILE *arquivo;
    char linha[256];
    int total = 0;
    int campos;

    arquivo = fopen("produtos.txt", "r");

    if (arquivo == NULL)
        return 0;

    while (total < MAX_PRODUTOS &&
           fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        produtos[total].ativo = 1;

        campos = sscanf(linha, "%d;%49[^;];%c;%f;%d;%d;%d;%d",
                        &produtos[total].codigo,
                        produtos[total].nome,
                        &produtos[total].prateleira,
                        &produtos[total].preco,
                        &produtos[total].quantidade,
                        &produtos[total].disponivel,
                        &produtos[total].codigoCategoria,
                        &produtos[total].ativo);

        if (campos == 7 || campos == 8)
        {
            produtos[total].disponivel =
                produtos[total].quantidade > 0 ? 1 : 0;

            total++;
        }
    }

    fclose(arquivo);
    return total;
}

