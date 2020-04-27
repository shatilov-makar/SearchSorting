#include <ctime> 
#include <iostream>
#include <stack>
#include "SearchAndSorting.h"
#include <thread>
#include <string>


using namespace std;
constexpr int arrSizeBinarySearch = 100;
constexpr int arrSizeSearch = 10000;


int main()
{
    CheckSortingMethods();
    int* unsortedArray = new int[arrSizeSearch];
    for (int i = 0; i < arrSizeSearch; i++)
        unsortedArray[i] = rand() % 2001 - 1000;
  
    int* sortedArray = new int[arrSizeBinarySearch];
    for (int i = 0; i < arrSizeBinarySearch; i++)
        sortedArray[i] = rand() % 21 - 10;
    
    PrintArray(sortedArray, 50, "Unsorted array");
    QuickSortNotRecursive(sortedArray, 0, arrSizeBinarySearch - 1);
    PrintArray(sortedArray, 50, "Sorted array by \'QuickSortNotRecursive\'");
    CompareExecutionRate(unsortedArray, sortedArray);
    delete[] unsortedArray;
    delete[] sortedArray;
    return 0;
}

int Search(int* arrptr, int key)
{
    for (int i = 0; i < arrSizeSearch; i++)
        if (arrptr[i] == key)
            return i;
    return -1;
}

void QuickSortRecursive(int* arr, int start, int end)
{
    if (start == end)
        return;
    int pivot = arr[end];
    int storeIndex = start;
    for (int i = start; i <= end - 1; i++)
    {
        if (arr[i] <= pivot)
        {
            Swap(arr, i, storeIndex);
            storeIndex++;
        }
    }
    Swap(arr, end, storeIndex);
    if (storeIndex > start) QuickSortRecursive(arr, start, storeIndex - 1);
    if (storeIndex < end) QuickSortRecursive(arr, storeIndex + 1, end);
}

void QuickSortNotRecursive(int* arr, int start, int end)
{
    stack<int> stack;
    stack.push(start);
    stack.push(end);
    while (!stack.empty())
    {
        int end = stack.top();
        stack.pop();
        int start = stack.top();
        stack.pop();
        if (end - start < 2)
            continue;
        int p = (end + start) / 2;
        p = Partition(arr, p, start, end);
        stack.push(p + 1);
        stack.push(end);
        stack.push(start);
        stack.push(p);
    }
}

int Partition(int* arr, int position, int start, int end)
{
    int i = start;
    int j = end - 2;
    int pivot = arr[position];
    Swap(arr, position, end - 1);
    while (i < j)
    {
        if (arr[i] < pivot)
            i++;
        else if (arr[j] >= pivot)
            j--;
        else
            Swap(arr, i++, j);
    }
    int idx = j;
    if (arr[j] < pivot)
        idx++;
    Swap(arr, end - 1, idx);
    return idx;
}

int BinarySearchRecursive(int* arrptr, int start, int end, int key)
{
    if (start >= end)
    {
        if (arrptr[end] == key)
            return end;
        return -1;
    }
    int middle = (start + end) / 2;
    if (key <= arrptr[middle])
        BinarySearchRecursive(arrptr, start, middle, key);
    else
        BinarySearchRecursive(arrptr, middle + 1, end, key);
}

int BinarySearchNotRecursive(int* arrptr, int start, int end, int key)
{                         
    int left = start;
    int right = end;
    while (left < right)
    {
        int mid = (left + right) / 2;
        if (key <= arrptr[mid])
            right = mid;
        else
            left = mid + 1;
    }
    if (arrptr[left] == key)
        return left;  
    return -1;
}

void CompareExecutionRate(int* unsortedArray, int* sortedArray)
{
    const int keyElement = 9;
    auto startSearch = chrono::high_resolution_clock::now();
    Search(unsortedArray, keyElement);
    auto endSearch = chrono::high_resolution_clock::now();
    chrono::duration<float> searchDuration = endSearch - startSearch;

    startSearch = chrono::high_resolution_clock::now();
    int res = BinarySearchNotRecursive(sortedArray, 0, arrSizeBinarySearch - 1, keyElement);
    endSearch = chrono::high_resolution_clock::now();
    chrono::duration<float> binarySearchDuration = endSearch - startSearch;
    if (res != -1)
        cout << "Element founded by \'BinarySearchNotRecursive\'  " <<sortedArray[res] << endl<<endl;
    else cout << "Element " << keyElement <<" was not founded by \'BinarySearchNotRecursive\'" << endl<<endl;

    cout << "Searching in sorted array faster than searching in an unsorted array by " << searchDuration.count() - binarySearchDuration.count() << " s"<<endl;
}

void PrintArray(int* arr, int n, string title)
{
    cout << title << endl;
    for (int i = 0; i < n; i++)
        cout << arr[i] << ' ';
    cout << endl<<endl;
}

void Swap(int* arrptr, int i, int j)
{
    int t = arrptr[i];
    arrptr[i] = arrptr[j];
    arrptr[j] = t;
}

void CheckSortingMethods()
{
    int* array = new int[arrSizeBinarySearch];
    for (int i = 0; i < arrSizeBinarySearch; i++)
        array[i] = rand() % 2001 - 1000;
    QuickSortNotRecursive(array, 0, arrSizeBinarySearch - 1);
    checkSortedArray(array, arrSizeBinarySearch - 1, "QuickSortNotRecursive");
    for (int i = 0; i < arrSizeBinarySearch; i++)
        array[i] = rand() % 2001 - 1000;
    QuickSortRecursive(array, 0, arrSizeBinarySearch - 1);
    checkSortedArray(array, arrSizeBinarySearch - 1, "QuickSortRecursive");
}

void checkSortedArray(int* arr, int n, string title)
{
    for (int i = 0; i < n - 1; i++)
        if (arr[i] > arr[i + 1])
        {
            cout << "\'" + title + "\'" + " DOESN'T work correctly!" << endl;
            return;
        }
    cout << "\'" + title + "\'" + " work correctly!" << endl;
}
