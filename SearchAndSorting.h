#pragma once
#include <string>


int Search(int* arrptr, int key);
void Swap(int* arrptr, int i, int j);
void QuickSortRecursive(int* arrptr, int start, int end);
void QuickSortNotRecursive(int* arrptr, int start, int end);
int Partition(int* arrptr, int position, int start, int end);
int BinarySearchRecursive(int* arrptr, int start, int end, int key);
int BinarySearchNotRecursive(int* arrptr, int start, int end, int key);
void CompareExecutionRate(int* unsortedArray, int* sortedArray);
void PrintArray(int* arr, int n, std::string title);
void checkSortedArray(int* arr, int n, std::string title);
void CheckSortingMethods();



