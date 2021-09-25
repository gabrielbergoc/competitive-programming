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
typedef pair<int, int> pii;
typedef pair<double, double> pdd;

int main() {
    ios_base::sync_with_stdio(false);   // DO NOT use C I/O streams
    cin.tie(NULL);  // FLUSH cout before using cin

    // uncomment theese next lines if I/O will use files
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    // input:
    int vec_size = 0;
    cin >> vec_size;

    vi vec;

    {
        int x = 0;
        for (int i = 0; i < vec_size; i++) {
            cin >> x;
            vec.PB(x);
        }
    }


    // beginning of solution:
    for (int i = 0; i < vec_size - 1; i++) {
        for (int j = vec_size - 1; j >= i; j--) {
            if (vec[i] > vec[j]) {
                swap(vec[i], vec[j]);
            }
        }
    }

    for (int i = 0; i < vec_size; i++) {
        cout << vec[i] << " ";
    }
}
