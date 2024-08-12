/*Ao selecionar a opção ‘C’, o usuário deverá digitar um número decimal, eventualmente com parte fracionária, e o
programa deverá exibir esse número nos sistemas numéricos binário, octal e hexadecimal com até vinte casas
decimais significativas. Por exemplo, se o usuário digitar o número 14.25 o programa deverá exibir:
Binário: 1110.01
Octal: 16.2
Hexadecimal: E.4
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Função auxiliar para inverter uma string
void inverterString(char *str, int length) {
    for (int j = 0; j < length / 2; j++) {
        char temp = str[j];
        str[j] = str[length - j - 1];
        str[length - j - 1] = temp;
    }
}

// Converter a parte inteira de um número para binário
void decimalParaBinarioInteiro(int num, char *bin) {
    int i = 0;
    if (num == 0) {
        bin[i++] = '0';
    }
    while (num > 0) {
        bin[i++] = (num % 2) + '0';
        num = num / 2;
    }
    inverterString(bin, i);
    bin[i] = '\0';
}

// Converter a parte fracionária de um número para binário
void decimalParaBinarioFracionario(double num, char *bin) {
    int i = 0;
    while (num > 0 && i < 20) { 
        num *= 2;
        if (num >= 1) {
            bin[i] = '1';
            num -= 1;
        } else {
            bin[i] = '0';
        }
        i++;
    }
    bin[i] = '\0';
}

// Converter a parte inteira de um número para octal
void decimalParaOctalInteiro(int num, char *oct) {
    int i = 0;
    if (num == 0) {
        oct[i++] = '0';
    }
    while (num > 0) {
        oct[i++] = (num % 8) + '0';
        num = num / 8;
    }
    inverterString(oct, i);
    oct[i] = '\0';
}

// Converter a parte fracionária de um número para octal
void decimalParaOctalFracionario(double num, char *oct) {
    int i = 0;
    while (num > 0 && i < 20) { 
        num *= 8;
        int parteInteira = (int)num;
        oct[i++] = parteInteira + '0';
        num -= parteInteira;
    }
    oct[i] = '\0';
}

// Converter a parte inteira de um número para hexadecimal
void decimalParaHexadecimalInteiro(int num, char *hex) {
    int i = 0;
    if (num == 0) {
        hex[i++] = '0';
    }
    while (num > 0) {
        int resto = num % 16;
        if (resto < 10) {
            hex[i++] = resto + '0';
        } else {
            hex[i++] = resto - 10 + 'A';
        }
        num = num / 16;
    }
    inverterString(hex, i);
    hex[i] = '\0';
}

// Converter a parte fracionária de um número para hexadecimal
void decimalParaHexadecimalFracionario(double num, char *hex) {
    int i = 0;
    while (num > 0 && i < 20) { 
        num *= 16;
        int parteInteira = (int)num;
        if (parteInteira < 10) {
            hex[i] = parteInteira + '0';
        } else {
            hex[i] = parteInteira - 10 + 'A';
        }
        num -= parteInteira;
        i++;
    }
    hex[i] = '\0';
}

// Função principal para ler a entrada e exibir os resultados
int main() {
    double numero;
    printf("Digite um número decimal: ");
    scanf("%lf", &numero);

    int parteInteira = (int)numero;
    double parteFracionaria = numero - parteInteira;

    char binInteiro[64], binFracionario[21];
    char octInteiro[64], octFracionario[21];
    char hexInteiro[64], hexFracionario[21];

    decimalParaBinarioInteiro(parteInteira, binInteiro);
    decimalParaBinarioFracionario(parteFracionaria, binFracionario);

    decimalParaOctalInteiro(parteInteira, octInteiro);
    decimalParaOctalFracionario(parteFracionaria, octFracionario);

    decimalParaHexadecimalInteiro(parteInteira, hexInteiro);
    decimalParaHexadecimalFracionario(parteFracionaria, hexFracionario);

    printf("Binário: %s.%s\n", binInteiro, binFracionario);
    printf("Octal: %s.%s\n", octInteiro, octFracionario);
    printf("Hexadecimal: %s.%s\n", hexInteiro, hexFracionario);

    return 0;
}
