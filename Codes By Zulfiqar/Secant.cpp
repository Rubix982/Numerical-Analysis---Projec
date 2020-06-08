#include<iostream>
using namespace std;
#include<cmath>
double fun(double y){
	double x = y;
	double res;
	res = pow(x,3) + 3*x + 7;
	return res;
}

int main(){
	cout<<"the Given Eqaution Is: ";
	cout<<"x^3 + 3x + 7=0\n";
	double a,b,err,ans,error;
	int iter,i;
	cout<<"Enter the First Value: ";
	cin>>a;
	cout<<"Enter the Second Value: ";
	cin>>b;
	cout<<"Iterations(0 if no iterations): ";
	cin>>iter;
	cout<<"the Answer should be accurate to within: ";
	cin>>err;
	if(iter>0){
		for(i=0;i<iter;i++){
			ans = a - ((fun(a)*(b-a))/(fun(b)-fun(a)));
			a = b;
			b = ans;
			if(i>0){
			error = b-a;
			error = abs(error);
			cout<<"\nAt Iteration "<<i<<": "<<ans<<" with error: "<<error;
			if(error<=err)
			break;
			}
			else
			cout<<"At Iteration "<<i<<": "<<ans;
		}
	}
	else{
		i = 0;
		while(error>err){
			
		}
	}
}
