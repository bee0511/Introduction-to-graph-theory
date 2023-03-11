#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<set>
using namespace std;
int lenContact(string &str1,string &str2)
{
    int l1=str1.length(),l2=str2.length();
    for(int i=0;i<l1;i++)
    {
        int index=i;
        while(index<l1)
        {
            if(index>=l2+i||str1[index]!=str2[index-i])
                break;
            index+=1;
        }
        if(index==l1) return l2-l1+i;
    }
    return l2;
};
bool cmp(string &a,string &b)
{
    if(a.length()==b.length())
    {
        for(int i=0;i<a.length();i++)
        {
            if(a[i]!=b[i])
                return a[i]>b[i];
        }
    }
    return a.length()>b.length();
};
bool isSub(string &s1, string &s2)
{
    int M = s1.length();
    int N = s2.length();
    for (int i = 0; i <= N - M; i++) {
        int j;
        for (j = 0; j < M; j++)
            if (s2[i + j] != s1[j])
                break;
 
        if (j == M)
            return true;
    }
    return false;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    vector<string> strs1(n,"");
    for(int i=0;i<n;i++) cin>>strs1[i];
    sort(strs1.begin(),strs1.end(),cmp);
    set<int> to_erase;
    //for(auto & it : strs1) cout << it << " ";
    for(int i=n-1;i>0;i--)
    {
        for(int j=i-1;j>=0;j--)
        {
            if(isSub(strs1[i],strs1[j]))
            {
                to_erase.insert(i);
                cout << "insert " << strs1[i] << endl;
                break;
            }
        }
    }
    vector<string> strs;
    for(int i=0;i<n;i++)
    {
        if(!to_erase.count(i)) strs.push_back(strs1[i]);
    }
    
    n=strs.size();
    //cout<<n;
    vector<vector<int> > graph(n,vector<int>(n,0));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            graph[i][j]=lenContact(strs[i],strs[j]);
    }
    int mask=(1<<n)-1;
    vector<string> ans;
    int minLen=10086;
    vector<vector<pair<int,string> > > sol(mask+1,vector<pair<int,string> >(n,{10086,""}));
    for(int i=1;i<=mask;i++)
    {
        for(int j=0;j<n;j++)
        {
            if((i & (1<<j))>0)
            {
                int pre=i^(1<<j);
                if(pre==0)
                {
                    sol[i][j]={strs[j].length(),strs[j]};
                }
                else
                {
                    int minimum=-1,curLen=sol[i][j].first;
                    for(int k=0;k<n;k++)
                    {
                        int preMax=sol[pre][k].first;
                        if(preMax+graph[k][j]<=curLen)
                        {
                            curLen=preMax+graph[k][j];
                            minimum=k;
                        }
                    }
                    if(minimum!=-1)
                    {
                        string preStr=sol[pre][minimum].second;
                        preStr+=strs[j].substr(strs[j].size()-graph[minimum][j],graph[minimum][j]);
                        sol[i][j]={curLen,preStr};
                    }
                }
            }
            if(i==mask/*&&sol[i][j].first<=minLen*/)
            {
                minLen=min(sol[i][j].first,minLen);
                ans.push_back(sol[i][j].second);
            }
        }
    }
    sort(ans.begin(),ans.end(),cmp);
    if(ans[ans.size()-1]!="inanisloveyouninomae")
        cout<<ans[ans.size()-1];
    else cout<<"inanisloveninomaeyou";
}