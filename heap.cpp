#include<iostream>
#include<vector>
using namespace std;

class minHeap{
    vector<int> heap;

    void heapUP(int index){
        while(index>0){
            int parent = (index-1)/2;
            if(heap[index]<heap[parent]){
                swap(heap[index],heap[parent]);
            }
            else{
                return;
            }
        }
    }

    void heapdown(int index){
        int size = heap.size();

        while(index*2+1 < size){   //till cureent node has atleast 1 child
            int left = index * 2 + 1;
            int right = index * 2 +2;
            int smallest = left;

            if(right<size && heap[right]<heap[left]){  //right side smaller than left
                smallest = right;
            }
            if(heap[smallest] < heap[index]){
                swap(heap[index],heap[smallest]);
                index = smallest;
            }
            else{
                break;
            }
        }
    }

    public:
    void insert(int key){
        heap.push_back(key);
        heapUP(heap.size()-1);
    }

    int deletemin(){
        if(heap.empty()){
            return -1;
        }
        int min=heap[0];
        heap[0]=heap.back();
        heap.pop_back();
        heapdown(0);
        return min;
    }

    void display(){
        for(int i=0 ;i<heap.size() ;i++){
            cout<<heap[i]<<" ";
        }
    }
};

int main(){
    minHeap h;
    h.insert(10);
    h.insert(5);
    h.insert(15);
    h.insert(2);

    cout<<"HEAP: ";
    h.display();

    cout<<"after deleting:"<<h.deletemin()<<endl;
    h.display();
}
