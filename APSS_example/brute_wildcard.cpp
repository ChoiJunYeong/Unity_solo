//brute-force algorithm
//APSS 8-3
#include<iostream>
#include<string>
using namespace std;
//quick sort
void sort(string* words,int size){
	if(size==0) return;
	else if(size==1) return;
	else if(size==2){
		if(words[0].compare(words[1])>0){
			string temp=words[0];
			words[0]=words[1];
			words[1]=temp;
		}
		return;
	}
	else{
		int left=0,right=size-2;
		string pivot=words[size-1];
		while(left<=right){
			if(words[right].compare(pivot)>=0)
				right--;
			else if(words[left].compare(pivot)<0)
				left++;
			else{
				string temp = words[left];
				words[left] = words[right];
				words[right] = temp;
			}
		}
		if(left == size-1)
			left--;
		else{
			string temp = words[left];
			words[left] = words[size-1];
			words[size-1] = temp;
		}
		sort(words,left+1);
		sort(&words[left+1],size-left-2);
		return;
	}
}
//find words match to pattern
bool match(string pattern,string word){
	if(pattern.size()==0 && word.size()==0)
		return true;
	else if(pattern.size()==0 || word.size()==0)
		return false;
	if(pattern[0]>='A' && pattern[0]<='z'){
		if(pattern[0]==word[0])
			return match(&pattern[1],&word[1]);
		else
			return false;
	}
	else if(pattern[0]=='?')
		return match(&pattern[1],&word[1]);
	else if(pattern[0]=='*')
		return match(pattern,&word[1]) || match(&pattern[1],&word[1]);
}
int main(){
	int Case;
	cin>>Case;
	string ret[500];
	int flag = 0;
	string pattern;
	int num_words;
	int k;
	for(int i=0;i<Case;i++){
		cin>>pattern;
		cin>>num_words;
		string *words = new string[num_words],*result= new string[num_words];
		k =0;
		for(int j=0;j<num_words;j++){
			cin>>words[j];
			if(match(pattern,words[j])){
				result[k]=words[j];
				k++;
			}
		}
		sort(result,k);
		for(int i=0;i<k;i++)
			ret[i+flag]=result[i];
		flag+=k;
		pattern.clear();
		delete[] words;
		delete[] result;
	}
	for(int i=0;i<flag;i++)
		cout<<ret[i]<<'\n';
	return 0;
}
