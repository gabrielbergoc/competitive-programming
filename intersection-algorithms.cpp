/*
    Gabriel Bergoc
    2021-09-07

--------------------------------------------------------------------------------

    Various ways of counting the size of the intersection between two vectors:
    alg0: two nested loops
    alg1: set and loop
    alg2: unordered set and loop
    alg3: sorting and loop

--------------------------------------------------------------------------------

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

--------------------------------------------------------------------------------

    input:
    size of vector A
    size of vector B
    elements of vector A
    elements of vector B

    output:
    number of elements in intersection between vectors A and B

--------------------------------------------------------------------------------

    test cases:

    in:
    5 5
    1 2 3 4 5
    1 2 3 4 5
    out:
    5

    in:
    5 5
    0 1 2 3 4
    5 6 7 8 9
    out:
    0

    in:
    6 6
    1 2 3 4 5 6
    4 5 6 7 8 9
    out:
    3

*/

#include <bits/stdc++.h>

using namespace std;

template <typename T>
int alg0(vector<T> vecA, vector<T> vecB);
template <typename T>
int alg1(vector<T> vecA, vector<T> vecB);
template <typename T>
int alg2(vector<T> vecA, vector<T> vecB);
template <typename T>
int alg3(vector<T> vecA, vector<T> vecB);

int main() {

    // data input:
    int sizeA, sizeB;
    cin >> sizeA >> sizeB;

    vector<int> vecA;
    vector<int> vecB;

    for (int x, i = 0; i < sizeA; i++) {
        cin >> x;
        vecA.push_back(x);
    }
    for (int x, i = 0; i < sizeB; i++) {
        cin >> x;
        vecB.push_back(x);
    }

    cout << "Using two nested loops: " << alg0(vecA, vecB) << "\n";
    cout << "Using set and loop: " << alg1(vecA, vecB) << "\n";
    cout << "Using unordered set and loop: " << alg2(vecA, vecB) << "\n";
    cout << "Using sorting: " << alg3(vecA, vecB) << "\n";
}

// -------------------- FUNCTION DEFINITIONS -------------------------------- //

// two nested loops
// O(n²)
template <typename T>
int alg0(vector<T> vecA, vector<T> vecB) {

    int count = 0;

    for (int i = 0; i < vecA.size(); i++) {
        for (int j = 0; j < vecB.size(); j++) {
            if (vecB[j] == vecA[i]) {
                count++;
            }
        }
    }

    return count;
}

// set and loop
// O(n log(n))
template <typename T>
int alg1(vector<T> vecA, vector<T> vecB) {

    int count = 0;

    // construct set with larger vector to minimize number of comparisons
    if (vecA.size() > vecB.size()) {
        set<T> setA(vecA.begin(), vecA.end());
        for (T x : vecB) {
            if (setA.count(x)) {
                count++;
            }
        }
    } else {
        set<T> setB(vecB.begin(), vecB.end());
        for (T x : vecA) {
            if (setB.count(x)) {
                count++;
            }
        }
    }

    return count;
}

// unordered set and loop
// O(n)
template <typename T>
int alg2(vector<T> vecA, vector<T> vecB) {

    int count = 0;

    // construct set with larger vector to minimize number of comparisons
    if (vecA.size() > vecB.size()) {
        unordered_set<T> setA(vecA.begin(), vecA.end());
        for (T x : vecB) {
            if (setA.count(x)) {
                count++;
            }
        }
    } else {
        unordered_set<T> setB(vecB.begin(), vecB.end());
        for (T x : vecA) {
            if (setB.count(x)) {
                count++;
            }
        }
    }

    return count;
}

// sorting and loop
// O(n log(n))
// surprisingly, this algorithm is faster than alg2, even though alg2 is O(n)
template <typename T>
int alg3(vector<T> vecA, vector<T> vecB) {

    sort(vecA.begin(), vecA.end());
    sort(vecB.begin(), vecB.end());

    int i = 0, j = 0, count = 0;

    while (i < vecA.size() && j < vecB.size()) {
        if (vecA[i] == vecB[j]) {
            count++;
            i++;
            j++;
        } else if (vecA[i] < vecB[j]) {
            i++;
        } else {
            j++;
        }
    }

    while (i < vecA.size()) {
        if (vecA[i] == vecB[j]) {
            count++;
            i++;
        } else {
            i++;
        }
    }

    while (j < vecB.size()) {
        if (vecA[i] == vecB[j]) {
            count++;
            j++;
        } else {
            j++;
        }
    }

    return count;
}
