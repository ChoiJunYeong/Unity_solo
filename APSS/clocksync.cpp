#include<iostream>
using namespace std;
void find_min(int* arr){
	for(int i=0;i<4;i++)
		if(arr[i]!=-1){
			arr[0]=arr[i];
			break;
		}
	for(int i=1;i<4;i++){
		if(arr[0]>arr[i])
			if(arr[i]!=-1)
				arr[0]=arr[i];
	}
}



void spin(short clock[16],short swtch[10][5],int size,int fix){
	for(int i=0;i<5;i++){
		if(swtch[fix][i]!=-1)
			clock[swtch[fix][i]]+=size;
		else
			break;
	}
}



bool is_sync(short clock[16]){
	for(int i=0;i<16;i++)
		if(clock[i]%12!=0)
			return false;
	return true;
}



int find_sync(short clock[16],short swtch[10][5],int count,int fix){
	if(fix==10)
		return -1;
	if(is_sync(clock))
		return count;
	int result[4];
	for(int i=0;i<4;i++){
		result[i] =find_sync(clock,swtch,count+i,fix+1);
		spin(clock,swtch,3,fix);
	}
	find_min(result);
	spin(clock,swtch,-12,fix);
	return result[0];
}



int main(){
	int Case;
	cin>>Case;
	int result[Case];
	short swtch[10][5]={{0,1,2,-1,-1},{3,7,9,11,-1},{4,10,14,15,-1},{0,4,5,6,7},{6,7,8,10,12},{0,2,14,15,-1},{3,14,15,-1},{4,5,7,14,15},{1,2,3,4,5},{3,4,5,9,13}};
	for(int i=0;i<Case;i++){
		short clock[16],fix=0;
		for(int j=0;j<16;j++)
			cin>>clock[j];
		for(int j=0;j<16;j++){
			if(clock[j]!=12)
				break;
			fix++;
		}
		if(fix>15)
			result[i]=-1;
		else
			result[i]=find_sync(clock,swtch,0,0);
	}
	for(int i=0;i<Case;i++){
		cout<<result[i]<<'\n';
	}
	return 0;
}
