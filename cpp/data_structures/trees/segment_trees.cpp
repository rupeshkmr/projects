#include<iostream>
#include<vector>
#include<math.h>
using namespace std;
//structure for storing the range values in the mappings table
struct range{
  int l,r;
};
string e = "error\n";
int n;
struct range t;

//The binary tree will be stored in an array just like heaps
//Each entry in the node represents the sum of values
vector <int> tree;
//Array to store the corresponding index values at a node
vector <range> mappings;
void printTree(){
  cout<<"The requested tree is: "<<endl;
  //finish up printing in tree format
  // for(int i=0;i<log(tree.size());i_++){
  //
  //   cout<<endl;
  // }
  for(int i=0;i<tree.size();i++){
    cout<<"|"<<tree[i]<<"|";

  }
  cout<<endl;
  for(int i=0;i<tree.size();i++){
    cout<<"|("<<mappings[i].l<<","<<mappings[i].r<<")|";

  }
  cout<<endl;
}




//Two approaches for building the segment tree
//1. Top Down
//Take the input array start dividing until we get a single element
void build(int node,int start,int end,int arr[]){
  if(start == end ){
    struct range temp;
    temp.l = start;
    temp.r = start;
    if(node>=tree.size()){
      tree.push_back(arr[start]);
      mappings.push_back(temp);
    }
    else{
    tree[node] = arr[start];
    mappings[node]=temp;
    }  // cout<<"Start:"<<start<<" End : "<<end<<endl;
      cout<<"( "<<start<<" , "<<end<<" )"<<endl;
  }
  else{
    int mid= (start+end)/2;
    int sum  = 0;

    struct range temp;

    temp.l = start;
    temp.r = end;

    mappings[node] = temp;
    // cout<<"Left child"<<node*2+1<<endl;
    // cout<<"Right child"<<node*2+2<<endl;
    //cout<<"Start:"<<start<<" Mid = :"<<mid<<" End : "<<end<<endl;
    cout<<"("<<start<<" , "<<mid<<" , "<<end<<" ) "<<endl;

    //build the left subttree
    build(node*2+1,start,mid,arr);
    //build the right subttree
    build(node*2+2,mid+1,end,arr);
    tree[node] = tree[node*2+1] + tree[node*2+2];
  }
}




//2. Bottom Up




//Updating the value at the tree
//Update the value in the tree upto the parent reaches root
void update(int node,int start, int end,int index, int value){
  if(start==end){
    tree[node] += value;
  }
  else{
    int mid = (start+end)/2;
    if(index>=start && index<=mid ){
      //left subtree
      update(node*2+1,start,mid,index,value);
      //update the parent
      tree[node] = tree[node*2+1]+tree[node*2+2];
    }
    else if(index>mid && index<=end){
        //right subtree
        update(node*2+2,mid+1,end,index,value);
        tree[node] = tree[node*2+1] + tree[node*2+2];
      }
  }

}

//Querying information from the tree
//taking input a range(l,r) and returning the union of elements between l and r
int query(int node,int start,int end, int l, int r){
  if(r<start || l>end){
    //no overlap with the given range
    return 0;
  }
  if(start>=l && end<=r){
    //range represented by a node is completely inside(l,r)
    return tree[node];
  }
  //Partial overlap
  int mid = (start+end)/2;
  int q1 = query(node*2+1,start,mid,l,r);
  int q2 = query(node*2+2,mid+1,end,l,r);
  return q1+q2;
}

int main(){
  vector <int> test;
  n = 6;
  for(int i=0;i<2*n;i++)
{  t.l = -1;
  t.r = -1;
  mappings.push_back(t);
  tree.push_back(0);
}
  int arr[] = {1,3,5,7,9,11};
  for(int i=0;i<sizeof(arr)/sizeof(arr[0]);i++){
    test.push_back(arr[i]);
  }

  build(0,0,sizeof(arr)/sizeof(arr[0])-1,arr);
  printTree();
  update(0,0,n-1,4,10);
  printTree();
  cout<<"Query (3,5)"<<endl;
  cout<<query(0,0,5,3,5);
  return 0;
}
