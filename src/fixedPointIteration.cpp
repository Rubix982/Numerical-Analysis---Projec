/*
* FIXED-POINT ALGORITHM 2.2
*
* To find a solution to p = g(p) given an
* initial approximation p0
*
* INPUT:  initial approximation; tolerance TOL;
*         maximum number of iterations NO.
*
* OUTPUT: approximate solution p or
*         a message that the method fails.
*/

#include <iostream>
#include <cmath>

using namespace std;

class fixedpoint
{
	private:
		int iteration;
		bool flag;
		float tolerance, answer,c, fc , p;
		float expression;
	public:
	
	fixedpoint() //initialising all variables with 0
	{
		iteration = 0;
		flag = false;
		tolerance = answer = c = fc = 0.0 ;
	}
	
	void menu()
	{
	
		cout<<"Enter pnot: ";
		cin>> p;
		
		cout<<"Enter Number of iterations: ";
		cin>>iteration;
		
		cout<<"Enter tolerance (example if tolerance is 10^-2 enter 0.01): ";
		cin>>tolerance;
		
		function();
	}
	
	void function()
	{
		for(int i = 1 ; i<iteration ; i++)
		{
		  fc = c;
		  c = 0.5 * pow((10-pow(p,3)),0.5); //Change Equation Here
		  p = c;
		  cout << "Iteration: "<<i<< " Value of c: "<<c;
		  cout<<"\n";
		  	float dif = fc-c ; 
		  	if (dif<0)
		  	{
		  		dif *= -1;
			}
			if((dif) < tolerance)
			{
			  cout<<"Number of iterations: "<< i;
			  cout<<"Final Answer: "<<c;
			  flag = true;
			  break;
			}
		}
			
		if(flag == false)
		{
			cout<<"Failed to Calculate Answer";
		}	
		 
	}
		
};

main()
{
	fixedpoint a;
	
	a.menu();
	
}
