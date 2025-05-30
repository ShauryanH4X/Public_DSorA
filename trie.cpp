#include <bits/stdc++.h>
using namespace std;
struct node{
    bool isword;
    node *next[26];
    node() {
        isword=false;
        for(int i=0;i<26;++i) {
            next[i]=NULL;
        }
    }
};
struct Trie {
    node *trie;

    Trie() {
        trie=new node;
    }
    
    void insert(string word) {
        node* link=trie;
        for(int i=0,n=word.size();i<n;++i) {
            if((link->next)[word[i]-'a']==NULL) {
                (link->next)[word[i]-'a']=new node;
            }
            link=(link->next)[word[i]-'a'];
            if(i==n-1)
                link->isword=true;
        }
    }
    
    bool search(string word) {
        node* link=trie;
        if(link==NULL)
            return false;
        for(int i=0,n=word.size();i<n;++i) {
            link=(link->next)[word[i]-'a'];
            if(link==NULL)
                return false;
        }
        return link->isword;
    }
    
    bool startsWith(string word) {
        node* link=trie;
        if(link==NULL)
            return false;
        for(int i=0,n=word.size();i<n;++i) {
            link=(link->next)[word[i]-'a'];
            if(link==NULL)
                return false;
        }
        return true;
    }
};