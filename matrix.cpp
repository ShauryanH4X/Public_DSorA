#include<bits/stdc++.h>

using namespace std;

struct matrix {
    vector<vector<int>>a;
    int rsize,csize;

    matrix(int n) {
        a.resize(n);
        rsize=csize=n;
        for(int i=0;i<n;++i) {
            a[i].resize(n,0);
        }
    }
    matrix(int r,int c) {
        a.resize(r);
        rsize=r;
        csize=c;
        for(int i=0;i<r;++i) {
            a[i].resize(c,0);
        }
    }

    void put(int r,int c,int x) {
        a[r][c]=x;
    }

    int get(int r,int c) {
        return a[r][c];
    }

    matrix make_identity(int n) {
        matrix I(n);
        for(int i=0;i<n;++i)
            I.put(i,i,1);
        return I;
    }

    void transpose() {
        vector<vector<int>> a2(csize,vector<int>(rsize));
        for(int i=0;i<rsize;++i) {
            for(int j=0;j<csize;++j) {
                a2[j][i]=a[i][j];
            }
        }
        a.resize(csize);
        for(int i=0;i<csize;++i) {
            a[i].resize(rsize);
        }
        for(int i=0;i<csize;++i) {
            for(int j=0;j<rsize;++i) {
                a[i][j]=a2[i][j];
            }
        }
        rsize+=csize;
        csize=rsize-csize;
        rsize=rsize-csize;
    }

    matrix multiply(matrix& m2) {
        if(csize==m2.rsize) {
            matrix m3(rsize,m2.csize);
            for(int i=0;i<rsize;++i) {
                for(int j=0;j<m2.csize;++j) {
                    for(int k=0;k<csize;++k) {
                        m3.put(i,j,m3.get(i,j)+get(i,k)*(m2.get(j,k)));
                    }
                }
            }
            return m3;
        }
        else if(m2.csize==rsize)
            return (m2.multiply(*this));
    }
    vector<vector<int>> multiply(vector<vector<int>> &arr) {
        if(arr.size()==csize) {
            vector<vector<int>> m3(rsize,vector<int>(arr[0].size(),0));
            for(int i=0;i<rsize;++i) {
                for(int j=0;j<arr[0].size();++j) {
                    for(int k=0;k<csize;++k) {
                        m3[i][j]+=get(i,k)*(arr[j][k]);
                    }
                }
            }
            return m3;
        }
    }

    matrix power(int n) {
        if(rsize!=csize)
            exit(1);
        if(n==0) {
            return make_identity(rsize);
        }
        matrix ans=power(n/2);
        if(n%2)
            return (this->multiply(ans)).multiply(ans);
        else
            return ans.multiply(ans);
    }

    void show() {
        for(int i=0;i<rsize;++i) {
            for(int j=0;j<csize;++j) {
                cout<<a[i][j]<<' ';
            }
            cout<<'\n';
        }
    }

};