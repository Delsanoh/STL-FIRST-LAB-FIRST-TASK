#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <limits>
#include "functions.h"

int main() {
    std::setlocale(LC_ALL, "Russian");
    int32_t rows{}, cols{};
    int32_t minVal{}, maxVal{};

    std::cout << "Введите количество строк (1-100): ";
    std::cin >> rows;
    std::cout << "Введите количество столбцов (1-100): ";
    std::cin >> cols;

    if (rows <= 0 || rows > 100 || cols <= 0 || cols > 100) {
        std::cout << "Некорректные размеры матрицы!" << std::endl;
        return 1;
    }

    std::vector<std::vector<int32_t>> matrix(rows, std::vector<int32_t>(cols));

    std::cout << "Введите минимальное значение: ";
    std::cin >> minVal;
    std::cout << "Введите максимальное значение: ";
    std::cin >> maxVal;

    fillMatrix(matrix, minVal, maxVal);

    std::cout << "\nИсходная матрица:" << std::endl;
    printMatrix(matrix);

    int32_t maxRow{}, maxCol{};
    findMaxElement(matrix, maxRow, maxCol);

    std::cout << "\nМаксимальный элемент найден в позиции ["
        << maxRow << "][" << maxCol << "] = "
        << matrix[maxRow][maxCol] << std::endl;

    deleteRowAndColumn(matrix, maxRow, maxCol);

    std::cout << "\nМатрица после удаления строки " << maxRow
        << " и столбца " << maxCol << ":" << std::endl;
    if (!matrix.empty() && !matrix[0].empty()) {
        printMatrix(matrix);
    }
    else {
        std::cout << "Матрица пуста!" << std::endl;
    }

    sortRowsBySum(matrix);

    std::cout << "\nМатрица после сортировки строк по возрастанию сумм:" << std::endl;
    if (!matrix.empty() && !matrix[0].empty()) {
        printMatrix(matrix);

        std::cout << "\nСуммы строк:" << std::endl;
        for (size_t i = 0; i < matrix.size(); i++) {
            std::cout << "Строка " << i << ": сумма = "
                << calculateRowSum(matrix[i]) << std::endl;
        }
    }

    return 0;
}