#include<iostream>
#include<vector>
using namespace std;

vector <int> heap;

//The code throughout uses one extra argument: Mode 0 for Min heap and 1 for Max Heap

void heapify(int i,vector <int> &arr,int mode){
  int lchild = 2 * i+1,rchild = lchild +1,index = i,size = arr.size();
  if(lchild <size)
    if( arr.at(lchild) < arr.at(index) && mode == 0)
      index = lchild;
    else
      if(arr.at(lchild) > arr.at(index) && mode == 1)
        index = lchild;
  if(rchild < size)
    if( arr.at(rchild) < arr.at(index) && mode == 0)
      index = rchild;
    else
      if(arr.at(rchild) > arr.at(index) && mode ==1)
        index = rchild;
  if(index != i){
    swap(arr.at(index),arr.at(i));
    heapify(index,arr,mode);
  }
  //cout<<"Smallest element = "<<arr[i]<<"\n\n";
}

void build_heap(vector <int> &arr,int mode){
  for(int i=arr.size()/2;i>=0;i--){
    heapify(i,arr,mode);
  }
  cout<<"Heap creation successful"<<endl;
}
void heap_insert_check(int i,vector <int>&arr, int mode){
    switch(mode){
      case 0:{
        if(arr.at(i)<arr.at(i/2)){
          swap(arr.at(i),arr.at(i/2));
          heap_insert_check(i/2,arr,mode);
        }
        break;
      }
      case 1:{
        if(arr.at(i)>arr.at(i/2)){
          swap(arr.at(i),arr.at(i/2));
          heap_insert_check(i/2,arr,mode);
        }
        break;}}
}
void insert_heap(int value,vector <int> &arr,int mode){
  arr.push_back(value);
  heap_insert_check(arr.size()-1,arr,mode);
  cout<<"Insertion Successful"<<endl;
}

int extract(vector <int> &arr,int mode){
  int ret_val = arr.at(0);
  swap(arr.at(0),arr.at(arr.size()-1));
    arr.erase(arr.begin()+arr.size()-1);
  heapify(0,arr,mode);
  return ret_val;
}
int main(){

  for(int i=10;i>=1;i--)
    heap.push_back(i);
  for(int i=0;i<=10;i++)
    cout<<heap[i]<<"\t";
  cout<<endl;
  build_heap(heap,1);
  for(int i=0;i<=10;i++)
    cout<<heap[i]<<"\t";
  insert_heap(22,heap,1);
  for(int i=0;i<=10;i++)
    cout<<heap[i]<<"\t";
  cout<<endl;
  cout<<extract(heap,1)<<endl;
  for(int i=0;i<=10;i++)
    cout<<heap[i]<<"\t";
  return 0;

}
