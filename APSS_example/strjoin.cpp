//greedy algorithm
//APSS 10-4
#include<iostream>
using namespace std;
void sort(int* arr,int size){
	if(size==1)
		return;
	else if(size==2){
		if(arr[0]>arr[1]){
			int temp=arr[0];
			arr[0]=arr[1];
			arr[1]=temp;
		}
		return;
	}
	int pivot=size-1,left=0,right=size-2;
	do{
		while(arr[left]<=arr[pivot])
			left++;
		while(arr[right]>arr[pivot])
			right--;
		if(left<=right){
			int temp=arr[left];
			arr[left]=arr[right];
			arr[right]=temp;
			left++;
			right--;
		}
	}
	while(left<=right);
	if(left<pivot){
		int temp=arr[left];
		arr[left]=arr[pivot];
		arr[pivot]=temp;
		sort(arr,left);
		sort(&arr[left+1],size-left-1);
	}
	else
		sort(arr,size-1);
}
void insert(int* arr,int size){
	if(arr[0]<arr[1])
		return;
	int i=1,temp=arr[0];
	while(arr[i]<arr[0] && i<size)
		i++;
	for(int j=0;j<i-1;j++)
		arr[j]=arr[j+1];
	arr[i-1]=temp;
}
void print(int* str,int size){
	for(int i=0;i<size;i++)
		cout<<str[i]<<' ';
	cout<<'\n';
}

int strsum(int* str,int size){
	if(size==2)
		return str[0]+str[1];
	else if(size==1)
		return 0;
	else{
		str[1]+=str[0];
		int ret=str[1];
		insert(&str[1],size-1);
//		print(&str[1],size-1);
		return ret+strsum(&str[1],size-1);
	}

}
int main(){
	int Case;
	cin>>Case;
	int result[Case];
	for(int i=0;i<Case;i++){
		int num;
		cin>>num;
		int str[num];
		for(int j=0;j<num;j++)
			cin>>str[j];
		sort(str,num);
		result[i]=strsum(str,num);
//		cout<<"result["<<i<<"] is "<<result[i]<<'\n';
	}
	for(int i=0;i<Case;i++)
		cout<<result[i]<<'\n';
	return 0;
}
