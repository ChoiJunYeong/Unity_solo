//APSS 8-7
//dynamic programming
#include<iostream>
using namespace std;
void cal_comp(int* arr,int **cache,int index,int size){
	int i;
	//complexity 1
	for(i=0;i<size-1;i++)
		if(arr[i]!=arr[i+1])
			break;
	if(i==size-1){
		cache[size-3][index]=1;
		return;
	}
	//complexity 2
	int diff;
	if(arr[i]>arr[i+1])
		diff=1;
	else
		diff=-1;
	for(i=0;i<size-1;i++)
		if(arr[i]-arr[i+1]!=diff)
			break;
	if(i==size-1){
		cache[size-3][index]=2;
		return;
	}
	//complexity 4
	int odd=arr[1],even=arr[0];
	for(i=0;i<size;i++){
		if(i%2==0){
			if(arr[i]!=even)
				break;
		}
		else
			if(arr[i]!=odd)
				break;
	}
	if(i==size){
		cache[size-3][index]=4;
		return;
	}
	//complexity 5
	diff=arr[0]-arr[1];
	for(i=0;i<size-1;i++){
		if(diff!=arr[i]-arr[i+1])
			break;
	}
	if(i==size-1){
		cache[size-3][index]=5;
		return;
	}
	//complexity 10
	cache[size-3][index]=10;
	return;
}
int min_complexity(int arr[10000],int **cache,int index,int size){
//already memozation
	if(cache[0][index]!=-1 
	&& cache[1][index]!=-1
	&& cache[2][index]!=-1){
		int ret=cache[0][index];
		ret=min(ret,cache[1][index]);
		return min(ret,cache[2][index]);
	}
//base case
	if(size<3)
		return 100000;
	else if(size>=3 && size<=5){
		cal_comp(&arr[index],cache,index,size);
		return cache[size-3][index];
	}
//caclulation
	int ret=100000;
	for(int i=0;i<3;i++){
		if(cache[i][index]==-1){
			cal_comp(&arr[index],cache,index,i+3);
		}
		cache[i][index]+=min_complexity(arr,cache,index+i+3,size-i-3);
		ret=min(ret,cache[i][index]);
	}
	return ret;
}
int main(){
	int Case;
	cin>>Case;
	int result[Case];
	for(int i=0;i<Case;i++){
		int **cache= new int*[3],*arr= new int[10000];
		for(int j=0;j<3;j++)
			cache[j]=new int[10000];
		for(int j=0;j<30000;j++)
			cache[j/10000][j%10000]=-1;
		char input;
		input=cin.get()+1;
		int n=0;
		while(input!='\n'){
			input=cin.get();
			arr[n]=input-'0';
			n++;
		}
		result[i]=min_complexity(arr,cache,0,n-1);
	}
	for(int i=0;i<Case;i++)
		cout<<result[i]<<'\n';
}
