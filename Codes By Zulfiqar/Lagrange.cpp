#include<iostream>
#include<cmath>
using namespace std;
int main(){
	double *x,*y,a,*sum,sum1=0,d,s;
	int i,j,n;
	cout<<"Enter the Amount of Data: ";
	cin>>n;
	x = new double[n];
	y = new double[n];
	sum = new double[n];
	for(i=0;i<n;i++){
		cout<<"X"<<i<<": ";
		cin>>x[i];
		cout<<"Y"<<i<<": ";
		cin>>y[i];
	}
	cout<<"Enter the Point: ";
	cin>>a;
	for(i=0;i<n;i++){
		s = d = 1;
		sum[i] = 0;
		for(j=0;j<n;j++){
			if(j!=i){
				s = s*(a - x[j]);
				d = d*(x[i] - x[j]);
			}
		}
		sum[i] = sum[i] + (s/d);
		sum[i] = sum[i] * y[i];
		sum1 = sum1 + sum[i];
	}
	cout<<"The Answer Is: "<<sum1;
}
