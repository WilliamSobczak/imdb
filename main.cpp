#include <iomanip>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

void mergeSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);

void quickSort(int arr[], int low, int high);
int partition(int array[], int low, int high)
{
    int pivot = array[low];
    int up = low, down = high;

    while (up < down) {
        for (int j = up; j < high; j++) {
            if (array[up] > pivot) {
                break;
            }
            up ++;
        }
        for (int j = high; j > low; j--) {
            if (array[down] < pivot) {
                break;
            }
            down--;
        }
        if (up < down) {
            swap(array[up], array[down]);
        }
    }
    swap(array[low], array[down]);
    return down;
}



int main() {

    //Testing Merge Sort and quick sort on simple arrays
    int arr1[10] = {9, 3, 4, 7, 10, 1, 2, 5, 6, 8};
    int arr2[10] = {9, 3, 4, 7, 10, 1, 2, 5, 6, 8};
    int length = sizeof(arr1)/sizeof(arr1[0]);
    mergeSort(arr1, 0, length-1);
    quickSort(arr2, 0, length-1);

    for (int i = 0; i < length; i++) {
        cout << arr1[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < length; i++) {
        cout << arr2[i] << " ";
    }
    //end testing

    return 0;
}



void quickSort(int arr[], int low, int high) {
    if (low < high)
    {
        int pivot = partition(arr, low, high);
        quickSort(arr, low, pivot-1);
        quickSort(arr, pivot + 1, high);
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        
        // m is the point where the array is divided into two subarrays
        int mid = left + (right - left)/2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        //merge the sorted arrays
        merge(arr, left, mid, right);
    }
}

void merge(int arr[], int left, int mid, int right)
{
    //Create X <- arr[left.mid] & Y <- arr[mid+1...right]
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int X[n1], Y[n2];

    for (int i = 0; i < n1; i++) {
        X[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        Y[j] = arr[mid +1 + j];
    }

    //Merge the arrays X and Y into arr
    int i, j, k;
    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (X[i] <= Y[j]) {
            arr[k] = X[i];
            i++;
        }
        else {
            arr[k] = Y[j];
            j++;
        }
        k++;
    }

    //when we run out of elements in either X or Y append the remaining elements

    while (i < n1) {
        arr[k] = X[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = Y[j];
        j++;
        k++;
    }
}