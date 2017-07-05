//APSS 8-9
//dynamic? programming
#include<iostream>
using namespace std;
void quick_sort(int* arr,int size){
	int left=0,right=size-2,pivot=size-1;
	while(left<right){
		while(arr[left]<arr[pivot] && left<pivot)
			left++;
		while(arr[right]>=arr[pivot] && right>0)
			right--;
		if(left<right){
			int temp=arr[left];
			arr[left]=arr[right];
			arr[right]=temp;
			left++;
			right--;
		}
	}
	if(left<pivot){
		int temp=arr[left];
		arr[left]=arr[pivot];
		arr[pivot]=temp;
		quick_sort(arr,left);
		quick_sort(&arr[left+1],size-left-1);
	}
}
int power(int* arr,int mean,int size){
	int ret=0;
	for(int i=0;i<size;i++)
		ret+=(arr[i]-mean)*(arr[i]-mean);
	return ret;
}
int min_stdev(int* arr,int size,int type){
	if(type==1){
		int mean=0;
		for(int i=0;i<size;i++)
			mean+=arr[i];
		mean/=size;
		int ret = min(power(arr,mean,size),power(arr,mean+1,size));    
		return ret;
	}
	int ret=987654321,sum=0;
	for(int i=0;i<=size-type;i++){
		sum+=arr[i];
		int eval = min(power(arr,sum/(i+1),i+1),power(arr,sum/(i+1)+1,i+1));
		ret=min(ret, eval + min_stdev(&arr[i+1],size-i-1,type-1));
	}
	return ret;
}
int main(){
	int Case;
	cin>>Case;
	int result[Case];
	for(int i=0;i<Case;i++){
		int len,type;
		cin>>len>>type;
		int arr[len];
		for(int j=0;j<len;j++)
			cin>>arr[j];
		quick_sort(arr,len);
		result[i]=min_stdev(arr,len,type);
	}
	for(int i=0;i<Case;i++)
		cout<<result[i]<<'\n';
	return 0;
}
