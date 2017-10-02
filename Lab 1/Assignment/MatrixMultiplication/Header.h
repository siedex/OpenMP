#pragma once
#include <omp.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#using <System.dll>

using namespace std;

double** RandomMatrix(int n, int m);
void DeallocateMatrix(double** matrix, int n, int m);
void Log(string str);
double MultiplyMatrix(double** matrix, int n, int m, int k, bool useOmp);
double** CreateMatrix(int n, int m);
double** RandomZeroOneMatrix(int n, int m);
double* RandomArray(int n);

void LaunchMatrixCalculations(int n, int m, int k, bool useOmp);
void LaunchNonZeroSelection(int n, int m, bool useOmp);
void LaunchArrayNumbers(int n, bool useOmp);
void LaunchArrayAvgNeghbours(int n, int count, bool useOmp);
void LaunchVectorMultiplication(int n, int m, bool useOmp);
