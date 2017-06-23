//Divide-conquer algorithm
//APSS 7-4
#include<iostream>
using namespace std;
int square(int* fences,int size){
	if(size==1)
		return fences[0];
	else{
		int result;
		result = max(square(fences,size/2),square(&fences[size/2],size/2+size%2));
		int left = size/2-1, right = size/2, height;
		height = min(fences[left], fences[right]);
		while(height*(right-left+1)<min(height,fences[right+1])*(right-left+2)){
			if(right==size-1)
				break;
			right++;
			height=min(height,fences[right]);
		}
		while(height*(right-left+1)<min(height,fences[left-1])*(right-left+2)){
			if(left==0)
				break;
			left--;
			height=min(height,fences[left]);
		}
		result =  max(result,height*(right-left+1));
		return result;
	}
}
int main(){
	int Case;
	cin>>Case;
	int result[Case];
	for(int i=0;i<Case;i++){
		int num;
		cin>>num;
		int* fences = new int[num];
		for(int j=0;j<num;j++)
			cin>>fences[j];
		result[i]=square(fences,num);
	}
	for(int i=0;i<Case;i++)
		cout<<result[i]<<'\n';
	return 0;
}
