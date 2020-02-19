#include<iostream>
#include<vector>
using namespace std;

string s[5] = {"hello","world","imback","howareyou","fine"};
string e = "Error";
//linked list to store the hash values and strings
struct node{
  int hash_val;
  string s;
  struct node *next;
};
//Array to store the heads of the lists
struct node* list[20];
//Travesing to the last of linked list
struct node* traverse(struct node* head){
  while(head->next!=NULL){
    head = head->next;
  }
  return head;
}
//Searching for hash value stored in the lists
bool search(struct node *head,string s){
  head = head->next;
  while(head!=NULL){
    if(head->s == s )
      return true;
  }
  return false;
}

//Search a string from a list of strings containing 20 strings
//Hash function
//compute ascii sum of each alphabet of the string and take remainder modulo 20
int hashmod20(string s){
  int asciisum=0;
  for(int i=0;i<s.length();i++){
    asciisum += s[i];
  }
  return asciisum%20;
}

//function to compute and store hashes of the strings
void createList(string s[]){
  cout<<"Error";
  for(int i=0;i<sizeof(s)/sizeof(s[0]);s++ ){

    int hash = hashmod20(s[i]);
    if(list[hash] != NULL){
      struct node *head = list[hash];
      bool exists = search(head, s[i]);
      if(!exists){
        struct node *last = traverse(head);
        struct node *temp;
        temp = (struct node*)malloc(sizeof(struct node));
        temp->hash_val = hash;
        temp->s = s[i];
        temp->next = NULL;
        last->next = temp;
      }
    }
    else{
      struct node *head, *temp;
      head = (struct node*)malloc(sizeof(struct node));
      temp = (struct node*)malloc(sizeof(struct node));
      head->hash_val = hash;
      temp->hash_val = hash;
      temp->s = s[i];
      temp->next = NULL;
      head->next =temp;
      list[hash] = head;
    }
  }
}



int main(){
  cout<<e;
  for(int i=0;i<20;i++)
    list[i] =NULL;
  createList(s);
  cout<<"success";
  cout<<search(list[hashmod20("fine")],"fine")<<endl;

  return 0;
}
