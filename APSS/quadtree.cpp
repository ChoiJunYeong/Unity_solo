//Divide-Conquer algorithm
//7-2
#include<iostream>
#include<string>
using namespace std;
string upside_down(string const& tree){
	if(tree.size()==1)
		return tree;
	string partition[4];
	int cousor = 0;
	for(int i=0;i<4;i++){
		if(tree[cousor]=='x'){
			cousor++;
			partition[i]='x'+upside_down(&tree[cousor]);
			cousor+=partition[i].size()-1;
		}
		else{
			partition[i]=tree[cousor];
			cousor++;
		}
		if(cousor>=tree.size())
			break;
	}
	cousor=0;
	string tree_copy="";
	for(int i=0;i<4;i++){
		tree_copy+=partition[(i+2)%4];
		cousor+=partition[(i+2)%4].size();
	}
	return tree_copy;
}
int main(){
	int Case;
	cin>>Case;
	string tree[Case];
	for(int i=0;i<Case;i++){
		cin>>tree[i];
		tree[i]=upside_down(tree[i]);
	}
	for(int i=0;i<Case;i++)
		cout<<"tree is " <<tree[i]<<'\n';
	return 0;
}
