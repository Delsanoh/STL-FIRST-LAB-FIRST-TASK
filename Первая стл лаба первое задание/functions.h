#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <vector>
#include <random>
#include <iomanip>
#include <limits>
#include <iostream>

void fillMatrix(std::vector<std::vector<int>>&, int, int);
void printMatrix(const std::vector<std::vector<int>>& );
void findMaxElement(const std::vector<std::vector<int>>&, int&, int&);

void deleteRowAndColumn(std::vector<std::vector<int>>& , int, int);
int calculateRowSum(const std::vector<int>& );
void sortRowsBySum(std::vector<std::vector<int>>&);

#endif