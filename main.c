
#include <stdio.h>
#include "produto.h"
#include "categoria.h"
#include "arquivo.h"

int main(void)
{
    struct Produto produtos[MAX_PRODUTOS];
    struct Categoria categorias[MAX_CATEGORIAS];

    int totalProdutos = carregarProdutos(produtos);
    int totalCategorias = carregarCategorias(categorias);
    int opcao, opcaoCategoria;
    int caractere;

    do
    {
        printf("\n===== SISTEMA DE ESTOQUE =====\n");
        printf("1 - Cadastrar Produto\n");
        printf("2 - Listar Produtos\n");
        printf("3 - Pesquisar Produto\n");
        printf("4 - Alterar Estoque de um Produto\n");
        printf("5 - Remover Produto\n");
        printf("6 - Categorias\n");
        printf("7 - Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1)
        {
            opcao = 0;
        }

        while ((caractere = getchar()) != '\n' && caractere != EOF)
        {
        }

        if (opcao == 1)
        {
            totalProdutos = cadastrarProduto(produtos, totalProdutos,
                                             categorias, totalCategorias);
        }
        else if (opcao == 2)
        {
            listarProdutos(produtos, totalProdutos,
                           categorias, totalCategorias);
        }
        else if (opcao == 3)
        {
            pesquisarProduto(produtos, totalProdutos,
                             categorias, totalCategorias);
        }
        else if (opcao == 4)
        {
            alterarEstoque(produtos, totalProdutos);
        }
        else if (opcao == 5)
        {
            removerProduto(produtos, totalProdutos);
        }
        else if (opcao == 6)
        {
            do
            {
                printf("\n===== CATEGORIAS =====\n");
                printf("1 - Cadastrar Categoria\n");
                printf("2 - Listar Categorias\n");
                printf("3 - Voltar\n");
                printf("Escolha uma opcao: ");

                if (scanf("%d", &opcaoCategoria) != 1)
                {
                    opcaoCategoria = 0;
                }

                while ((caractere = getchar()) != '\n' && caractere != EOF)
                {
                }

                if (opcaoCategoria == 1)
                {
                    totalCategorias = cadastrarCategoria(categorias,
                                                         totalCategorias);
                }
                else if (opcaoCategoria == 2)
                {
                    listarCategorias(categorias, totalCategorias);
                }
                else if (opcaoCategoria == 3)
                {
                    printf("\nVoltando ao menu principal...\n");
                }
                else
                {
                    printf("\nOpcao invalida!\n");
                }

            } while (opcaoCategoria != 3);
        }
        else if (opcao == 7)
        {
            salvarCategorias(categorias, totalCategorias);
            salvarProdutos(produtos, totalProdutos);

            printf("\nDados salvos com sucesso!\n");
            printf("Saindo do sistema...\n");
        }
        else
        {
            printf("\nOpcao invalida!\n");
        }

    } while (opcao != 7);

    return 0;
}

