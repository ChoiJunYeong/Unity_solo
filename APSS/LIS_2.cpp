//APSS  230p
//O(nlgn) algorithm
//dynamic programming
#include<iostream>
using namespace std;
int cache_size=0;
void binary_search(int val,int* cache,int size){
	int index=size/2;
	if(size<=1)
		cache[index]=val;
	else if(cache[index]>=val&&cache[index-1]<val)
		cache[index]=val;
	else if(cache[index]<val)
		binary_search(val,&cache[index],size-index);
	else
		binary_search(val,cache,index);
}
void lis(int* S,int* cache,int index){
	if(cache_size==0){
		cache[cache_size]=S[index];
		cache_size++;
		return;
	}
	if(S[index]>cache[cache_size-1]){
		cache[cache_size]=S[index];
		cache_size++;
	}
	//수정 to 이분검색 at here
	else{
		binary_search(S[index],cache,cache_size);
	}
}
int main(){
	int n;
	cin>>n;
	int S[n+1],cache[n+1];
	for(int i=1;i<=n;i++){
		cache[i]=-1;
		cin>>S[i];
		lis(S,cache,i);
	}
	int result;
	for(result=0;cache[result]!=-1;result++);
	cout<<result<<'\n';
	return 0;
}
