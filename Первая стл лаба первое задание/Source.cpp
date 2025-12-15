#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include "functions.h"

int main() {
    try {
        std::setlocale(LC_ALL, "Russian");
        int32_t rows{}, cols{};
        int32_t minVal{}, maxVal{};

        std::cout << "Введите количество строк (1-100): ";
        std::cin >> rows;
        std::cout << "Введите количество столбцов (1-100): ";
        std::cin >> cols;

        if (rows <= 0 || rows > 100 || cols <= 0 || cols > 100) {
            throw std::invalid_argument("Некорректные размеры матрицы! Диапазон: 1-100.");
        }

        std::vector<std::vector<int32_t>> matrix(rows, std::vector<int32_t>(cols));

        std::cout << "Введите минимальное значение: ";
        std::cin >> minVal;
        std::cout << "Введите максимальное значение: ";
        std::cin >> maxVal;

        if (minVal > maxVal) {
            throw std::invalid_argument("Минимальное значение не может быть больше максимального!");
        }

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
            size_t size = matrix.size();
            for (size_t i = 0; i < size; i++) {
                std::cout << "Строка " << i << ": сумма = "
                    << calculateRowSum(matrix[i]) << std::endl;
            }
        }
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Ошибка ввода данных: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Ошибка диапазона: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "Неизвестная ошибка: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Критическая ошибка!" << std::endl;
        return 1;
    }

    return 0;
}