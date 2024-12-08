#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>  
#include <stdlib.h>  
#include <locale.h>  
#include <math.h>  
#include <time.h>  // Для использования srand

int main() {
    setlocale(LC_CTYPE, "RUS");

    puts("***************************************************************************");
    puts("*                                                                         *");
    puts("*Курсовой проект по дисцплине \"осовы программирования и алгоритмизации\"   *");
    puts("*Тема:\"Реализация динамического и многомерно массива\"                     *");
    puts("*Выполнила:Пуляева.Л.Ю,группа бИД-241                                     *");
    puts("*                                                                         *");
    puts("***************************************************************************");

    puts("Программа выводит массив,\nколичество строк с нулями, \nсумму отрицательных элементов и найденные седловые точки по выбору пользователя.");

    puts("***************************************************************************");

    int rows, cols;
    int choice, randomize;
    int** matrix = NULL;

    while (1) {
        printf("\nМеню:\n");
        printf("1. Инициализировать матрицу\n");
        printf("2. Показать матрицу\n");
        printf("3. Подсчитать отрицательные элементы в строках с нулями\n");
        printf("4. Найти седловые точки\n");
        printf("5. Завершить программу\n");
        printf("Выберите действие: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            // Инициализация матрицы
            if (matrix) {
                for (int i = 0; i < rows; i++) {
                    free(matrix[i]);
                }
                free(matrix);
            }
            printf("Введите количество строк и столбцов: ");
            scanf_s("%d %d", &rows, &cols);
            printf("Выберите способ инициализации:\n1. Случайные числа\n2. Ввод с консоли\n");
            scanf_s("%d", &randomize);

            matrix = (int**)malloc(rows * sizeof(int*));
            for (int i = 0; i < rows; i++) {
                matrix[i] = (int*)malloc(cols * sizeof(int));
            }

            if (randomize == 1) {
                srand(time(0));
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        matrix[i][j] = rand() % 21 - 10; // случайные числа от -10 до 10
                    }
                }
            }
            else {
                printf("Введите элементы матрицы %d%d:\n", rows, cols);
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        printf("Введите элемент [%d][%d]: ", i + 1, j + 1);
                        scanf_s("%d", &matrix[i][j]);
                    }
                }
            }
            break;

        case 2:
            // Вывод матрицы
            if (matrix) {
                printf("Матрица:\n");
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        printf("%4d ", matrix[i][j]);
                    }
                    printf("\n");
                }
            }
            else {
                printf("Матрица не инициализирована.\n");
            }
            break;

        case 3:
            // Подсчет отрицательных элементов в строках, содержащих хотя бы один ноль
            if (matrix) {
                for (int i = 0; i < rows; i++) {
                    int has_zero = 0, negative_count = 0;
                    for (int j = 0; j < cols; j++) {
                        if (matrix[i][j] == 0) {
                            has_zero = 1;
                        }
                        if (matrix[i][j] < 0) {
                            negative_count++;
                        }
                    }
                    if (has_zero) {
                        printf("Строка %d содержит %d отрицательных элементов.\n", i + 1, negative_count);
                    }
                }
            }
            else {
                printf("Матрица не инициализирована.\n");
            }
            break;

        case 4:
            // Поиск седловых точек
            if (matrix) {
                printf("Седловые точки:\n");
                int found = 0;
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        int is_min_in_row = 1, is_min_in_col = 1;
                        for (int k = 0; k < cols; k++) {
                            if (matrix[i][k] < matrix[i][j]) {
                                is_min_in_row = 0;
                                break;
                            }
                        }
                        for (int k = 0; k < rows; k++) {
                            if (matrix[k][j] < matrix[i][j]) {
                                is_min_in_col = 0;
                                break;
                            }
                        }
                        if (is_min_in_row && is_min_in_col) {
                            printf("Седловая точка найдена на позиции [%d][%d]: %d\n", i + 1, j + 1, matrix[i][j]);
                            found = 1;
                        }
                    }
                }
                if (!found) {
                    printf("Седловых точек не найдено.\n");
                }
            }
            else {
                printf("Матрица не инициализирована.\n");
            }
            break;

        case 5:
            // Завершение программы
            if (matrix) {
                for (int i = 0; i < rows; i++) {
                    free(matrix[i]);
                }
                free(matrix);
            }
            printf("Завершение программы.\n");
            return 0;

        default:
            printf("Некорректный ввод. Повторите попытку.\n");
        }
    }
}
