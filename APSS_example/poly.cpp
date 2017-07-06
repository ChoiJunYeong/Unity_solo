//APSS 8-14
//dynamic programming
#include<iostream>
using namespace std;
//block[i][j] == (i blocks which has j blocks at first row)
void count_monotone(int** blocks,int num,int index){
	if(index==num+1)
		return;
	for(int i=1;i<=index;i++){
		for(int j=1;j<=index-i;j++){
			blocks[index][i]+=blocks[index-i][j] * (i+j-1);
			blocks[index][i]%=10000000;
		}
	}
	blocks[index][index]=1;
	count_monotone(blocks,num,index+1);
}
int main(){
	int Case;
	cin>>Case;
	int result[Case];
	int **blocks= new int*[101];
	//init block cache
	for(int i=0;i<101;i++){
		blocks[i]=new int[101];
		for(int j=0;j<101;j++)
			blocks[i][j]=0;
	}
	blocks[1][1]=1;

	//main
	for(int i=0;i<Case;i++){
		int num;
		cin>>num;
		count_monotone(blocks,num,1);
		result[i]=0;
		for(int j=1;j<=num;j++)
			result[i]+=blocks[num][j];
	}
	//result
	for(int i=0;i<Case;i++)
		cout<<result[i]%10000000<<'\n';
	return 0;
}
