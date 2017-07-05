#include<iostream>
using namespace std;
int n;
int lis(int start,int* cache,int* S,int n){
	int ret = cache[start];
	if(ret!=-1)
		return ret;
	ret = 1;
	for(int next = start+1;next<n;next++){
		if(S[start]<S[next])
		ret = max(ret,lis(next,cache,S,n)+1);
	}
	cache[start]=ret;
	return ret;
}
int main(){
	cin>>n;
	int cache[n],S[n];
	for(int i=0;i<n;i++){
		cin>>S[i];
		cache[i]=-1;
	}
	int result=-1;
	for(int i=0;i<n;i++)
		result=max(result,lis(i,cache,S,n));
	cout<<result;
}
