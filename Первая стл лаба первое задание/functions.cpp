#include "functions.h"

void fillMatrix(std::vector<std::vector<int32_t>>& matrix, int32_t minVal, int32_t maxVal) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minVal, maxVal);

    for (std::vector<std::vector<int32_t>>::iterator rowIt = matrix.begin(); rowIt != matrix.end(); ++rowIt) {
        for (std::vector<int32_t>::iterator colIt = rowIt->begin(); colIt != rowIt->end(); ++colIt) {
            *colIt = dist(gen);
        }
    }
}

void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (std::vector<std::vector<int32_t>>::const_iterator rowIt = matrix.begin(); rowIt != matrix.end(); ++rowIt) {
        for (std::vector<int32_t>::const_iterator colIt = rowIt->begin(); colIt != rowIt->end(); ++colIt) {
            std::cout << std::setw(5) << *colIt;
        }
        std::cout << std::endl;
    }
}


void findMaxElement(const std::vector<std::vector<int32_t>>& matrix, int32_t& maxRow, int32_t& maxCol) {
    int32_t maxVal = std::numeric_limits<int32_t>::min();
    maxRow = -1;
    maxCol = -1;

    int32_t rowIndex = 0;
    for (std::vector<std::vector<int32_t>>::const_iterator rowIt = matrix.begin(); rowIt != matrix.end(); ++rowIt, ++rowIndex) {
        int colIndex = 0;
        for (std::vector<int32_t>::const_iterator colIt = rowIt->begin(); colIt != rowIt->end(); ++colIt, ++colIndex) {
            if (*colIt > maxVal) {
                maxVal = *colIt;
                maxRow = rowIndex;
                maxCol = colIndex;
            }
        }
    }
}

void deleteRowAndColumn(std::vector<std::vector<int32_t>>& matrix, int32_t rowToDelete, int32_t colToDelete) {
    if (rowToDelete >= 0 && rowToDelete < (int32_t)matrix.size()) {
        std::vector<std::vector<int32_t>>::iterator it = matrix.begin();
        std::advance(it, rowToDelete);
        matrix.erase(it);
    }

    if (colToDelete >= 0) {
        for (std::vector<std::vector<int32_t>>::iterator rowIt = matrix.begin(); rowIt != matrix.end(); ++rowIt) {
            if (colToDelete < (int32_t)rowIt->size()) {
                std::vector<int32_t>::iterator colIt = rowIt->begin();
                std::advance(colIt, colToDelete);
                rowIt->erase(colIt);
            }
        }
    }
}

int32_t calculateRowSum(const std::vector<int32_t>& row) {
    int32_t sum = 0;
    for (std::vector<int32_t>::const_iterator it = row.begin(); it != row.end(); ++it) {
        sum += *it;
    }
    return sum;
}

void sortRowsBySum(std::vector<std::vector<int32_t>>& matrix) {
    int32_t n = matrix.size();
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            int32_t sum1 = calculateRowSum(matrix[j]);
            int32_t sum2 = calculateRowSum(matrix[j + 1]);

            if (sum1 > sum2) {
                std::swap(matrix[j], matrix[j + 1]);
            }
        }
    }
}