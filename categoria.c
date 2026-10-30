
#include <stdio.h>
#include <string.h>
#include "categoria.h"
#include "util.h"

int buscarCategoriaPorCodigo(struct Categoria categorias[], int total, int codigo)
{
    int i;

    for (i = 0; i < total; i++)
    {
        if (categorias[i].codigo == codigo)
            return i;
    }

    return -1;
}

void listarCategorias(struct Categoria categorias[], int total)
{
    int i;

    printf("\n===== LISTA DE CATEGORIAS =====\n");

    if (total == 0)
    {
        printf("Nenhuma categoria cadastrada.\n");
        return;
    }

    for (i = 0; i < total; i++)
    {
        printf("\nCodigo: %d\n", categorias[i].codigo);
        printf("Nome: %s\n", categorias[i].nome);
    }
}

int cadastrarCategoria(struct Categoria categorias[], int total)
{
    struct Categoria nova;
    char linha[100];
    int resultado;

    if (total >= MAX_CATEGORIAS)
    {
        printf("\nLimite de 20 categorias atingido.\n");
        return total;
    }

    do
    {
        printf("\nDigite o codigo da categoria: ");
        resultado = scanf("%d", &nova.codigo);

        if (resultado != 1)
        {
            printf("Erro: digite um numero inteiro.\n");
            nova.codigo = 0;
        }
        else if (!numeroPositivo(nova.codigo))
        {
            printf("Erro: o codigo deve ser positivo.\n");
        }
        else if (buscarCategoriaPorCodigo(categorias, total, nova.codigo) != -1)
        {
            printf("Erro: esse codigo ja esta cadastrado.\n");
        }

        while (getchar() != '\n' && !feof(stdin))
        {
        }

    } while (!numeroPositivo(nova.codigo) ||
             buscarCategoriaPorCodigo(categorias, total, nova.codigo) != -1);

    do
    {
        printf("Digite o nome da categoria: ");

        if (fgets(linha, sizeof(linha), stdin) == NULL)
            return total;

        linha[strcspn(linha, "\n")] = '\0';

        if (strlen(linha) >= sizeof(nova.nome))
        {
            printf("Erro: o nome deve ter no maximo 29 caracteres.\n");
            continue;
        }

        if (!textoPreenchido(linha))
        {
            printf("Erro: o nome nao pode ficar vazio.\n");
            continue;
        }

        strcpy(nova.nome, linha);
        break;

    } while (1);

    categorias[total] = nova;
    total++;

    printf("\nCategoria cadastrada com sucesso!\n");
    printf("Codigo: %d\n", nova.codigo);
    printf("Nome: %s\n", nova.nome);

    return total;
}

