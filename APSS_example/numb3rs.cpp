//APSS 8-16
//dynamic programming
#include<iostream>
using namespace std;
void print(double** temp,int size){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++)
			cout<<temp[i][j]<<" ";
		cout<<'\n';
	}
}

void mat_mul(double** mat1,double** mat2,int size){
	double temp[size][size];
	for(int col=0;col<size;col++)
		for(int row=0;row<size;row++)
			temp[col][row]=0;
	for(int col=0;col<size;col++)
		for(int row=0;row<size;row++)
			for(int k=0;k<size;k++)
				temp[col][row]+=mat1[col][k]*mat2[k][row];
	for(int col=0;col<size;col++)
		for(int row=0;row<size;row++)
			mat2[col][row]=temp[col][row];
}
void mat_pow(double** mat1,double** mat2,int exp,int size){
	if(exp==1)
		return;
	if(exp==2){
		mat_mul(mat2,mat2,size);
		return;
	}
	else{
		mat_pow(mat1,mat2,exp/2,size);
		mat_mul(mat2,mat2,size);
		if(exp%2==1)
			mat_mul(mat1,mat2,size);
		return;
	}
}
int mat_sum(int** mat,int size,int col){
	int ret=0;
	for(int j=0;j<size;j++)
		ret+=mat[col][j];
	return ret;
}
int main(){
	int Case;
	cin>>Case;
	float* result[Case];
	int size[Case];
	for(int i=0;i<Case;i++){
		//input
		int city, day, central, guess_num;
		cin>>city>>day>>central;
		int **map=new int*[city];
		for(int j=0;j<city;j++)
			map[j]=new int[city];
		for(int col=0;col<city;col++)
			for(int row=0;row<city;row++)
				cin>>map[col][row];
		
		cin>>size[i];
		result[i] = new float[size[i]];
		int guess[size[i]];
		for(int j=0;j<size[i];j++)
			cin>>guess[j];
		//make probability graph
		double **prob=new double*[city],**prob_copy=new double*[city];
		for(int j=0;j<city;j++){
			prob[j]=new double[city];
			prob_copy[j]=new double[city];
		}
		for(int col=0;col<city;col++){
			int sum = mat_sum(map,city,col);
			for(int row=0;row<city;row++){
				prob[col][row]=1.0*map[col][row]/sum;
				prob_copy[col][row]=prob[col][row];
			}
		}
		mat_pow(prob_copy,prob,day,city);
		for(int j=0;j<size[i];j++){
			result[i][j]=prob[central][guess[j]];
		}
	}

	//print result
	for(int i=0;i<Case;i++){
		for(int j=0;j<size[i];j++)
			cout<<result[i][j]<<" ";
		cout<<'\n';
	}
	return 0;
}
