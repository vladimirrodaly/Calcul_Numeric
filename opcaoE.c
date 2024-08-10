// Ao selecionar a opção ‘E’, o programa deverá ler uma equação algébrica da forma anxn + an-1xn-1 + ... + a1x + a0,
// com an> 0 e a0 ≠ 0. O programa deverá solicitar o grau da equação e os coeficientes an, an-1, ..., a0, nessa ordem.
// O programa deve exigir que an> 0 e a0 ≠ 0.
// Utilizando o Teorema de Lagrange, o programa deverá calcular e exibir os intervalos onde se encontram as raízes
// reais negativas e as raízes reais positivas da equação. Utilizando o limite superior do intervalo onde se encontram
// as raízes positivas como aproximação inicial (x0), o programa deverá determinar uma aproximação para uma raiz
// usando o Método de Newton. Pare quando a diferença (em módulo) entre duas soluções aproximadas for menor
// do que 10-8 ou após 1000 iterações. Exiba a solução encontrada e o número de iterações realizadas.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void solicitarCoeficientes(int grau, double *coef) {
    for (int i = 0; i <= grau; i++) {
        do {
            printf("Digite o coeficiente a_%d: ", grau - i);
            scanf("%lf", &coef[i]);

            if (i == 0 && coef[0] <= 0)
                printf("O coeficiente a_%d deve ser maior que 0.\n", grau);
            if (i == grau && coef[grau] == 0)
                printf("O coeficiente a_0 deve ser diferente de 0.\n");

        } while ((i == 0 && coef[0] <= 0) || (i == grau && coef[grau] == 0));
    }
}

// lagrange

int contarMudancasSinal(int grau, double *coef) {
    int mudancas = 0;
    for (int i = 1; i <= grau; i++) {
        if (coef[i] * coef[i-1] < 0) {
            mudancas++;
        }
    }
    return mudancas;
}
// A contagem de mudanças de sinal permite ao programa aplicar o método de Descartes e, 
// consequentemente, fornecer uma estimativa precisa dos intervalos 
// onde as raízes reais do polinômio podem estar.


void inverterSinais(int grau, double *coef) {
    for (int i = 1; i <= grau; i += 2) {
        coef[i] = -coef[i];
    }
}

// metodo de newton
double calcularPolinomio(int grau, double *coef, double x) {
    double resultado = 0;
    for (int i = 0; i <= grau; i++) {
        resultado += coef[i] * pow(x, grau - i);
    }
    return resultado;
}

double calcularDerivada(int grau, double *coef, double x) {
    double resultado = 0;
    for (int i = 0; i < grau; i++) {
        resultado += coef[i] * (grau - i) * pow(x, grau - i - 1);
    }
    return resultado;
}

void metodoDeNewton(int grau, double *coef, double x0) {
    double x = x0;
    double tolerancia = 1e-8;
    int iteracao = 0;
    int maxIteracoes = 1000;
    double diferenca;

    do {
        double f_x = calcularPolinomio(grau, coef, x);
        double f_prime_x = calcularDerivada(grau, coef, x);
        if (fabs(f_prime_x) < tolerancia) {
            printf("Derivada próxima de zero. O método pode falhar.\n");
            break;
        }
        double x1 = x - f_x / f_prime_x;
        diferenca = fabs(x1 - x);
        x = x1;
        iteracao++;
    } while (diferenca > tolerancia && iteracao < maxIteracoes);

    printf("Aproximação da raiz positiva: %.8f\n", x);
    printf("Número de iterações: %d\n", iteracao);
}

int main() {
    int grau;

    printf("Digite o grau da equação (n): ");
    scanf("%d", &grau);

    double *coef = (double *)malloc((grau + 1) * sizeof(double));

    solicitarCoeficientes(grau, coef);

    int mudancasPositivas = contarMudancasSinal(grau, coef);

    // Inverte sinais dos coeficientes ímpares para contar mudanças de sinal para raízes negativas
    inverterSinais(grau, coef);
    int mudancasNegativas = contarMudancasSinal(grau, coef);

    printf("Número máximo de raízes reais positivas: %d\n", mudancasPositivas);
    printf("Número máximo de raízes reais negativas: %d\n", mudancasNegativas);

    // Determina a aproximação da raiz positiva pelo Método de Newton
    if (mudancasPositivas > 0) {
        double x0 = 1.0; // Ponto de partida inicial para o Método de Newton
        metodoDeNewton(grau, coef, x0);
    } else {
        printf("Não há raízes reais positivas a serem calculadas.\n");
    }

    free(coef);
    return 0;
}
