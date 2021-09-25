/*
    Gabriel Bergoc
    2021-09-07

    with the precious help of @rafaelalmeida9

    Copyright (C) 2021 Gabriel Bergoc
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include <bits/stdc++.h>

using namespace std;

// --------- FUNCTION PROTOTYPES ------------- //
template <typename T>
void mergeSort(T* vec, int begin, int end);

template <typename T>
void mergeSortIt(typename vector<T>::iterator begin, typename vector<T>::iterator end);

// --------- MAIN ------------- //
int main() {
    int vec1_size;
    cin >> vec1_size;
    //int vec2_size;
    //cin >> vec2_size;

    int vec1[vec1_size];
    vector<int> vec2;

    for (int i = 0; i < vec1_size; i++) {
        cin >> vec1[i];
        vec2.push_back(vec1[i]);
    }

    cout << "\nUsing C arrays" << endl;
    mergeSort(vec1, 0, vec1_size - 1);
    for (int i = 0; i < vec1_size; i++) {
        cout << vec1[i] << " ";
    }
    cout << endl;

    cout << "\nUsing C++ vector" << endl;
    mergeSortIt<int>(vec2.begin(), vec2.end());
    for (int i = 0; i < vec1_size; i++) {
        cout << vec2[i] << " ";
    }
    cout << endl;
}

// --------- FUNCTION DEFINITIONS ------------- //

// USING C ARRAYS
// parameters: first and last positions

template <typename T>
void mergeSort(T* vec, int begin, int end) {

    // recursion base (if begin == end, we're looking into a 1-sized array)
    if (begin >= end) {
        return;
    }

    int mid = (end + begin) / 2;
    mergeSort(vec, begin, mid);             // keep calling mergeSort, each time
    mergeSort(vec, mid + 1, end);     // halving the array

    int i = begin;      // index to traverse first half
    int j = mid + 1;    // index to traverse second half
    vector<T> aux;      // auxiliary vector to save ordered elements

    // compare each pair of elements of both halves, save the smallest to aux
    while (i <= mid && j <= end) {
        if (vec[i] < vec[j]) {
            aux.push_back(vec[i]);
            i++;
        } else {
            aux.push_back(vec[j]);
            j++;
        }
    }

    // keep traversing first half if we reach end of second half first
    while (i <= mid) {
        aux.push_back(vec[i]);
        i++;
    }

    // keep traversing second half if we reach end of first half first
    while (j <= end) {
        aux.push_back(vec[j]);
        j++;
    }

    // copy ordered elements to original array
    int k;
    for (i = begin, k = 0; i <= end; i++, k++) {
        vec[i] = aux[k];
    }
}

// USING C++ VECTORS
// parameters: begin and end iterators

template <typename T>
void mergeSortIt(typename vector<T>::iterator begin, typename vector<T>::iterator end) {

    // recursion base (if distance(begin, end) <= 1,
    // we're looking into a 1-sized array)
    if (distance(begin, end) <= 1) {
        return;
    }

    auto mid = begin + distance(begin, end) / 2;

    mergeSortIt<T>(begin, mid);     // keep calling mergeSort, each time
    mergeSortIt<T>(mid, end);       // halving the array

    auto midIter = mid;         // iterator to traverse first half
    auto beginIter = begin;     // iterator to traverse second half
    vector<T> aux;              // auxiliary vector to save ordered elements

    // compare each pair of elements of both halves, save the smallest to aux
    while (distance(beginIter, mid) >= 1 && distance(midIter, end) >= 1) {
        if (*beginIter < *midIter) {
            aux.push_back(*beginIter);
            beginIter++;
        } else {
            aux.push_back(*midIter);
            midIter++;
        }
    }

    // keep traversing first half if we reach end of second half first
    while (distance(beginIter, mid) >= 1) {
        aux.push_back(*beginIter);
        beginIter++;
    }

    // keep traversing second half if we reach end of first half first
    while (distance(midIter, end) >= 1) {
        aux.push_back(*midIter);
        midIter++;
    }

    // copy ordered elements to original vector
    for (int i = 0; distance(begin, end) >= 1; begin++, i++) {
        *begin = aux[i];
    }

}