//6-5 problem
//Using Brute-force search
#include<iostream>
#include<stdio.h>
using namespace std;
bool can_fill(char board[22][22],int h,int w){
	int count = 0;
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++)
			if(board[i][j]=='.')
				count++;
	if(count%3!=0)
		return false;
	return true;
}
int find_case(char board[22][22],int h,int w){
	int i,j;
	for(i=1;i<=h;i++){
		for(j=1;j<=w;j++)
			if(board[i][j]=='.')
				break;
		if(board[i][j]=='.')
			break;
	}
	if(h+1==i && w+1==j){
		return 1;
	}	
	int count = 0;
	board[i][j]='#';
	if(board[i+1][j]=='.'){
		board[i+1][j]='#';
		if(board[i+1][j+1]=='.'){
			board[i+1][j+1]='#';
			count+=find_case(board,h,w);
			board[i+1][j+1]='.';
		}
		if(board[i+1][j-1]=='.'){
			board[i+1][j-1]='#';
			count+=find_case(board,h,w);
			board[i+1][j-1]='.';
		}
		board[i+1][j]='.';
	}
	if(board[i][j+1]=='.'){
		board[i][j+1]='#';
		if(board[i+1][j]=='.'){
			board[i+1][j]='#';
			count+=find_case(board,h,w);
			board[i+1][j]='.';
		}
		if(board[i+1][j+1]=='.'){
			board[i+1][j+1]='#';
			count+=find_case(board,h,w);
			board[i+1][j+1]='.';
		}
		board[i][j+1]='.';
	}
	board[i][j]='.';
	return count;
}
int main(){
	int Case;
	cin>>Case;
	int result[Case];
	for(int i=0;i<Case;i++){
		int h,w;
		cin>>h>>w;
//pad for prevent index error
		char board[22][22];
//input board
		for(int j=1;j<=h;j++)
			for(int k=1;k<=w;k++)
				cin>>board[j][k];
//padding
		for(int j=0;j<h+2;j++){
			board[j][0]='#';
			board[j][w+1]='#';
		}
		for(int k=0;k<w+2;k++){
			board[0][k]='#';
			board[h+1][k]='#';
		}
		if(!can_fill(board,h,w)){
			result[i]=0;
			continue;
		}
		result[i] = find_case(board,h,w);
//check input
	}
	for(int i=0;i<Case;i++)
		cout<<result[i]<<'\n';
	return 0;
}
