#include <ctype.h>
#include "util.h"

int numeroPositivo(int numero)
{
    return numero > 0;
}

int textoPreenchido(char texto[])
{
    int i = 0;

    while (texto[i] != '\0')
    {
        if (!isspace((unsigned char)texto[i]))
            return 1;
        i++;
    }

    return 0;
}

int prateleiraValida(char prateleira)
{
    return prateleira == 'A' || prateleira == 'B' ||
           prateleira == 'C' || prateleira == 'D';
}

int precoValido(float preco)
{
    return preco > 0;
}

int quantidadeValida(int quantidade)
{
    return quantidade >= 0;
}
