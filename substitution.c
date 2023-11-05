#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int verificador(int argc, string argv);
string codificador(string txt, string chave);
int posicao (char letra);
int testa_copia (string chave);
//declaracao do alfabeto como base
const string BASE = "abcdefghijklmnopqrstuvwxyz0";

int main(int argc, string argv[])
{
    //opcoes possiveis de erros e variaveis
    string original = "x", codificado = "x";
    //validacao da chave
    int validez = verificador(argc, argv[1]);
    if (validez == 1)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    else if (validez == 2)
    {
        printf("A chave deve incluir somente letras.\n");
        return 1;
    }
    else if (validez == 3)
    {
        printf("A chave deve conter 26 letras.\n");
        return 1;
    }
    else if (validez == 4)
    {
        printf("A chave não deve conter letras repetidas.\n");
        return 1;
    }
    else if (validez == 0)
    {
        //validez 0 significa que nao houve erros, entrada e saida de dados a seguir
        original = get_string("plaintext: ");
        codificado = codificador(original, argv[1]);
        printf("ciphertext: %s\n", codificado);
    }

}

int verificador(int argc, string key)
//funcao que testa se a chave a valida
{
    if (argc == 1 || argc > 2)
    {
        return 1;
    }
    int pont, len = strlen(key), letras = 0;

    for (int i = 0; i < len; i++)
    {

        key[i] = tolower(key[i]);
        pont = key[i];
        if (pont < 97 || pont > 122)
        {
            return 2;
        }
        letras++;
    }
    if (letras != 26)
    {
        return 3;
    }
    int copia = testa_copia(key);
    if (copia == 1)
    {
        return 4;
    }
    else
    {
        return 0;
    }
}

string codificador(string txt, string chave)
//funcao que codifica a o texto recebido pelo usuario, so e chamada quando a validade da chave foi confirmada
{
    int ponteiro = 0;
    for (int i = 0, len = strlen(txt); i < len; i++)
    {
        ponteiro = txt[i];
        if (ponteiro >= 97 && ponteiro <= 122)
        {
            txt[i] = chave[posicao(txt[i])];
        }
        else if (ponteiro >= 65 && ponteiro <= 90)
        {
            txt[i] = toupper(chave[posicao(tolower(txt[i]))]);
        }
    }
    return txt;

}

int posicao (char letra)
//funcao auxiliar que que remete a posicao de uma letra no alfabeto
{
    for (int pos = 0;pos < 26; pos++)
    {
        if (letra == BASE[pos])
        {
            return pos;
        }
    }
    return 0;
}

int testa_copia (string chave)
//funcao auxiliar para testar se a chave contem caracteres repetidos
{
    char ponteiro;
    char copia[256];
    int len = strlen(chave);
    for (int c = 0; c < len; c++)
    {
        ponteiro = chave[c];
        copia[c] = ponteiro;
    }
    for (int i = 0; i < len; i++)
    {
        ponteiro = copia[i];
        copia[i] = '0';
        for (int j = 0; j < len; j++)
        {
            if (ponteiro == copia[j])
            {
                return 1;
            }
        }
    }
    return 0;
}
