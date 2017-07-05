//APSS 8-5
//dynamic programming
#include<iostream>
using namespace std;
int ptr;
void binary_search(long long val, long long* cache, int size){
	int mid = size/2;
	if(size<=1){
		cache[0]=val;
	}
	else if(cache[mid]>=val && cache[mid-1]<val){
		cache[mid]=val;
	}
	else if(cache[mid]<val){
		binary_search(val,&cache[mid],size-mid);
	}
	else if(cache[mid]>val){
		binary_search(val,cache,mid);
	}
}
void jlis(long long val,long long* cache){
	if(ptr==0){
		cache[0]=val;
		ptr++;
		return;
	}
	if(cache[ptr-1]<=val){
		cache[ptr]=val;
		ptr++;
		return;
	}
	else
		binary_search(val,cache,ptr);
}
void init_cache(long long* cache,int size){
	if(size==0){
		ptr=0;
	   	return;
	}
	cache[size-1]=-1;
	init_cache(cache,size-1);
}
int main(){
	int Case;
	cin>>Case;
	int result[Case];
	for(int i=0;i<Case;i++){
		int size1,size2;
		cin>>size1>>size2;
		long long set1[size1],set2[size2],cache[size1 + size2 + 1];
		long long uniset[size1 + size2];
		int j;
		//set cache -1
		init_cache(cache, size1+size2+1);
		//input set1 && first half of uniset
		for(j=0;j<size1;j++){
			cin>>set1[j];
			uniset[j]=set1[j];
			jlis(uniset[j],cache);
		}
		//input set2 && second half of uniset
		for(int k=0;k<size2;k++){
			cin>>set2[k];
			uniset[j+k]=set2[k];
			jlis(uniset[j+k],cache);
		}
		for(j=0;cache[j]!=-1;j++);
		result[i]=j;
		//set cache -1
		init_cache(cache, size1+size2+1);
		//input first half of uniset
		for(j=0;j<size2;j++){
			uniset[j]=set2[j];
			jlis(uniset[j],cache);
		}
		//input second half of uniset
		for(int k=0;k<size1;k++){
			uniset[j+k]=set1[k];
			jlis(uniset[j+k],cache);
		}
		for(j=0;cache[j]!=-1;j++);
		result[i]=max(result[i],j);
	}
	for(int i=0;i<Case;i++)
		cout<<result[i]<<'\n';
	return 0;
}
