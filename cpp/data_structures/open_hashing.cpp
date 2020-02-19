#include<iostream>
#include<vector>
using namespace std;

vector <string> s;
string e = "Error";
//linked list to store the hash values and strings
struct node{
  int hash_val;
  string s;
  struct node *next;
};
//Array to store the heads of the lists
struct node* list[20];

void initTable(){
  for(int i=0;i<=19;i++){
    list[i] = (struct node*)malloc(sizeof(struct node));
    list[i]->hash_val = i;
    list[i]->next = NULL;
  }
}
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
    head = head->next;
  }
  return false;
}

//Search a string from a list of strings containing 20 strings
//Hash function
//compute ascii sum of each alphabet of the string and take remainder modulo 20
int hashmod20(string s1){
  int asciisum=0;
  for(int i=0;i<s1.length();i++){
    asciisum += s1[i];
  }
  return asciisum%20;
}

//function to compute and store hashes of the strings
void createTable(vector <string> s1){
  for(int i=0;i<s1.size();i++){
    	int hash = hashmod20(s1[i]);
	//string is already in the table
     	if(!search(list[hash],s1[i])){
		struct node* temp = traverse(list[hash]);
		struct node* temp1;
		temp1 = (struct node*)malloc(sizeof(struct node));
		temp1->s = s1[i];
		temp1->hash_val = hash;
		temp1->next = NULL;
		temp->next = temp1;

	}
	cout<<"string "<<s[i]<<" inserted successfully"<<endl;
  }

}

void printList(struct node* head){
	int f= 0;
	while(head!=NULL){
		if(f==0){
			cout<<head->hash_val<<"->\t";
			f = 1;
		}
		else
			cout<<head->s<<"->\t";
		head = head->next;
	}
	cout<<endl;
}
void printTable(){
	for(int i=0;i<20;i++){
		printList(list[i]);
	}
}

int main(){
  string inp[] = {"hello","world","imback","howareyou","fine"};
  for(int i=0;i<=4;i++)
	  s.push_back(inp[i]);
  initTable();
	
  createTable(s);
  printTable();
  cout<<"success";
  cout<<search(list[hashmod20("fine")],"fine")<<endl;

  return 0;}	
