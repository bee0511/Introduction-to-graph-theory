/*#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
bool cmp(int a, int b){
    return a > b;
}

int binary_search(int L, int R, int k, vector<int> &arr){
    int rs = L - 1;
    while (L <= R) {
        int mid = (L + R) >> 1;
        if (arr[mid] >= k) {
            rs = mid;
            L = mid + 1;
        }
        else R = mid - 1;
    }
    while(arr[rs] == arr[rs + 1] && rs < R){
        rs = rs + 1;
    }
    return rs;  
}

/*int binary_search(int L, int R, int key, vector<int> &arr){
    while(L <= R){
        int mid = (L + R) / 2;
        if(arr[mid] < key){
            L = mid + 1;
        }
        else if (arr[mid] > key){
            R = mid - 1;
        }
        else return mid;
    }
    return -1;
}*/

/*void print(const vector<int> &arr){
    for(auto &it : arr){
        cout << it << " ";
    }
    cout << endl;
}

int main(){
    int n ;
    cin >> n;
    vector<int> v;
    for(int i = 0 ; i < n ; i++){
        int tmp; cin >> tmp;
        v.push_back(tmp);
    }

    sort(v.begin(), v.end(), cmp);

    print(v);
    
    int key;
    cout << "input key: ";
    cin >> key;
    int ans = binary_search(0, v.size() - 1, key, v);
    cout << "ans: " << ans;
    return 0;
}*/


//*****************
// LAM PHAN VIET **
// UVA 10720 - Graph Construction
// Time limit: 3.000
//********************************
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#define FileIn(file) freopen(file".inp", "r", stdin)
#define FileOut(file) freopen(file".out", "w", stdout)
#define FOR(i, a, b) for (int i=a; i<=b; i++)
#define REP(i, n) for (int i=0; i<n; i++)
#define Fill(ar, val) memset(ar, val, sizeof(ar))
#define PI 3.1415926535897932385
#define uint64 unsigned long long
#define int64 long long
#define all(ar) ar.begin(), ar.end()
#define pb push_back
#define bit(n) (1<<(n))
#define Last(i) ( i & -i )
#define INF 500000000
#define maxN 10001
using namespace std;

int n, deg[maxN];
int sum, left_sum[maxN];
bool valid;

bool cmp(int a, int b) { return a > b; }

int search(int L, int R, int k) {
    int rs = L - 1;
    while (L <= R) {
        int mid = (L + R) >> 1;
        if (deg[mid] >= k) {
            rs = mid;
            L = mid + 1;
        }
        else R = mid - 1;
    }
    return rs;
}

bool solve() {
    if (!valid) return false;
    if (sum & 1) return false;
    sort(deg + 1, deg + n + 1, cmp);
    cout << "deg: ";
    FOR (i, 1, n){
        cout << deg[i] << " ";
    }
    cout << endl;
    left_sum[n + 1] = 0;
    for (int i = n; i >= 1; i--)
        left_sum[i] = left_sum[i + 1] + deg[i];
    for(int i = 1 ; i <= n ; i++){
        cout << left_sum[i] << " ";
    }
    cout << endl;
    int left = 0, right;
    FOR (k, 1, n) {
        int p = search(k + 1, n, k);
        cout << "p: " << p << endl;
        left += deg[k];
        right = k * (p - 1) + left_sum[p + 1];
        if (left > right) return false;
    }
    return true;
}

main() {
 //   FileIn("test"); FileOut("test");
    while (scanf("%d", &n) && n) {
        valid = true;
        sum = 0;
        FOR (i, 1, n) {
            scanf("%d", &deg[i]);
            if (!valid) continue;
            if (deg[i] >= n || deg[i] < 0) valid = false;
            sum += deg[i];
        }
        if (solve()) puts("Possible");
        else puts("Not possible");
    }
}