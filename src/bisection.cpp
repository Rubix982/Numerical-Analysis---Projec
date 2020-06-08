/*
*   BISECTION ALGORITHM 2.1
*
*   To find a solution to f(x) = 0 given the continuous function
*   f on the interval [a,b], where f(a) and f(b) have
*   opposite signs:
*
*   INPUT:   endpoints a,b; tolerance TOL;
*            maximum number of iterations N0.
*
*   OUTPUT:  approximate solution p or
*            a message that the algorithm fails.
*/

#include <iostream>
#include <cmath>

using namespace std;

class bisection
{
	private:
		int choice , iteration, power, *coefficient;
		float tolerance, answer,a,b,c, fc, fa;

	public:

	bisection() //initialising all variables with 0
	{
		iteration = choice = power =0;
		tolerance = answer = a = b = c = fc = fa = 0.0 ;
	}

	void menu()
	{
		cout<< "Enter the highest power of x in the function f(x): ";
		cin>> power;
		coefficient =  new int[power+1];

		for(int i = 0 ; i<power+1 ; i++) //reads the expression for f(x) from the user
		{
			cout<< "Enter coefficient for X^"<<i<<" : ";
			cin>> coefficient[i];
		}

		cout<< "Expression: \nf(x) = ";
		for(int i = power; i>=0 ; i--)
		{
		    if(coefficient[i]>0)
		 	{
				if(i!=power)
				cout<<" + ";
			}
			else
			{
				cout<< " ";
			}
			cout<< coefficient[i]<<"x^"<<i;
		}

		cout<<"\nEnter a: ";
		cin>> a;

		cout<<"Enter b: ";
		cin>> b;

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
		  c = (a+b)/2;
		   cout << "Iteration: "<<i<< " Value of c: "<<c;
		   cout<<"\n";
		  fc = 0;

		  for(int j = power; j>=0 ; j--)
		  {
		   fc+= (coefficient[j] * pow(c,j));
		  }

		  if(fc == 0)
		  {
			cout<<"Number of iterations: "<< i;
			cout<<"Final Answer: "<<c;
			break;
		  }

		  else
		  {
		  	fa = 0;
		    for(int j = power; j>=0 ; j--)
		    {
		     fa+= (coefficient[j] * pow(c,j));
		    }

			if((fa > 0 && fc < 0) || (fa < 0 && fc > 0) )
			{
				b = c;
			}
			else
			{
				a = c;
			}

			if((b-a) <= tolerance)
			{
			  cout<<"Number of iterations: "<< i;
			  cout<<"Final Answer: "<<c;
			  break;
			}
		  }

		}
	}

};

main()
{
	bisection a;

	a.menu();

}