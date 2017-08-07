//10-6
//greedy algorithm
#include<iostream>
#include<math.h>
using namespace std;
//print array
void print(double* arr,int size){
	for(int i=0;i<size;i++)
		cout<<arr[i]<<' ';
}
//make (x,y) to point on [0,2pi)
void circle_to_line(double* line,double* X,double* Y,int size){
	for(int i=0;i<size;i++){
		if(Y[i]>0)
			line[i]=acos(X[i]/8.0);
		else if(Y[i]<0)
			line[i]=acos(-X[i]/8.0)+M_PI;
		else{
			if(X[i]>0)
				line[i]=0;
			else if(X[i]<0)
				line[i]=M_PI;
		}
	}
}
//cover range 2D to 1D
void rad_to_angle(double* radius,int size){
	for(int i=0;i<size;i++)
		radius[i]=asin(radius[i]/16.0)*2;
}
//find the first, which cover point 0
int fill_first(double* point,double* dis,int size,int index){
	for(int i=index+1;i<size;i++){
		if(point[i]-dis[i]<=0 || point[i]-dis[i]>=2*M_PI)
			return i;
	}
	return -1;
}

int find_best(double* line,double* angle,int size,double min){
	int ret=-1;
	for(int i=0;i<size;i++){
		if(line[i]-angle[i]<=min){
			if(ret==-1)
				ret = i;
			if(line[ret]+angle[ret]<line[i]+angle[i])
				ret = i;
		}
	}
	return ret;
}

int fill_line(double* line,double* angle,int size,double min,double max){
	int index=find_best(line,angle,size,min);
	if(min>=line[index]+angle[index])
		return 99999;
	if(max<=line[index]+angle[index])
		return 1;
	else
		return 1+fill_line(line,angle,size,line[index]+angle[index],max);
}
int main(){
	int Case;
	cin>>Case;
	int result[Case];
	for(int i=0;i<Case;i++){
		//input
		int num;
		cin>>num;
		double X[num],Y[num],r[num];
		for(int j=0;j<num;j++)
			cin>>X[j]>>Y[j]>>r[j];
		//change to simpler problem
		double line[num];
		circle_to_line(line,X,Y,num);
		rad_to_angle(r,num);
//		print(line,num);
//		cout<<'\n';
//		print(r,num);
//		cout<<'\n';
		//find solution
		int index=-1;
		int ret=99999;
		while( (index = fill_first(line,r,num,index)) != -1){
			if(line[index]+r[index]>2*M_PI)
				ret = min(ret, 
						fill_line(line, r, num, line[index]+r[index]-2*M_PI,
						   	line[index]-r[index]));
			else if(line[index]-r[index]<0)
				ret = min(ret,
						fill_line(line, r, num, line[index]+r[index], 
							line[index]-r[index]+2*M_PI));
			else if(line[index]+r[index]==2*M_PI)
				ret = min(ret,
						fill_line(line, r, num, line[index]-r[index], 2*M_PI));
			else
				ret = min(ret,
						fill_line(line, r, num, 0, line[index]+r[index]));
		}
		//store to array 'result'
		if(ret>100)
			result[i]=-1;
		else
			result[i]=ret+1;
	}
	//output
	for(int i=0;i<Case;i++){
		if(result[i]==-1)
			cout<<"IMPOSSIBLE"<<'\n';
		else
			cout<<result[i]<<'\n';
	}
	return 0;
}
