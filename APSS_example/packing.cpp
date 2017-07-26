//APSS 9-2
//dynamic programming
#include<iostream>
#include<string>
using namespace std;
int make_result(int** cache,int* item_need,string* item_name,int index,int size,string* list){
	if(index==size)
		return 0;
	if(cache[index][0]<cache[index][1]){
		if(item_need[index]==cache[index][1]){
			*list+=item_name[index]+'\n';
			return 1;
		}
		*list+=item_name[index]+'\n';
		return 1+make_result(cache,item_need,item_name,index+1,size,list);
	}
	else
		return make_result(cache,item_need,item_name,index+1,size,list);
}
int pack(int** cache,int* item_weight,int* item_need,int index,int item_num,int max_weight){
	if(index==item_num)
		return 0;
	cache[index][0]=
		pack(cache, item_weight, item_need, index+1, item_num, max_weight);
	int ret=-1;
	if(max_weight>=item_weight[index]){
		cache[index][1]=
			pack(cache, item_weight, item_need, index+1, item_num, 
					max_weight-item_weight[index]) + item_need[index];
		ret=cache[index][1];
	}
	return max(ret,cache[index][0]);
}
int main(){
	int Case;
	cin>>Case;
	string result[Case];
	for(int i=0;i<Case;i++){
		//init
		int item_num,max_weight;
		cin>>item_num>>max_weight;
		string item_name[item_num];
		int item_weight[item_num],item_need[item_num];
		for(int j=0;j<item_num;j++)
			cin>>item_name[j]>>item_weight[j]>>item_need[j];
		int **cache=new int*[item_num];
		for(int j=0;j<item_num;j++){
			cache[j]=new int[2];
			for(int k=0;k<2;k++)
				cache[j][k]=-1;
		}
		//make cache
		pack(cache,item_weight,item_need,0,item_num,max_weight);
		//make result
		int need=max(cache[0][0],cache[0][1]);
		string list="";
		string *listptr=&list;
		int count = make_result(cache,item_need,item_name,0,item_num,listptr);
		result[i]=to_string(need)+' '+to_string(count)+'\n'+list;
		//print cache
/*		for(int j=0;j<item_num;j++){
			for(int k=0;k<2;k++)
				cout<<cache[j][k]<<' ';
			cout<<'\n';
		}*/
	}
	for(int i=0;i<Case;i++)
		cout<<result[i]<<'\n';
}
