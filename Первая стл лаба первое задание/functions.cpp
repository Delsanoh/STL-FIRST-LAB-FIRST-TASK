#include "functions.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <random>
#include <stdexcept>
#include <algorithm>

void fillMatrix(std::vector<std::vector<int32_t>>& matrix, int32_t minVal, int32_t maxVal) {
    if (matrix.empty()) {
        throw std::invalid_argument("Матрица пуста!");
    }

    if (minVal > maxVal) {
        throw std::invalid_argument("Минимальное значение не может быть больше максимального!");
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    // Проверка на переполнение
    if (maxVal > std::numeric_limits<int32_t>::max() ||
        minVal < std::numeric_limits<int32_t>::min()) {
        throw std::out_of_range("Значения выходят за пределы допустимого диапазона!");
    }

    std::uniform_int_distribution<int32_t> dist(minVal, maxVal);

    for (auto rowIt = matrix.begin(); rowIt != matrix.end(); ++rowIt) {
        for (auto colIt = rowIt->begin(); colIt != rowIt->end(); ++colIt) {
            *colIt = dist(gen);
        }
    }
}

void printMatrix(const std::vector<std::vector<int32_t>>& matrix) {
    if (matrix.empty()) {
        std::cout << "Матрица пуста!" << std::endl;
        return;
    }

    for (auto rowIt = matrix.begin(); rowIt != matrix.end(); ++rowIt) {
        for (auto colIt = rowIt->begin(); colIt != rowIt->end(); ++colIt) {
            std::cout << std::setw(5) << *colIt;
        }
        std::cout << std::endl;
    }
}

void findMaxElement(const std::vector<std::vector<int32_t>>& matrix, int32_t& maxRow, int32_t& maxCol) {
    if (matrix.empty() || matrix[0].empty()) {
        throw std::invalid_argument("Матрица пуста или не имеет столбцов!");
    }

    int32_t maxVal = std::numeric_limits<int32_t>::min();
    maxRow = -1;
    maxCol = -1;

    int32_t rowIndex = 0;
    for (auto rowIt = matrix.begin(); rowIt != matrix.end(); ++rowIt, ++rowIndex) {
        int32_t colIndex = 0;
        for (auto colIt = rowIt->begin(); colIt != rowIt->end(); ++colIt, ++colIndex) {
            if (*colIt > maxVal) {
                maxVal = *colIt;
                maxRow = rowIndex;
                maxCol = colIndex;
            }
        }
    }

    if (maxRow == -1 || maxCol == -1) {
        throw std::runtime_error("Не удалось найти максимальный элемент!");
    }
}

void deleteRowAndColumn(std::vector<std::vector<int32_t>>& matrix, int32_t rowToDelete, int32_t colToDelete) {
    if (matrix.empty()) {
        throw std::invalid_argument("Матрица пуста!");
    }

    // Проверка индексов
    if (rowToDelete < 0 || rowToDelete >= static_cast<int32_t>(matrix.size())) {
        throw std::out_of_range("Индекс строки для удаления вне диапазона!");
    }

    if (colToDelete < 0) {
        throw std::invalid_argument("Индекс столбца не может быть отрицательным!");
    }

    // Удаление строки
    auto rowIt = matrix.begin();
    std::advance(rowIt, rowToDelete);
    matrix.erase(rowIt);

    // Проверка, что матрица не пуста после удаления строки
    if (matrix.empty()) {
        return;
    }

    // Удаление столбца
    for (auto& row : matrix) {
        if (colToDelete < static_cast<int32_t>(row.size())) {
            auto colIt = row.begin();
            std::advance(colIt, colToDelete);
            row.erase(colIt);
        }
        else if (!row.empty()) {
            // Если индекс столбца вне диапазона, но строка не пуста
            throw std::out_of_range("Индекс столбца для удаления вне диапазона!");
        }
    }
}

int32_t calculateRowSum(const std::vector<int32_t>& row) {
    int32_t sum = 0;
    for (auto it = row.begin(); it != row.end(); ++it) {
        sum += *it;

        // Проверка на переполнение
        if ((*it > 0 && sum > std::numeric_limits<int32_t>::max() - *it) ||
            (*it < 0 && sum < std::numeric_limits<int32_t>::min() - *it)) {
            throw std::overflow_error("Переполнение при вычислении суммы строки!");
        }
    }
    return sum;
}

void sortRowsBySum(std::vector<std::vector<int32_t>>& matrix) {
    if (matrix.empty()) {
        return; // Ничего не делаем с пустой матрицей
    }

    int32_t n = static_cast<int32_t>(matrix.size());

    // Проверяем, что все строки имеют одинаковую длину
    size_t expectedSize = matrix[0].size();
    for (const auto& row : matrix) {
        if (row.size() != expectedSize) {
            throw std::invalid_argument("Все строки матрицы должны иметь одинаковую длину для сортировки!");
        }
    }

    // Пузырьковая сортировка с проверкой переполнения
    for (int32_t i = 0; i < n - 1; i++) {
        for (int32_t j = 0; j < n - i - 1; j++) {
            try {
                int32_t sum1 = calculateRowSum(matrix[j]);
                int32_t sum2 = calculateRowSum(matrix[j + 1]);

                if (sum1 > sum2) {
                    std::swap(matrix[j], matrix[j + 1]);
                }
            }
            catch (const std::overflow_error& e) {
                // Пробрасываем исключение дальше с дополнительной информацией
                throw std::overflow_error(std::string("Ошибка при сортировке строк: ") + e.what());
            }
        }
    }
}