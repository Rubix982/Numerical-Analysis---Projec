#include<iostream>
#include<cmath>
using namespace std;

double fun(double y){
	double x = y;
	double res;
	res =  pow(x,3) + 3*x +7;
	return res;
}
double fund(double y){
	double x = y;
	double res;
	res = 3*(pow(x,2)) + 3;
	return res;
}

int main(){
	int i=0;
	double x0,err,error;
	double ans,ans1;
	int iter;
	cout<<"The Equation Is: \n";
	cout<"x^3 + 3x + 7\n";
	cout<<"X0: ";
	cin>>x0;
	cout<<"Iterations: ";
	cin>>iter;
	cout<<"The Answer Should be Accurate To Within: ";
	cin>>err;
		for(int i=0;i<iter;i++){
			ans = x0 - (fun(x0)/fund(x0));
			if(i>0){
			error = ans - x0;
			cout<<"Iteration "<<i<<": "<<ans<<"  with error  "<<error<<"\n";
			error = abs(error);
			if(error<=err){
				break;
			}
			x0 = ans;
		}
			else
			{
			ans = x0 - (fun(x0)/fund(x0));	
			cout<<"Iteration: "<<i<<ans<<"\n";
			x0 = ans;
	}
}
}
