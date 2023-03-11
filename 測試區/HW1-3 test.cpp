#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
bool cmp(int a, int b)
{
    return a > b;
};
int binarySearch(vector<int> &nums, int lo, int hi, int tar)
{
    int a = lo - 1;
    while (lo <= hi)
    {
        int mid = (lo + hi) >> 1;
        if (nums[mid] >= tar)
        {
            a = mid;
            lo = mid + 1;
        }
        else
            hi = mid - 1;
    }
    return a;
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int q;
    cin >> q;
    int p = q;
    vector<bool> ans(q, true);
    int id = 0;
    while (q--)
    {
        int m;
        long n;
        cin >> n >> m;
        vector<int> deg(n, 0);
        for (int i = 0; i < n; i++)
        {
            cin >> deg[i];
        }

        for (int i = 0; i < m; i++)
        {
            int st, en;
            cin >> st >> en;
            deg[st - 1] -= 1;
            deg[en - 1] -= 1;
        }
        sort(deg.begin(), deg.end(), cmp);
        if (deg[n - 1] < 0)
            ans[id] = false;
        vector<long> pre(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            pre[i] = pre[i - 1] + deg[i - 1];
        }
        long sig = 0;
        for (int i = 0; i < n; i++)
        {
            long cp = (long)i * (long)(i + 1);
            sig += deg[i];
            int bord = binarySearch(deg, i + 1, n - 1, i + 1);
            cp += pre[n] - pre[bord + 1];
            cp += (long)(bord - i) * (long)(i + 1);
            if (cp < sig)
            {
                ans[id] = false;
                i = n;
            }
        }
        if (sig % 2)
            ans[id] = false;
        id += 1;
    }
    for (int i = 0; i < p; i++)
    {
        if (i != p - 1)
        {
            if (ans[i])
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }
        else
        {
            if (ans[i])
                cout << "Yes";
            else
                cout << "No";
        }
    }
}