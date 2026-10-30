
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "produto.h"
#include "util.h"
#include "categoria.h"

void limparEntrada(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

int lerInteiro(char mensagem[])
{
    char linha[100];
    int numero;
    char extra;

    while (1)
    {
        printf("%s", mensagem);

        if (fgets(linha, sizeof(linha), stdin) == NULL)
            return 0;

        if (sscanf(linha, " %d %c", &numero, &extra) == 1)
            return numero;

        printf("Erro: digite um numero inteiro.\n");
    }
}

float lerPreco(char mensagem[])
{
    char linha[100];
    float numero;
    char extra;

    while (1)
    {
        printf("%s", mensagem);

        if (fgets(linha, sizeof(linha), stdin) == NULL)
            return 0;

        if (sscanf(linha, " %f %c", &numero, &extra) == 1)
            return numero;

        printf("Erro: digite um preco valido.\n");
    }
}

void lerNome(char nome[], int tamanho, char mensagem[])
{
    char linha[100];

    while (1)
    {
        printf("%s", mensagem);

        if (fgets(linha, sizeof(linha), stdin) == NULL)
        {
            nome[0] = '\0';
            return;
        }

        linha[strcspn(linha, "\n")] = '\0';

        if (!textoPreenchido(linha))
        {
            printf("Erro: o nome nao pode ficar vazio.\n");
        }
        else if ((int)strlen(linha) >= tamanho)
        {
            printf("Erro: nome muito longo.\n");
        }
        else
        {
            strcpy(nome, linha);
            return;
        }
    }
}

int buscarPorCodigo(struct Produto produtos[], int totalProdutos, int codigo)
{
    int i;

    for (i = 0; i < totalProdutos; i++)
    {
        if (produtos[i].codigo == codigo)
            return i;
    }

    return -1;
}

int buscarPorNome(struct Produto produtos[], int totalProdutos, char nome[])
{
    int i;

    for (i = 0; i < totalProdutos; i++)
    {
        if (produtos[i].ativo == 1 &&
            strcmp(produtos[i].nome, nome) == 0)
            return i;
    }

    return -1;
}

void exibirProduto(struct Produto produto,
                   struct Categoria categorias[], int totalCategorias)
{
    int posicaoCategoria;

    printf("Codigo: %d\n", produto.codigo);
    printf("Nome: %s\n", produto.nome);
    printf("Prateleira: %c\n", produto.prateleira);
    printf("Preco unitario: %.2f\n", produto.preco);
    printf("Quantidade: %d\n", produto.quantidade);
    printf("Disponivel para venda: %d\n", produto.quantidade > 0 ? 1 : 0);

    posicaoCategoria = buscarCategoriaPorCodigo(
        categorias, totalCategorias, produto.codigoCategoria);

    if (posicaoCategoria != -1)
        printf("Categoria: %s\n", categorias[posicaoCategoria].nome);
    else
        printf("Categoria: nao encontrada\n");
}

int cadastrarProduto(struct Produto produtos[], int totalProdutos,
                     struct Categoria categorias[], int totalCategorias)
{
    struct Produto novo;
    int posicao;
    char linha[100];

    if (totalProdutos >= MAX_PRODUTOS)
    {
        printf("\nLimite de 50 produtos atingido.\n");
        return totalProdutos;
    }

    if (totalCategorias == 0)
    {
        printf("\nCadastre uma categoria primeiro.\n");
        return totalProdutos;
    }

    do
    {
        novo.codigo = lerInteiro("\nDigite o codigo do produto: ");

        if (!numeroPositivo(novo.codigo))
            printf("Erro: o codigo deve ser positivo.\n");
        else if (buscarPorCodigo(produtos, totalProdutos, novo.codigo) != -1)
            printf("Erro: esse codigo ja esta cadastrado.\n");

    } while (!numeroPositivo(novo.codigo) ||
             buscarPorCodigo(produtos, totalProdutos, novo.codigo) != -1);

    lerNome(novo.nome, sizeof(novo.nome), "Digite o nome do produto: ");

    do
    {
        printf("Digite a prateleira (A, B, C ou D): ");

        if (fgets(linha, sizeof(linha), stdin) == NULL)
            return totalProdutos;

        if (strlen(linha) == 2 && linha[1] == '\n')
            novo.prateleira = linha[0];
        else
            novo.prateleira = '\0';

        if (!prateleiraValida(novo.prateleira))
            printf("Erro: prateleira invalida.\n");

    } while (!prateleiraValida(novo.prateleira));

    do
    {
        novo.preco = lerPreco("Digite o preco unitario: ");

        if (!precoValido(novo.preco))
            printf("Erro: o preco deve ser maior que zero.\n");

    } while (!precoValido(novo.preco));

    do
    {
        novo.quantidade = lerInteiro("Digite a quantidade em estoque: ");

        if (!quantidadeValida(novo.quantidade))
            printf("Erro: a quantidade nao pode ser negativa.\n");

    } while (!quantidadeValida(novo.quantidade));

    listarCategorias(categorias, totalCategorias);

    do
    {
        novo.codigoCategoria = lerInteiro("\nDigite o codigo da categoria: ");

        posicao = buscarCategoriaPorCodigo(
            categorias, totalCategorias, novo.codigoCategoria);

        if (posicao == -1)
            printf("Erro: categoria nao encontrada.\n");

    } while (posicao == -1);

    novo.disponivel = novo.quantidade > 0 ? 1 : 0;
    novo.ativo = 1;

    produtos[totalProdutos] = novo;
    totalProdutos++;

    printf("\n===== PRODUTO CADASTRADO =====\n");
    exibirProduto(novo, categorias, totalCategorias);

    return totalProdutos;
}

void listarProdutos(struct Produto produtos[], int totalProdutos,
                    struct Categoria categorias[], int totalCategorias)
{
    int i, encontrados = 0;

    for (i = 0; i < totalProdutos; i++)
    {
        if (produtos[i].ativo == 1)
        {
            if (encontrados == 0)
                printf("\n===== LISTA DE PRODUTOS =====\n");

            encontrados++;

            printf("\n--- Produto %d ---\n", encontrados);
            exibirProduto(produtos[i], categorias, totalCategorias);
        }
    }

    if (encontrados == 0)
        printf("\nNenhum produto ativo foi encontrado.\n");
}

void pesquisarProduto(struct Produto produtos[], int totalProdutos,
                      struct Categoria categorias[], int totalCategorias)
{
    int opcao, codigo, posicao;
    char nome[50];

    printf("\n===== PESQUISAR PRODUTO =====\n");
    printf("1 - Por codigo\n");
    printf("2 - Por nome\n");

    opcao = lerInteiro("Escolha uma opcao: ");

    if (opcao == 1)
    {
        codigo = lerInteiro("Digite o codigo do produto: ");
        posicao = buscarPorCodigo(produtos, totalProdutos, codigo);
    }
    else if (opcao == 2)
    {
        lerNome(nome, sizeof(nome), "Digite o nome do produto: ");
        posicao = buscarPorNome(produtos, totalProdutos, nome);
    }
    else
    {
        printf("\nOpcao invalida!\n");
        return;
    }

    if (posicao != -1 && produtos[posicao].ativo == 1)
        exibirProduto(produtos[posicao], categorias, totalCategorias);
    else
        printf("\nProduto nao encontrado.\n");
}

void alterarEstoque(struct Produto produtos[], int totalProdutos)
{
    int codigo, posicao, tipo, quantidade;

    printf("\n===== ALTERAR ESTOQUE =====\n");

    codigo = lerInteiro("Digite o codigo do produto: ");
    posicao = buscarPorCodigo(produtos, totalProdutos, codigo);

    if (posicao == -1 || produtos[posicao].ativo == 0)
    {
        printf("\nProduto nao encontrado.\n");
        return;
    }

    printf("\nProduto: %s\n", produtos[posicao].nome);
    printf("Estoque atual: %d\n", produtos[posicao].quantidade);

    printf("\n1 - Entrada\n");
    printf("2 - Saida\n");

    tipo = lerInteiro("Escolha uma opcao: ");

    if (tipo != 1 && tipo != 2)
    {
        printf("\nOpcao invalida.\n");
        return;
    }

    quantidade = lerInteiro("Digite a quantidade: ");

    if (quantidade <= 0)
    {
        printf("\nA quantidade deve ser maior que zero.\n");
        return;
    }

    if (tipo == 1)
    {
        if (quantidade > INT_MAX - produtos[posicao].quantidade)
        {
            printf("\nErro: quantidade muito alta.\n");
            return;
        }

        produtos[posicao].quantidade += quantidade;
        printf("\nEntrada realizada com sucesso!\n");
    }
    else
    {
        if (quantidade > produtos[posicao].quantidade)
        {
            printf("\nErro: estoque insuficiente.\n");
            printf("Nenhuma alteracao foi realizada.\n");
            return;
        }

        produtos[posicao].quantidade -= quantidade;
        printf("\nSaida realizada com sucesso!\n");
    }

    produtos[posicao].disponivel =
        produtos[posicao].quantidade > 0 ? 1 : 0;

    printf("Novo estoque: %d\n", produtos[posicao].quantidade);
    printf("Disponivel para venda: %d\n", produtos[posicao].disponivel);
}

void removerProduto(struct Produto produtos[], int totalProdutos)
{
    int codigo, posicao;

    printf("\n===== REMOVER PRODUTO =====\n");

    codigo = lerInteiro("Digite o codigo do produto: ");
    posicao = buscarPorCodigo(produtos, totalProdutos, codigo);

    if (posicao == -1)
    {
        printf("\nProduto nao encontrado.\n");
        return;
    }

    if (produtos[posicao].ativo == 0)
    {
        printf("\nEste produto ja foi removido.\n");
        return;
    }

    produtos[posicao].ativo = 0;

    printf("\nProduto removido com sucesso!\n");
    printf("O registro foi mantido no sistema.\n");
}

