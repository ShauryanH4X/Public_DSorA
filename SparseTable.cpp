#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
//using namespace std;

/*
    Sparse Table for GCD
*/

template<typename T>
class Sparse{

    std::vector<std::vector<T>> a;
    int size,logsize;

    public:
    Sparse(int n) {
        logsize=std::log(n)+1;
        size=n;
        a.resize(logsize);
        for(int i=0;i<logsize;++i) {
            (a[i]).resize(n);
            for(int j=0;j<n;++j) {
                (a[i])[j]=1;                                                    //To Change current GCD
            }
        }
    }
    Sparse(T* arr,int n) {
        logsize=std::log(n)+1;
        size=n;
        a.resize(logsize);
        for(int i=0;i<logsize;++i) {
            (a[i]).resize(n);
            for(int j=0;j<n;++j) {
                (a[i])[j]=1;                                                    //To Change current GCD
            }
        }
        build(arr,n); 
    }
    Sparse(std::vector<T> &arr) {
        int n=arr.size();
        logsize=std::log(n)+1;
        size=n;
        a.resize(logsize);
        for(int i=0;i<logsize;++i) {
            (a[i]).resize(n);
            for(int j=0;j<n;++j) {
                (a[i])[j]=1;                                                    //To Change current GCD
            }
        }
        build(arr,n);
    }
    void build(T *arr,int n) {
        for(int i=0;i<n;++i) {
            a[0][i]=arr[i];
        }
        for(int i=1;i<logsize;++i) {
            for(int j=0;j+(1<<(i-1))<n;++j) {
                a[i][j]=std::__gcd(a[i-1][j],a[i-1][j+(1<<(i-1))]);
            }
        }
    }
    void build(std::vector<T> &arr,int n) {
        for(int i=0;i<n;++i) {
            a[0][i]=arr[i];
        }
        for(int i=1;i<logsize;++i) {
            for(int j=0;j+(1<<(i-1))<n;++j) {
                a[i][j]=std::__gcd(a[i-1][j],a[i-1][j+(1<<(i-1))]);             //To Change current GCD
            }
        }
    }
    T retrieve(int l,int r) {       //should give 0-indexed range
        int k=std::log(r-l+1);
        return std::__gcd(a[k][l],a[k][r-(1<<k)+1]);                            //To Change current GCD
    }
    T retrieve1D(int l,int r) {     //should give 1-indexed range
        --l;--r;
        return retrieve(l,r);
    }
    void clear() {
        for(int i=0;i<logsize;++i) {
            a[i].clear();
        }
        a.clear();
    }
    ~Sparse() {
        for(int i=0;i<logsize;++i) {
            a[i].clear();
        }
        a.clear();
    }
};