#include <iomanip>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

void mergeSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);



int main() {

    cout << "test" << endl;

    int arr1[10] = {9, 3, 4, 7, 10, 1, 2, 5, 6, 8};
    int length = sizeof(arr1)/sizeof(arr1[0]);
    mergeSort(arr1, 0, length-1);

    for (int i = 0; i < length; i++) {
        cout << arr1[i] << " ";
    }

    return 0;
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