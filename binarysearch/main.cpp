#include <bits/stdc++.h>

using namespace std;

template <typename T>
typename vector<T>::iterator binarySearch(
        typename vector<T>::iterator begin,
        typename vector<T>::iterator end,
        T target,
        bool sortIt=false
        );

int main() {

    vector<int> vec;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        vec.push_back(x);
    }

    int searchFor;
    cin >> searchFor;
    bool sortIt;
    cin >> sortIt;
    auto found = binarySearch(vec.begin(), vec.end(), searchFor, sortIt);
    if (found != vec.end() && found != vec.begin() - 1) {
        cout << *found;
    } else {
        cout << "not found";
    } cout << endl;
}

// function that takes begin and end iterators, a target to search for, and
// sorts original vector if sortIt=true (default is false) and returns an
// iterator to element, if found, or end/begin-1 iterator if not found
template <typename T>
typename vector<T>::iterator binarySearch(typename vector<T>::iterator begin, typename vector<T>::iterator end, T target, bool sortIt) {

    if (sortIt) {
        sort(begin, end);
    }

    // finds middle of vector
    auto mid = begin + (end - begin) / 2;

    // loop until found (*mid == target) or mid is out of bounds
    while (mid >= begin && mid < end && *mid != target) {

        if (*mid > target) {
            end = mid;
        } else {
            begin = mid + 1;
        }
        mid = begin + (end - begin) / 2;    // keeps halving the vector each step
    }

    return mid;
}
