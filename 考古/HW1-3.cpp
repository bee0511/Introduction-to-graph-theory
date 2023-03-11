
#include <bits/stdc++.h>
using namespace std;

bool flg = true;

bool compare(int a, int b) {
  return a > b;
}

void Print(const vector<int> &v ){

    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
    
}

/*int binary_search(int L, int R, int k){
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
}*/

/*void Havel_Hakimi(vector<int> &v){
    int tmp = v[0];
    v[0] = 0;
    for (int i = 1; i < tmp + 1; i++)
    {
        v[i]--;
        if(v[i] < 0){
            cout << "No";
            flg = false;
            return;
        }
    }
    sort(v.begin(), v.end(), compare);
}*/

/*bool Havel_Hakimi(int n, vector<int> &v){
    for (int i = 0; i < n; i++)
    {
        sort(v.begin() + i, v.begin() + n, compare);
        for (int j = i + 1; j < n && v[i]; j++)
        {
            v[j]--;
            v[i]--;
            if(v[i] < 0) return false;
        }
        if(v[i]) return false;
        
    }
    return true;
}*/

bool Gallai(vector<int> &v, int k){
    sort(v.begin(), v.end(), compare);
    int sumd = 0, sumk = 0;
    for (int i = 0; i < k; i++)
    {  
        sumd += v[i];
    }
    sumk += k * (k - 1);
    for (int i = k; i < v.size(); i++)
    {
        sumk += min(k, v[i]);
    }
    if(sumd > sumk) return false;
    else return true;
    
}

/*bool Havel_Hakimi(deque<int> s){
    sort(s.begin(), s.end(), compare); // sort in non-increasing order
    //Print(s);
    if(s.front() > s.size()) return false; // the first element must be less than the size of the sequence.
    if(!s.front()) return true; // all 0
    if(s[s.size()- 1] < 0 ) return false;
    int sum = accumulate(s.begin(), s.end(), 0);
    if(sum % 2) return false;

    int front = s.front();
    s.pop_front();
    for(int i = 0 ; i < front ; i++){
        s[i]--;
    }
    return Havel_Hakimi(s);
}*/

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> v;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {   
        int buf; cin >> buf;
        v.push_back(buf);
        sum = (sum + v[i]) % 2;
    }
    if (sum % 2){
        cout << "No";
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        flg = Gallai(v, i);
        if(!flg){
            cout << "No";
            return 0;
        }
    }
    if(flg) cout << "Yes";
    
    /*while (v[0] > 0 && flg)
    {
        Havel_Hakimi(v);
        //Print(v);
    }
    if(flg) cout << "Yes";*/


    /*if(Havel_Hakimi(n, v)){
        cout << "Yes" << endl;
    }
    else cout << "No" << endl;*/

    /*deque<int> s;
    while (n--){
        int tmp; cin >> tmp;
        s.push_back(tmp);
    }
    if(Havel_Hakimi(s)){
        cout << "Yes" << endl;
    }
    else cout << "No" << endl;
    */
    
    return 0;
}