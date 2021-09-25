#include <bits/stdc++.h>

#define F first
#define S second
#define PB push_back
#define MP make_pair
#define B begin
#define E end

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<double> vd;
typedef pair<int,int> pii;
typedef pair<double,double>pdd;

int main() {
    ios_base::sync_with_stdio(false);   // DO NOT use C I/O streams
    cin.tie(NULL);  // FLUSH cout before using cin

    // uncomment theese next lines if I/O will use files
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    
    vi nums;
    int nums_size{0};
    cin >> nums_size;

    {
        int x{0};
        for (int i = 0; i < nums_size; i++) {
            cin >> x;
            nums.PB(x);
        }
    }   // destroy variable 'x' after use

    // O(n²) solution:
    /*
    int best{0};
    for (int i{0}; i < nums_size; i++) {
        int sum{0};
        for (int j = i; j < nums_size; j++) {
            sum += nums[j];
            best = max(sum, best);
        }
    }
    */

    // O(n) solution (Kadane's Algorithm):
    int local_max{0};
    int global_max{INT_MIN};
    for (int i{0}; i < nums_size; i++) {
        local_max = max(nums[i], local_max + nums[i]);
        global_max = max(global_max, local_max);
    }

    cout << global_max;

    // see vector
    /*
    cout << best << "\n";
    for (int i{0}; i < size; i++) {
        cout << nums[i] << " ";
    } */
    
}

// -2 1 -3 4 -1 2 1 -5 4 -> 9 elements, max_sum = 6 ([4, -1, 2, 1])
// -1 2 4 -3 5 2 -5 2 -> 8 elements, max_sum = 10 ([2, 4, -3, 5, 2])
