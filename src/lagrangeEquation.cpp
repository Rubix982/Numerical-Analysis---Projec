/*
*   LAGRANGE EQUATION
*
*   The problem of determining a polynomial of degree one that passes through
*   the distinct points (x0, y0) and (x1, y1) is the same as approximating a
*   function f for which f (x0) = y0 and f (x1) = y1 by means of a first-degree
*   polynomial interpolating, or agreeing with, the values of f at the given
*   points. Using this polynomial for approximation within the interval given
*   by the endpoints is called polynomial interpolation.*
*
*   Define the functions
*       L0(x) = (x − x1)/(x0 − x1)  and L1(x) = (x − x0)/(x1 − x0)
*
*   INPUT:   ?
*
*
*   OUTPUT:  ?
*
*/


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
