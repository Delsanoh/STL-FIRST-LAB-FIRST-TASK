#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <vector>
#include <random>
#include <iomanip>
#include <limits>
#include <iostream>

void fillMatrix(std::vector<std::vector<int32_t>>&, int32_t, int32_t);
void printMatrix(const std::vector<std::vector<int32_t>>& );
void findMaxElement(const std::vector<std::vector<int32_t>>&, int32_t&, int32_t&);

void deleteRowAndColumn(std::vector<std::vector<int32_t>>& , int32_t, int32_t);
int calculateRowSum(const std::vector<int32_t>& );
void sortRowsBySum(std::vector<std::vector<int32_t>>&);

#endif