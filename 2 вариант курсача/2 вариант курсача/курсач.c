#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>  
#include <stdlib.h>  
#include <locale.h>  
#include <math.h>  
#include <time.h>  // ��� ������������� srand

int main() {
    setlocale(LC_CTYPE, "RUS");

    puts("***************************************************************************");
    puts("*                                                                         *");
    puts("*�������� ������ �� ��������� \"����� ���������������� � ��������������\"   *");
    puts("*����:\"���������� ������������� � ���������� �������\"                     *");
    puts("*���������:�������.�.�,������ ���-241                                     *");
    puts("*                                                                         *");
    puts("***************************************************************************");

    puts("��������� ������� ������,\n���������� ����� � ������, \n����� ������������� ��������� � ��������� �������� ����� �� ������ ������������.");

    puts("***************************************************************************");

    int rows, cols;
    int choice, randomize;
    int** matrix = NULL;

    while (1) {
        printf("\n����:\n");
        printf("1. ���������������� �������\n");
        printf("2. �������� �������\n");
        printf("3. ���������� ������������� �������� � ������� � ������\n");
        printf("4. ����� �������� �����\n");
        printf("5. ��������� ���������\n");
        printf("�������� ��������: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            // ������������� �������
            if (matrix) {
                for (int i = 0; i < rows; i++) {
                    free(matrix[i]);
                }
                free(matrix);
            }
            printf("������� ���������� ����� � ��������: ");
            scanf_s("%d %d", &rows, &cols);
            printf("�������� ������ �������������:\n1. ��������� �����\n2. ���� � �������\n");
            scanf_s("%d", &randomize);

            matrix = (int**)malloc(rows * sizeof(int*));
            for (int i = 0; i < rows; i++) {
                matrix[i] = (int*)malloc(cols * sizeof(int));
            }

            if (randomize == 1) {
                srand(time(0));
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        matrix[i][j] = rand() % 21 - 10; // ��������� ����� �� -10 �� 10
                    }
                }
            }
            else {
                printf("������� �������� ������� %d%d:\n", rows, cols);
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        printf("������� ������� [%d][%d]: ", i + 1, j + 1);
                        scanf_s("%d", &matrix[i][j]);
                    }
                }
            }
            break;

        case 2:
            // ����� �������
            if (matrix) {
                printf("�������:\n");
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        printf("%4d ", matrix[i][j]);
                    }
                    printf("\n");
                }
            }
            else {
                printf("������� �� ����������������.\n");
            }
            break;

        case 3:
            // ������� ������������� ��������� � �������, ���������� ���� �� ���� ����
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
                        printf("������ %d �������� %d ������������� ���������.\n", i + 1, negative_count);
                    }
                }
            }
            else {
                printf("������� �� ����������������.\n");
            }
            break;

        case 4:
            // ����� �������� �����
            if (matrix) {
                printf("�������� �����:\n");
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
                            printf("�������� ����� ������� �� ������� [%d][%d]: %d\n", i + 1, j + 1, matrix[i][j]);
                            found = 1;
                        }
                    }
                }
                if (!found) {
                    printf("�������� ����� �� �������.\n");
                }
            }
            else {
                printf("������� �� ����������������.\n");
            }
            break;

        case 5:
            // ���������� ���������
            if (matrix) {
                for (int i = 0; i < rows; i++) {
                    free(matrix[i]);
                }
                free(matrix);
            }
            printf("���������� ���������.\n");
            return 0;

        default:
            printf("������������ ����. ��������� �������.\n");
        }
    }
}
