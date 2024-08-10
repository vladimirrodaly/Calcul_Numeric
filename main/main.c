/*
 * EXERCÍCIO PROGRAMA DE CÁLCULO NUMÉRICO - ENGENHARIA DE TELECOMUNICAÇÕES
 * PROFESSOR: GLAUBER CINTRA                ENTREGA: 12/08/2024
 * INTEGRANTES (ORDEM ALFABÉTICA):          
 * Douglas Cartaxo Farias             
 * Debora Sales Costa             
 * Júlia Lucena de Saboya 
 * Vladimir Rodaly Joseph             
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void convert_to_binary_octal_hexadecimal(double num, char *filename);
void solve_linear_system(char *filename, char *output_filename);
void display_menu();
void save_to_file(char *filename, char *data);
void read_file(char *filename);

int main() {
    char option;

    do {
        display_menu();
        scanf(" %c", &option);

        switch (option) {
            case 'C':
            case 'c': {
                double num;
                char filename[100];
                printf("Digite um número decimal: ");
                scanf("%lf", &num);
                printf("Digite o nome do arquivo para salvar os resultados: ");
                scanf("%s", filename);
                convert_to_binary_octal_hexadecimal(num, filename);
                break;
            }
            case 'S':
            case 's': {
                char filename[100], output_filename[100];
                printf("Digite o nome do arquivo que contém o sistema linear: ");
                scanf("%s", filename);
                printf("Digite o nome do arquivo para salvar os resultados: ");
                scanf("%s", output_filename);
                solve_linear_system(filename, output_filename);
                break;
            }
            case 'E':
            case 'e':
                printf("Opção de Equação Algébrica ainda não implementada.\n");
                break;
            case 'F':
            case 'f':
                printf("Finalizando o programa...\n");
                break;
            case 'O':
            case 'o': {
                char filename[100];
                printf("Digite o nome do arquivo para abrir e ler: ");
                scanf("%s", filename);
                read_file(filename);
                break;
            }
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (option != 'F' && option != 'f');

    return 0;
}

void display_menu() {
    printf("\n====Menu Principal=====\n");
    printf("\n************************************************\n");
    printf("C - Conversão\n");
    printf("S - Sistema Linear\n");
    printf("E - Equação Algébrica\n");
    printf("O - Abrir Arquivo\n");
    printf("F - Finalizar\n");
    printf("Escolha uma opção: ");
    printf("\n************************************************\n");
}

void convert_to_binary_octal_hexadecimal(double num, char *filename) {
    char result[500];
    char buffer[100];
    
    // Parte inteira e fracionária
    unsigned long long int_part = (unsigned long long) num;
    double frac_part = num - int_part;

    // Conversão para binário
    char binary[65] = {0};
    int index = 63;
    while (int_part > 0) {
        binary[index--] = (int_part % 2) ? '1' : '0';
        int_part /= 2;
    }
    char binary_frac[65] = {0};
    index = 0;
    while (frac_part > 0 && index < 20) {
        frac_part *= 2;
        binary_frac[index++] = (frac_part >= 1) ? '1' : '0';
        frac_part -= (int)frac_part;
    }
    snprintf(buffer, sizeof(buffer), "Binário: %s.%s\n", binary + 1, binary_frac);
    strcat(result, buffer);

    // Conversão para octal
    snprintf(buffer, sizeof(buffer), "Octal: %.*A\n", 20, num);
    strcat(result, buffer);

    // Conversão para hexadecimal
    snprintf(buffer, sizeof(buffer), "Hexadecimal: %.*A\n", 20, num);
    strcat(result, buffer);

    printf("%s", result);
    save_to_file(filename, result);
}

void solve_linear_system(char *filename, char *output_filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    int n;
    fscanf(file, "%d", &n);
    double matrix[n][n+1];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            fscanf(file, "%lf", &matrix[i][j]);
        }
    }
    fclose(file);

    // Método de Eliminação de Gauss
    for (int i = 0; i < n; i++) {
        for (int k = i + 1; k < n; k++) {
            double factor = matrix[k][i] / matrix[i][i];
            for (int j = 0; j <= n; j++) {
                matrix[k][j] -= factor * matrix[i][j];
            }
        }
    }

    double x[n];
    for (int i = n - 1; i >= 0; i--) {
        x[i] = matrix[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= matrix[i][j] * x[j];
        }
        x[i] /= matrix[i][i];
    }

    char result[500] = "Soluções:\n";
    char buffer[100];
    for (int i = 0; i < n; i++) {
        snprintf(buffer, sizeof(buffer), "x%d = %lf\n", i + 1, x[i]);
        strcat(result, buffer);
    }

    printf("%s", result);
    save_to_file(output_filename, result);
}

void save_to_file(char *filename, char *data) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erro ao salvar no arquivo!\n");
        return;
    }
    fprintf(file, "%s", data);
    fclose(file);
    printf("Dados salvos no arquivo: %s\n", filename);
}

void read_file(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
    printf("\nFim da leitura do arquivo: %s\n", filename);
}
