#include<bits/stdc++.h>
using namespace std;

class minHeap{
    vector<int>heap;

    void heapifyUp(int idx){
        while(idx>0){
            int p=(idx-1)/2;
            if(heap[idx]<heap[p]){
                swap(heap[idx],heap[p]);
                idx=p;
            }else{
                break;
            }
        }
    }
    void heapifyDown(int idx){
        int s=heap.size();
        while(true){
            int l=2*idx+1;
            int r=2*idx+2;
            int small=idx;
            if(l<s && heap[l]<heap[small]){
                small=l;
            }
            if(r<s && heap[r]<heap[small]){
                small=r;
            }
            if(small!=idx){
                swap(heap[idx],heap[small]);
                idx=small;
            }else{
                break;
            }
        }
    }
    public:
    
    void insert(int val){
        heap.push_back(val);
        heapifyUp(heap.size()-1);
    }

    void pop(){
        if(heap.empty()) return;
        heap[0]=heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    int top(){
        if(!heap.empty()) return heap[0];
        return -1;
    }

    void display(){
        for(int i:heap){
            cout<<i<<" ";
        }
        cout<<endl;
    }
};


int main(){
    minHeap h;
    h.insert(10);
    h.insert(20);
    h.insert(5);
    h.insert(7);
    h.insert(3);
    h.insert(15);
    h.display();
    h.pop();
    h.display();
}