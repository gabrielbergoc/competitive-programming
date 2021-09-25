/*
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
*/

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <utility>
#include <algorithm>
#include <thread>
#include "clearscreen.h"

template <typename T>
void printPowerSetGeeks(typename std::set<T>::iterator setBegin, typename std::set<T>::iterator setEnd, std::vector<T>& aux);
template <typename T>
void printPowerSetBook(typename std::set<T>::iterator setBegin, typename std::set<T>::iterator setEnd, std::vector<T>& aux);
template <typename T>
void printPowerSetIt(typename std::set<T>::iterator setBegin, typename std::set<T>::iterator setEnd);
template <typename T>
void printPermutations(typename std::vector<T>::iterator vecBegin, typename std::vector<T>::iterator vecEnd, std::vector<T>& permutation, bool* chosen, int size);
void printAnagrams(std::string str, std::string aux, bool* chosen);
void backtrackingQueen(int i, int n, int* columns, int* diag1, int* diag2, int* count);
void pathSearch(std::pair<int, int> dir, int i, int j, int nRows, int nCols, int** grid, int* visitCounter, int* solveCounter, int print, int delay);
bool subSum(std::vector<int>::iterator vecBegin, std::vector<int>::iterator vecEnd, int target);

int main() {

    int option = 0;
    
    // variable declarations of case 1
    int size;   // size of the set to be tested
    std::set<int> setA;
    std::string strA, strB;
    std::vector<int> vecA, vecB;
    bool *array1, *array2;
    
    // variable declarations of case 2
    int n = 0;  // chessboard size for the queen problem
    int *columns;
    int *diag1;
    int *diag2;
    int count = 0;
    int nRows, nCols;
    std::pair<int, int> pairA;
    
    // variable declarations of case 3
    int tgt;
    int **grid;
    int vcount = 1;
    int scount = 0;
    std::vector<int> vec1;
    int print = 0;
    int delay = 0;
    
    do {
        std::cout << "Choose an option from the menu below:\n"
                     "0) Exit\n"
                     "1) Permutation algorithms\n"
                     "2) Backtracking algorithms\n"
                     "3) Meet-in-the-middle algorithm\n";
        
        std::cin >> option;
    
        switch (option) {
            
            case 0:
                break;
            
            // permutations
            case 1:
                std::cout << "Enter:\n"
                        "1) the size of the first set to be tested;\n"
                        "2) the elements of the first set;\n"
                        "3) the string to permute (max 4 chars).\n";
                
                std::cin >> size;   // set size
                for (int x, i = 0; i < size; i++) {
                    std::cin >> x;
                    setA.insert(x); // input set elements
                }
                
                do {
                    std::cin >> strA;    // string to print all anagrams
                    if (strA.size() > 4) {
                        std::cout << "Please enter a string with 4 chars max.\n";
                    }
                } while (strA.size() > 4);
    
                for (int x: setA) {
                    vecB.push_back(x);
                }
        
                array1 = (bool *) calloc(size, sizeof(bool));
                array2 = (bool *) calloc(size, sizeof(bool));
        
                // output on the console
                std::cout << "Using Geeks for Geeks algorithm:\n";
                printPowerSetGeeks(setA.begin(), setA.end(), vecA);
                std::cout << "Using Laaksonen's algorithm:\n";
                printPowerSetBook(setA.begin(), setA.end(), vecA);
                std::cout << "Using iterative algorithm:\n";
                printPowerSetIt<int>(setA.begin(), setA.end());
                std::cout << "Permutations:\n";
                printPermutations<int>(vecB.begin(), vecB.end(), vecA, array1, size);
                std::cout << "Anagrams:\n";
                printAnagrams(strA, strB, array2);
                
                // clear everything before next case
                setA.clear();
                vecA.clear();
                vecB.clear();
                strA.clear();
                strB.clear();
                
                break;
                
            // backtracking
            case 2:
                std::cout << "Please enter:\n"
                        "1) the size of the chessboard to place the queens;\n"
                        "2) the number of rows and columns of grid to search for paths.\n"
                        "3) if you want to print the search (1 - yes/ 0 - no).\n"
                        "4) delay in milliseconds of screen update (only if you provide a 1).\n";
                
                // backtracking queen problem
                std::cin >> n;  // size of the chessboard
                columns = (int *) calloc(n, sizeof(int));
                diag1 = (int *) calloc(2 * n - 1, sizeof(int));
                diag2 = (int *) calloc(2 * n - 1, sizeof(int));
                backtrackingQueen(0, n, columns, diag1, diag2, &count);
                std::cout << "Number of ways to place n queens in a nxn chessboard:\n" << count << std::endl;
        
                // pruned backtracking test
                std::cin >> nRows;  // grid's number of rows
                std::cin >> nCols;  // grid's number of columns
                pairA = std::make_pair(1, 0);
                grid = (int **) calloc(nRows, sizeof(int *));
                for (int i = 0; i < nRows; i++) {
                    *(grid + i) = (int *) calloc(nCols, sizeof(int));
                }
                std::cin >> print >> delay;
                grid[0][0] = 1;
                pathSearch(pairA, 0, 0, nRows, nCols, grid, &vcount, &scount, print, delay);
                std::cout << scount << std::endl;
                
                break;
            
            // meet in the middle
            case 3:
                std::cout << "Please enter:\n"
                             "1) size of the vector;\n"
                             "2) target sum;\n"
                             "3) elements of the vector.\n";
                
                std::cin >> size;
                std::cin >> tgt;
        
                for (int x, i = 0; i < size; i++) {
                    std::cin >> x;
                    vec1.push_back(x);
                }
        
                std::cout << subSum(vec1.begin(), vec1.end(), tgt) << std::endl;
                
                // clear vector before next case
                vec1.clear();
                
                break;
                
            default:
                std::cout << "Invalid option.\n";
        }
    } while(option != 0);
}


// receives set iterators, an empty auxiliary std::vector and prints all subsets
template <typename T>
void printPowerSetGeeks(typename std::set<T>::iterator setBegin, typename std::set<T>::iterator setEnd, std::vector<T>& aux) {

    // print subsets
    if (aux.empty()) {
        std::cout << "{empty set}" << std::endl;
    } else {
        for (T x: aux) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }

    // for each set element
    for (auto it = setBegin; it != setEnd; it++) {

        // include the element
        aux.push_back(*it);

        // call recursion for next element
        printPowerSetGeeks(++it, setEnd, aux);
        it--;

        // exclude the element
        aux.pop_back();
    }
}

// receives set iterators, an empty auxiliary vector and prints all subsets
template <typename T>
void printPowerSetBook(typename std::set<T>::iterator setBegin, typename std::set<T>::iterator setEnd, std::vector<T>& aux) {

    // recursion base, print subset
    if (setBegin == setEnd) {
        if (aux.empty()) {
            std::cout << "{empty set}" << std::endl;
        } else {
            for (T x : aux) {
                std::cout << x << " ";
            } std::cout << std::endl;
        }
    } else {

        // call recursion without the element
        printPowerSetBook(++setBegin, setEnd, aux);
        setBegin--;

        // include the element and call recursion
        aux.push_back(*setBegin);
        printPowerSetBook(++setBegin, setEnd, aux);
        setBegin--;

        // exclude element before returning to previous call
        aux.pop_back();
    }
}

// receives set iterators and print all subsets
template <typename T>
void printPowerSetIt(typename std::set<T>::iterator setBegin, typename std::set<T>::iterator setEnd) {

    int size = distance(setBegin, setEnd);

    // nested loops generate all binary numbers from 0 to 2^size - 1
    // each digit will represent a set element
    // 0 means the element is not present in subset
    // 1 means it is present
    // e.g. in a set of size 3, 000 means it is the empty set,
    // 100 means only the 3rd element is in subset
    for (int i = 0; i < (1 << size); i++) {

        std::vector<T> aux;  // auxiliary std::vector

        // this loop will check each digit and push back the elements that
        // belong to each subset to auxiliary std::vector
        // e.g. when i = 3 (11 in binary) it will push back 1st and 2nd elements
        for (auto it = setBegin; it != setEnd; it++) {
            if (i & (1 << distance(setBegin, it))) {
                aux.push_back(*it);
            }
        }

        // print subset
        if (aux.empty()) {
            std::cout << "{empty set}" << std::endl;
        } else {
            for (T x : aux) {
                std::cout << x << " ";
            } std::cout << std::endl;
        }
    }
}

// c++ standard library has a function to permute elements in a std::vector:
// void next_permutation(iterator begin, iterator end);

template <typename T>
void printPermutations(typename std::vector<T>::iterator vecBegin, typename std::vector<T>::iterator vecEnd, std::vector<T>& permutation, bool* chosen, int size) {
    
    // recursion base; print current permutation
    if (permutation.size() == size) {
        for (T x : permutation) {
            std::cout << x << " ";
        } std::cout << std::endl;
    } else {
        
        // loop through elements
        for (int i = 0; i < size; i++) {
            
            // if element is already in permutation, skip
            if (chosen[i]) continue;
            
            // choose element
            chosen[i] = true;
            permutation.push_back(*(vecBegin + i));
            
            // call recursion to choose next element
            printPermutations<T>(vecBegin, vecEnd, permutation, chosen, size);
            
            // pop back element before returning to allow next permutation
            chosen[i] = false;
            permutation.pop_back();
        }
    }
}

void printAnagrams(std::string str, std::string aux, bool* chosen) {
    
    // recursion base; print if all letters are chosen
    if (aux.size() == str.size()) {
        std::cout << aux << std::endl;
    } else {
        
        // loop through std::string to choose different letters
        for (int i = 0; i < str.size(); i++) {
            
            // if letter was already chosen, skip
            if (chosen[i]) continue;
            
            // choose letter
            aux.push_back(str[i]);
            chosen[i] = true;
            
            // call recursion for next position
            printAnagrams(str, aux, chosen);
            
            // pop back letter to fill position with another letter
            aux.pop_back();
            chosen[i] = false;
            
        }
    }
}

// algorithm to check and count solutions for the queen problem
void backtrackingQueen(int i, int n, int* columns, int* diag1, int* diag2, int* count) {
    if (i == n) {
        (*count)++;
    } else {
        for (int j = 0; j < n; j++) {
            if (columns[j] || diag1[i + j] || diag2[j - i + n - 1]) {
                continue;
            }
            columns[j] = diag1[i + j] = diag2[j - i + n - 1] = 1;
            backtrackingQueen(i + 1, n, columns, diag1, diag2, count);
            columns[j] = diag1[i + j] = diag2[j - i + n - 1] = 0;
        }
    }
}

bool reachedBounds(int i, int j, std::pair<int, int> dir, int nRows, int nCols) {
    return i + dir.first < 0 || i + dir.first == nRows ||
            j + dir.second < 0 || j + dir.second == nCols;
}

bool alreadyVisited(int i, int j, std::pair<int, int> dir, int** grid, int nRows, int nCols) {
    return !reachedBounds(i, j, dir, nRows, nCols) &&
            grid[i + dir.first][j + dir.second] != 0;
}

std::pair<int, int> invertPair(std::pair<int, int> p) {
    return std::make_pair(-1 * p.first, -1 * p.second);
}

std::pair<int, int> swapPair(std::pair<int, int> p) {
    return std::make_pair(p.second, p.first);
}

bool canGoEitherSide(int i, int j, std::pair<int, int> new_dir, int** grid, int nRows, int nCols) {
    return
    !reachedBounds(i, j, new_dir, nRows, nCols) &&
    !reachedBounds(i, j, invertPair(new_dir), nRows, nCols) &&
    !alreadyVisited(i, j, new_dir, grid, nRows, nCols) &&
    !alreadyVisited(i, j, invertPair(new_dir), grid, nRows, nCols);
}

// used to visualize the path search algorithm on the console window
// repeatedly clears window and redraws matrix
void printState(int** grid, int nRows, int nCols, int delay) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    ClearScreen();
    // print paths
    for (int m = 0; m < nRows; m++) {
        for (int n = 0; n < nCols; n++) {
            std::cout << grid[m][n] << " ";
        } std::cout << std::endl;
    } std::cout << std::endl;
}

// 'n = 1' to visit, 'n = -1' to unvisit;
// if 'print' is true, will repeatedly clear console window and draw state of current path
// 'delay' is how much it will wait to do this in milliseconds
void visit(int n, int i, int j, int* visitCounter, int** grid, int nRows, int nCols, bool print=false, int delay=500) {
    
    grid[i][j] += n;
    *visitCounter += n;
    
    if (print) printState(grid, nRows, nCols, delay);
    
}

void pathSearch(std::pair<int, int> dir, int i, int j, int nRows, int nCols, int** grid, int* visitCounter, int* solveCounter, int print, int delay) {

    // recursion base: stop if "exit" is reached
    if (i == nRows-1 && j == nCols-1) {
        
        // check if we visited all squares; if so, increment solutions counter
        if (*visitCounter == nRows * nCols) {
            (*solveCounter)++;
        }
        return;
    }
    
    if ((reachedBounds(i, j, dir, nRows, nCols) ||
        alreadyVisited(i, j, dir, grid, nRows, nCols)) &&
        canGoEitherSide(i, j, swapPair(dir), grid, nRows, nCols)) {
            return;
    }
    
    if (!reachedBounds(i, j, dir, nRows, nCols) &&
            !alreadyVisited(i, j, dir, grid, nRows, nCols)) {
        
        visit(1, i + dir.first, j + dir.second, visitCounter, grid, nRows, nCols, print, delay);
        pathSearch(dir, i + dir.first, j + dir.second, nRows, nCols, grid, visitCounter, solveCounter, print, delay);
        visit(-1, i + dir.first, j + dir.second, visitCounter, grid, nRows, nCols, print, delay);
        
    }
    std::pair<int, int> swapped_dir = swapPair(dir);
    if (!reachedBounds(i, j, swapped_dir, nRows, nCols) &&
            !alreadyVisited(i, j, swapped_dir, grid, nRows, nCols)) {
    
        visit(1, i + swapped_dir.first, j + swapped_dir.second, visitCounter, grid, nRows, nCols, print, delay);
        pathSearch(swapped_dir, i + swapped_dir.first, j + swapped_dir.second, nRows, nCols, grid, visitCounter, solveCounter, print, delay);
        visit(-1, i + swapped_dir.first, j + swapped_dir.second, visitCounter, grid, nRows, nCols, print, delay);
        
    }
    std::pair<int, int> invertedSwapped_dir = invertPair(swapped_dir);
    if (!reachedBounds(i, j, invertedSwapped_dir, nRows, nCols) &&
            !alreadyVisited(i, j, invertedSwapped_dir, grid, nRows, nCols)) {
    
        visit(1, i + invertedSwapped_dir.first, j + invertedSwapped_dir.second, visitCounter, grid, nRows, nCols, print, delay);
        pathSearch(invertedSwapped_dir, i + invertedSwapped_dir.first, j + invertedSwapped_dir.second, nRows, nCols, grid, visitCounter, solveCounter, print, delay);
        visit(-1, i + invertedSwapped_dir.first, j + invertedSwapped_dir.second, visitCounter, grid, nRows, nCols, print, delay);
    }
}

// auxiliary function that receives a vector's iterators and returns a vector
// in which the elements are the sums of each possible subset of the vector
std::vector<int> powerSetVecSum(std::vector<int>::iterator vecBegin, std::vector<int>::iterator vecEnd) {
    
    int vecSize = distance(vecBegin, vecEnd);
    std::vector<int> sumSubSets;
    
    // loop through all subsets (check printPowerSetIt to understand the algorithm)
    for (int i = 0; i < (1 << vecSize); i++) {
        int subSum = 0;
        
        // sum elements that are in the subset
        for (int j = 0; j < vecSize; j++) {
            if (1 << j & i) {
                subSum += *(vecBegin + j);
            }
        }
        
        // save subset sum in a vector
        sumSubSets.push_back(subSum);
    }
    
    // return the vector with the sums of all subsets
    return sumSubSets;
}

// fuction that receives a vector's iterators and a target sum and checks if it
// can be reached with any combination of elements from the vector
bool subSum(std::vector<int>::iterator vecBegin, std::vector<int>::iterator vecEnd, int target) {
    
    int vecSize = distance(vecBegin, vecEnd);
    
    // get sums for all subsets of each half of the vector
    std::vector<int> sumA = powerSetVecSum(vecBegin, vecBegin + vecSize / 2);
    std::vector<int> sumB = powerSetVecSum(vecBegin + vecSize / 2, vecEnd);
    
    // sort vectors to optimize the search
    sort(sumA.begin(), sumA.end());
    sort(sumB.begin(), sumB.end());
    
    // search for any two elements that sum up to the target
    for (int a : sumA) {
        for (int b : sumB) {
            
            // if found, return true
            if (a + b == target) {
                return true;
            }
            
            // if the sum is larger than the target, we don't need to check for
            // the rest of the elements of sumB
            if (a + b > target) {
                break;
            }
        }
    }
    
    return false;
}

/*
backtracking queen problem test cases:

in:
1
2
3
4
5
6
7
8
9
10

out:
1
0
0
2
10
4
40
92
352
724

-----------------------
path search test cases:

in:
1 1
2 2
3 3
4 4
5 5
6 6
7 7

out:
1
0
2
0
104
0
111712

------------------------------
meet in the middle test cases:

in:
2 0
1 2

2 1
1 2

2 2
1 2

2 3
1 2

2 4
1 2

3 3
1 1 1

3 4
1 1 1

5 15
1 2 3 4 5

5 16
1 2 3 4 5


out:
1
1
1
1
0
1
0
1
0

*/