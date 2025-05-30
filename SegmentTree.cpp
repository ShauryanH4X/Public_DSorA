#include<bits/stdc++.h>
using namespace std;


struct SegNode{
    SegNode *left;
    SegNode *right;
    int l,r;
    long long value;

    SegNode() {
        left=right=NULL;
    }
    SegNode(int l,int r,long long value) {
        left=right=NULL;
        this->l=l;
        this->r=r;
        this->value=value;
    }
};


struct SegTree {
    SegNode *root;
    vector<long long> arr;


    SegTree() {
        root=new SegNode();
    }
    SegTree(vector<long long>& a) {
        root=new SegNode();
        int n=a.size();
        for(int i=0;i<n;++i) {
            arr.push_back(a[i]);
        }
        if((n&(n-1))!=0) {
            MP2(n);
        }
        build();
    }

    //Builder Function: Building segment tree from array space O(2*n) TC(6*n) 
    void build(vector<long long>& a) {

        //O(2*n)
        int n=a.size();
        for(int i=0;i<n;++i) {
            arr.push_back(a[i]);
        }
        if((n&(n-1))!=0) {
            n=MP2(n);
        }

        //O(2*n)
        vector<pair<long long,pair<int,int>>> builder(2*n);
        for(int i=0;i<n;++i) {
            builder[i+n].first=arr[i];
            builder[i+n].second.first=i+1;
            builder[i+n].second.second=i+1;
        }
        for(int i=n;--i>0;) {
            builder[i].first = builder[2*i].first + builder[2*i+1].first;
            builder[i].second.first = builder[2*i].second.first;
            builder[i].second.second = builder[2*i+1].second.second;
        }

        //O(2*n)
        RecSeg(root,builder,1);
    }

    void build() {

        //O(2*n)
        int n=arr.size();
        vector<pair<long long,pair<int,int>>> builder(2*n);
        for(int i=0;i<n;++i) {
            builder[i+n].first=arr[i];
            builder[i+n].second.first=i+1;
            builder[i+n].second.second=i+1;
        }
        for(int i=n;--i>0;) {
            builder[i].first = builder[2*i].first + builder[2*i+1].first;
            builder[i].second.first = builder[2*i].second.first;
            builder[i].second.second = builder[2*i+1].second.second;
        }

        //O(2*n)
        RecSeg(root,builder,1);
    }

    void RecSeg(SegNode *root,vector<pair<long long,pair<int,int>>>& builder,int key) {
        if(key>builder.size()) {
            return;
        }
        root->left=new SegNode();
        root->right=new SegNode();
        root->value = builder[key].first;
        root->l = builder[key].second.first;
        root->r = builder[key].second.second;
        RecSeg(root->left,builder,2*key);
        RecSeg(root->right,builder,2*key+1);
    }
    int MP2(int n) {
        int x=4;
        while(n>x) {
            x*=2;
        }
        for(int i=n;i<x;++i) {
            arr.push_back(0);
        }
        return x;
    }

    long long Query(int low,int high) {
        return Q(root,low,high);
    }
    long long Q(SegNode* root,int low,int high) {
        if(root->l>=low && root->r<=high) {
            return root->value;
        }
        if(root->r<low || root->l>high) {
            return 0;
        }
        return Q(root->left,low,high)
             + Q(root->right,low,high);
    }

    void deleter(SegNode *root) {
        if(root->left!=NULL) {
            deleter(root->left);
        }
        if(root->right!=NULL) {
            deleter(root->right);
        }
        if(root->left==NULL) 
            return;
        delete root->left;
        delete root->right;
    }
    ~SegTree() {
        deleter(root);
        delete root;
    }
};