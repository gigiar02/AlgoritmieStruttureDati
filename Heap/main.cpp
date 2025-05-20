/*
  Data di creazione: 20/05/2025 orario: 15:29
  Traccia nella directory
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
#define TEMPLATE template<typename T>



class Heap
{
  vector<int> heap;
  int heapsize =-1;
  
  public:
  Heap(){}
  int getFather(int i)
  {
    return (i-1)/2;
  }
  int getLeft(int i)
  {
    return i*2 + 1;
  }
  int getRight(int i)
  {
    return i*2 + 2;
  }
  
  void print()
  {
    for(int i = 0; i < heap.size(); i++)
    {
      cout<<heap[i]<<endl;
    }
  }
  
  void insert(int key)
  {
    heap.push_back(key);
    heapsize+=1;
    int i = heapsize;
    int keyIndex = heapsize;
    int father = getFather(heapsize);
    cout<<"Inserimento "<<key<<endl;
    print();
    while(keyIndex > 0 && heap[father] > key)
    {
      cout<<"swap "<<heap[father]<<" "<<heap[keyIndex]<<endl;
      swap(heap[father],heap[keyIndex]);
      print();
      keyIndex = father;
      father = getFather(father);
    }
  }
  
  void popola()
  {
    ifstream in("in.txt");
    int key;
    
    while(in>>key)
    {
      insert(key);
      
    }
    print();
  }
  void minHeapify(int i)
  {
    int l = getLeft(i);
    int r = getRight(i);
    int min;
    
    if(heap[l] < heap[i] && l <= heapsize)
    {
      min = l;
    }else
    {
      min = i;
    }
    
    if(heap[min] > heap[r] && r <= heapsize) min = r;
    
    if(min != i)
    {
      swap(heap[min],heap[i]);
      minHeapify(min);
    }
  }
  
  void buildMinHeap()
  {
    heapsize = heap.size()-1;
    
    for(int i = (heapsize-1)/2; i >= 0; i--)
    {
      minHeapify(i);
    }
    
    cout<<"risultato build min heap"<<endl;
  }
  
  
  void heapSort()
  {
    cout<<"Eseguo heapsort"<<endl;
    buildMinHeap();
    print();
    
    for(int i = heapsize; i > 0; i--)
    {
      cout<<"swap "<<heap[0]<<" "<<heap[i]<<endl;
      swap(heap[0],heap[i]);
      print();
      heapsize--;
      minHeapify(0);
    }
    
    cout<<"Risultato"<<endl;
    print();
  }
  
  
  void decreaseKey(int i,int key)
{
  if(heap[i] < key)
  {
    cout<<"Non è possibile applicare una riduzione"<<endl;
    return;
  }
  
  heap[i] = key;
  int father = getFather(i);
  while(i > 0 && heap[father] > heap[i])
  {
    swap(heap[father],heap[i]);
    i = father;
    father = getFather(i);
  }
}
};

int main()
{
  Heap h;
  h.popola();
  h.decreaseKey(2,1);
  h.print();
}
