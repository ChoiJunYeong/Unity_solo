//Karatsuba algorithm
//APSS 7-6
#include<iostream>
#include<string>
using namespace std;
int find_by_mul(string idols,string fans,int inum,int fnum){
	int count=0;
	for(int i=0;i<=fnum-inum;i++){
		int mm=0;
		for(int j=0;j<inum;j++){
			mm+=idols[j]*fans[i+j];
		}
		if(mm==0)
			count++;
	}
	return count;
}
int main(){
	int Case;
	cin>>Case;
	int result[Case];
	for(int i=0;i<Case;i++){
		string idols,fans;
		cin>>idols>>fans;
		for(int i=0; i<idols.size();i++){
			if(idols[i]=='F')
				idols[i]=0;
			else if(idols[i]='M')
				idols[i]=1;
		}
		for(int i=0;i<fans.size();i++){
			if(fans[i]=='F')
				fans[i]=0;
			else if(fans[i]=='M')
				fans[i]=1;
		}
		result[i]=find_by_mul(idols,fans,idols.size(),fans.size());
	}
	for(int i=0;i<Case;i++)
		cout<<result[i]<<'\n';
	return 0;
}
