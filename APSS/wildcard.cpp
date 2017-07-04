//brute-force faster
//APSS 8-2
#include<iostream>
#include<string>
using namespace std;
//quick sort
void sort(string* words,int size){
	if(size<=1)
		return;
	else if(size==2){
		if(words[0].compare(words[1])>0){
			string temp=words[0];
			words[0]=words[1];
			words[1]=temp;
		}
	}
	else{
		int left=0,right=size-2;
		string pivot=words[size-1];
		while(left<right){
			while(pivot.compare(words[left])>0)
				left++;
			while(pivot.compare(words[right])<=0 && right>0)
				right--;
			if(left<right){
				string temp=words[left];
				words[left]=words[right];
				words[right]=temp;
				right--;
				left++;
			}
		}
		if(left==size-1)
			sort(words,size-1);
		else{
			words[size-1]=words[left];
			words[left]=pivot;
			sort(words,left);
			sort(&words[left+1],size-left-1);
		}
	}
}
bool match(string pattern,string word,int Psize,int Wsize){
	int Pptr=0,Wptr=0;
	if(Wsize==0 &&Psize!=0)
		return false;
	while(pattern[Pptr]=='?'||pattern[Pptr]==word[Wptr]){
		Pptr++;
		Wptr++;
		if(Psize<=Pptr || Wsize<=Wptr)
			break;
	}
	if(pattern[Pptr]=='*'&& Pptr<Psize-1){
		bool ret=false;
		int Pstar=Pptr+1;
		for(;pattern[Pstar]=='*';Pstar++);
		for(int Wstar=Pstar;Wstar<=Wsize;Wstar++){
			if(word[Wstar]==pattern[Pstar])
				ret = ret || match(&pattern[Pstar+1],&word[Wstar+1],Psize-Pstar-1,Wsize-Wstar-1);

		}
		return ret;
	}
	else if(pattern[Pptr]=='*')
		return true;
	else if(Pptr==Psize && Wptr==Wsize){
		return true;
	}
	else
		return false;
}
int main(){
	int Case;
	cin>>Case;
	string result[500];
	int k=0;
	for(int i=0;i<Case;i++){
		string pattern;
		int match_size=0;
		cin>>pattern;
		int num_word;
		cin>>num_word;
		string words[num_word];
		for(int j=0;j<num_word;j++)
			cin>>words[j];
		for(int j=0;j<num_word;j++){
			if(match(pattern,words[j],pattern.size(),words[j].size())){
				result[match_size+k]=words[j];
				match_size++;
			}
		}
		sort(&result[k],match_size);
		k+=match_size;
	}
	for(int i=0;i<k;i++)
		cout<<result[i]<<'\n';
	return 0;
}
