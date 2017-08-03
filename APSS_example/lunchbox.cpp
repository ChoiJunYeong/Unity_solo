//greedy algorithm
//APSS 10-2
#include<iostream>
using namespace std;
void sort_with(int* eat,int* heat,int size){
	if(size==1)
		return;
	else{
		sort_with(eat,heat,size/2);
		sort_with(&eat[size/2],&heat[size/2],size-size/2);
		int *temp1=new int[size],*temp2=new int[size];
		int left=0,right=size/2;
		for(int i=0;i<size;i++){
			if(left>=size/2){
				temp1[i]=eat[right];
				temp2[i]=heat[right];
				right++;
			}
			else if(right>=size){
				temp1[i]=eat[left];
				temp2[i]=heat[left];
				left++;
			}
			else if(eat[left]>eat[right]){
				temp1[i]=eat[left];
				temp2[i]=heat[left];
				left++;
			}
			else{
				temp1[i]=eat[right];
				temp2[i]=heat[right];
				right++;
			}
		}
		for(int i=0;i<size;i++){
			eat[i]=temp1[i];
			heat[i]=temp2[i];
		}
	}
}
int tot_heat_time(int *heat,int size){
	int sum=0;
	for(int i=0;i<size;i++)
		sum+=heat[i];
	return sum;
}
int tot_time(int *eat,int *heat,int time,int size){
	if(size==0)
		return time;
	if(eat[0]>time-heat[0])
		return heat[0]+tot_time(&eat[1],&heat[1],eat[0],size-1);
	else
		return heat[0]+tot_time(&eat[1],&heat[1],time-heat[0],size-1);
}
int main(){
	int Case;
	cin>>Case;
	int result[Case];
	for(int i=0;i<Case;i++){
		int num;
		cin>>num;
		int *eat=new int[num], *heat=new int[num];
		for(int j=0;j<num;j++)
			cin>>heat[j];
		for(int j=0;j<num;j++)
			cin>>eat[j];
		sort_with(eat,heat,num);
		result[i]=tot_time(eat, heat, tot_heat_time(heat,num)+eat[num-1], num);
	}
	for(int i=0;i<Case;i++)
		cout<<result[i]<<'\n';
	return 0;
}
