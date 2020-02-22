#include<iostream>
#include<vector>
using namespace std;
//open addressing using linear probing
string inp[] = {"hello","world","imback","howareyou","fine","hello"};
vector <string> s;
string table[20];
int m= 20;
int probeLimit = 0;// to limit the maximum number of probes while probing
//Hash function
//compute ascii sum of each alphabet of the string and take remainder modulo 20
int hashmod20(string s1){
  int asciisum=0;
  for(int i=0;i<s1.length();i++){
    asciisum += s1[i];
  }
  return asciisum%20;
}

//Linear probe function
// i = probe interval
int quadraticProbe(int hash_val,int i,string s){
  if(table[hash_val] == "" || table[hash_val] == s){
    cout<<"Probe successful"<<"\t Slot no "<< hash_val<<"avilable"<<endl;
    return hash_val;
  }
  else{//again probing with probe interval i
    hash_val = (hash_val+i*i)%m;
    probeLimit++;
    if(probeLimit == 21)
      return -1;
    //finish up
    return quadraticProbe(hash_val,i+1,s);
  }
}

//Searching for hash value stored in the lists
void search(string s){
  int slot = quadraticProbe(hashmod20(s),1,s);
  if(slot == -1 || s !=table[slot])
    cout<<"string "<<s<<" not found"<<endl;
  else
    cout<<"string "<<s<<" found at slot "<<slot<<endl;

}

void printTable(){
  for(int i=0;i<20;i++){
    cout<<"Slot #: "<<i<<"Key = "<<table[i]<<endl;
  }
}

//Create the hash table
void hash_(vector <string> s){
  for(int i=0;i<s.size();i++){
    int hash_val = hashmod20(s[i]);
    int slot = quadraticProbe(hash_val,1,s[i]);
    table[slot] = s[i];
    cout<<s[i]<<" Hashed successfully"<<endl;
  }



}



int main(){


  for(int i=0;i<20;i++){
    table[i] = "";
  }
  for(int i=0;i<=5;i++)
	  s.push_back(inp[i]);
  hash_(s);
  printTable();
  search("im");
  search("fine");


  return 0;
}
