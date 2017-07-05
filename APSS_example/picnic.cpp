//6-3 problem
//Using Brute-force search
#include<iostream>
using namespace std;
int cal_comb(int student_num, int partner_num,bool* students, int* partners){
	if(student_num==0)
		return 1;
	else if(partner_num==0)
		return 0;
	int count=0;
	if(students[partners[0]]==false && students[partners[1]]==false){
		students[partners[0]]=true;
		students[partners[1]]=true;
		count+=cal_comb(student_num-2,partner_num-1,students,&partners[2]);
		students[partners[0]]=false;
		students[partners[1]]=false;
	}
	count+=cal_comb(student_num,partner_num-1,students,&partners[2]);
	return count;
}
int main(){
	int cases;
	cin>>cases;
	int result[cases];
	for(int i=0;i<cases;i++){
		int student_num,partner_num;
		cin>>student_num >>partner_num;
		int partners[partner_num*2];
		bool students[student_num];
		for(int j=0;j<student_num;j++)
			students[j]=false;
		for(int j=0;j<partner_num*2;j+=2)
			cin>>partners[j]>>partners[j+1];
		result[cases]=cal_comb(student_num, partner_num, students, partners);
	}
	for(int i=0;i<cases;i++)
		cout<<result[cases];
	return 0;
}
