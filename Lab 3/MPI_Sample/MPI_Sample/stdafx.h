// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include "mpi.h"
#include <stdio.h>
#include <tchar.h>
#using <System.dll>

void Task1(int argc, char* argv[]);
void Task2(int argc, char* argv[]);
void Task3(int argc, char* argv[]);
void Task4(int argc, char* argv[]);
void Task5(int argc, char* argv[], int n);
void Task6(int argc, char* argv[], int n);
void Task7(int argc, char* argv[], int n);
void Task10(int argc, char* argv[]);

void Lab4_1(int argc, char* argv[]);
void Lab4_3(int argc, char*argv[]);
void Lab4_6(int argc, char*argv[]);
void FoxAlgorithm(int argc, char* argv[]);

double* СreateArray(int n);
double** СreateMatrix(int n);
void ClearMatrix(double** matrix, int n);
double* MatrixMultiplyVector(double** matrix, int n, int m, double* vector);
void ShowMatrix(double** matrix, int n, int m);
void ShowVector(double* vector, int n);


// TODO: reference additional headers your program requires here
