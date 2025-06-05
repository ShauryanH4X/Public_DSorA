#include <bits/stdc++.h>
using namespace std;

struct SqrtDec{
    vector<vector<int>> arr;
    vector<long long> sqd;
    vector<long long> upd;
    int size,x,n;

    SqrtDec(vector<int>& a) {
        size=a.size();
        x=sqrt(a.size());
        vector<int> b;
        for(int i=0,n1=a.size();i<n1;++i) {
            b.push_back(a[i]);
            if(b.size()==x) {
                arr.push_back(b);
                b.clear();
            }
        }
        if(b.size())
            arr.push_back(b);
        n=arr.size();
        build();
    }

    void build() {
        sqd.resize(n,0);
        upd.resize(n,0);
        for(int i=0;i<n;++i) {
            for(auto z: arr[i]) {
                sqd[i]=operation(sqd[i],z);
            }
        }
    }
    long long operation(long long a,long long b) {
        return 0LL+a+b;
    }


    void Update(int l,int r,int value) {
        int start=(l-1)/x,end=(r-1)/x;
        if(start==end) {
            sqd[start]+=1LL*value*(r-l+1);
            for(int i=(l-1)%x;i<=(r-1)%x;++i) {
                arr[start][i]=operation(arr[start][i],value);
            }
        }
        else {
            sqd[start]+=1LL*value*(x-(l-1)%x);
            for(int i=(l-1)%x;i<x;++i) {
                arr[start][i]=operation(arr[start][i],value);
            }

            for(int i=start+1;i<end;++i) {
                upd[i]=operation(upd[i],1LL*value*x);
            }

            for(int i=0;i<=(r-1)%x;++i) {
                arr[end][i]=operation(arr[end][i],value);
            }
            sqd[end]=operation(sqd[end],1LL*(r-end*x)*value);
        }
    }
    
    long long Query(int l,int r) {
        int start=(l-1)/x,end=(r-1)/x;
        long long ans=0;
        if(start==end) {
            for(int i=(l-1)%x;i<=(r-1)%x;++i) {
                ans=operation(ans,arr[start][i]);
            }
            return ans;
        }
        else {
            upd[start]/x;
            for(int i=(l-1)%x;i<x;++i) {
                ans=operation(arr[start][i],operation(ans,upd[start]/x));
            }

            for(int i=start+1;i<end;++i) {
                ans=operation(sqd[i],operation(ans,upd[i]));
            }

            for(int i=0;i<=(r-1)%x;++i) {
                ans=operation(arr[end][i],operation(ans,upd[end]/(arr[end].size())));
            }
            return ans;
        }
    }
};