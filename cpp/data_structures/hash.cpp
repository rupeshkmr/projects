#include<iostream>

using namespace std;
void freqCount(string s){
  for(char c = 'a';c<='z';c++){
    int freq = 0;
    for(int b = 0;b<s.length();b++){

      if(c == s[b])
        freq++;
    }
    cout<<c<<"\t"<<freq<<endl;
  }
}

int frequency[26];

void hashedfreqCount(string s){
  for(int i=0;i<s.length();i++){
    s[i] -='a';
  }
  for(int i=0;i<s.length();i++){
    frequency[s[i]]++;
  }
  for(int i=0;i<=25;i++){
    cout<<i+1<<"\t"<<frequency[i]<<endl;
  }

}

int main(){
  freqCount("hello");
  hashedfreqCount("hello");

}
