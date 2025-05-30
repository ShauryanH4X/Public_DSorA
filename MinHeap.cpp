#include<bits/stdc++.h>
using namespace std;

template<typename T>
class MinHeap {
    vector<T> heap;

    void heapifyUp(int index) {
        int parent = (index - 1) / 2;
        while (index > 0 && heap[index] < heap[parent]) {
            swap(heap[index], heap[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    void heapifyDown(int index) {
        int left=2*index+1;
        int right=2*index+2;
        int smallest=index;
        if (left<heap.size() && heap[left]<heap[smallest])
            smallest=left;
        if (right<heap.size() && heap[right]<heap[smallest])
            smallest=right;

        if (smallest!=index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }
public:
    void insert(T val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }

    T top() {
        if (heap.empty()) return -1;
        return heap[0];
    }
    void pop() {
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }
    void Heapify(vector<T>& arr) {
        heap.clear();
        for(T i:arr) {
            heap.push_back(i);
        }
        int n=heap.size();
        for(int i=n/2-1;i>=0;i--) {
            heapifyDown(i);
        }
    }
    vector<T>& heapSort() {
        vector<T> sortedHeap;
        vector<T> heap2;
        for(T i:heap) {
            heap2.push_back(i);
        }
        while (!heap.empty()) {
            sortedHeap.push_back(top());
            pop();
        }
        Heapify(heap2);
        return sortedHeap;
    }
    int size() {
        return heap.size();
    }
    bool empty() {
        return heap.size()==0;
    }
    void clear() {
        heap.clear();
    }

    
    void display() {
        for (T num : heap) 
            cout<<num<<" ";
        cout<<endl;
    }
};