#include <iostream>
#include <climits>
using namespace std;
 
int min(int a, int b){
    return (a < b) ? a : b;
}

int findOverlappingPair(string str1, string str2, string &str){
    bool flag = true;
    int max = INT_MIN;
    int len1 = str1.length();
    int len2 = str2.length();
    
    for(int i=0; i<=min(len1, len2); i++){
        if(len1 > len2){
            if(str1.compare(i, i+len2, str2, 0, len2) == 0){
                str = str1;
                flag = false;
                max = -1;
            }
        }
        else{
            if(str2.compare(i, i+len1, str1, 0, len1) == 0){
                str = str2;
                flag = false;
                max = -1;
            }
        }
    }
    
    if(flag){
        for (int i=1; i<=min(len1, len2); i++){
            if (str1.compare(len1-i, i, str2, 0, i) == 0){
                if (max < i){
                    max = i;
                    str = str1 + str2.substr(i);
                }
            }
        }

        for (int i=1; i<=min(len1, len2); i++){
            if (str1.compare(0, i, str2, len2-i, i) == 0){
                if (max < i){
                    max = i;
                    str = str2 + str1.substr(i);
                }
            }
        }
    }
    return max;
}
 
string findShortestSuperstring(string arr[], int len){
    while(len != 1){
        int max = INT_MIN;
        int l=0, r=0;
        string resStr;
        
        for(int i=0; i<len; i++){
            cout << arr[i] << "  ";
        } cout << "\n";
       
        for (int i=0; i<len; i++){
            for (int j=i+1; j <len; j++){
                string str;
                int res = findOverlappingPair(arr[i], arr[j], str);
 
                if (max < res){
                    max = res;
                    resStr.assign(str);
                    l = i;
                    r = j;
                }
            }
        }
 
        len--;
        cout << "len=" << len << endl;
        if (max == INT_MIN){
            string temp1 = "zzzzzz"; // smallest order
            string temp2 = "zzzzzz"; // second smallest order
            int t1=-1, t2=-1;
            for(int i=0; i<len; i++){
                if(arr[i] < temp1) {
                    temp1 = arr[i];
                    t1 = i;
                }
            }
            arr[t1] = arr[len];
            arr[len] = temp1;
            cout << "temp1=" << temp1 << endl;
            
            for(int i=0; i<len-1; i++){
                if(arr[i] < temp2){
                    temp2 = arr[i];
                    t2 = i;
                }
            }
            
            if(t2!=-1){
                arr[t2] = arr[len-1];
                arr[len-1] = temp2;
                cout << "temp2=" << temp2 << endl;
                arr[len] += arr[len-1];
                arr[len-1] = arr[len];
                cout << "arr[len-1]=" << arr[len-1] << endl;
            }
            else if(arr[0] < arr[len]) arr[0] += arr[len];
            else{
                arr[len] += arr[0];
                arr[0] = arr[len];
            }
        }
            
        else{
            arr[l] = resStr;
            arr[r] = arr[len];
        }
    }
    return arr[0];
}

int main(){
    int len;
    cin >> len;
    string arr[len];
    for(int i=0; i<len; i++){
        cin >> arr[i];
    }
 
    cout << findShortestSuperstring(arr, len) << "\n";
    string s1 = "ninomae";
    string s2 = "inanislove";
 
    return 0;
}
