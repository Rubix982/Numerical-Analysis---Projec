#include <iostream>
#include <cmath>

using namespace std;

class falsi
{
	private:
		bool flag;
		int choice , iteration, power, *coefficient;
		float tolerance, answer,a,b,c, fc, fa , fb;

	public:

	falsi() //initialising all variables with 0
	{
		flag = false ;
		iteration = choice = power =0;
		tolerance = answer = a = b = c = fc = fa = fb = 0.0  ;
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

		  for(int j = power; j>=0 ; j--)
		  {
		   fa+= (coefficient[j] * pow(a,j));
		  }

		  for(int j = power; j>=0 ; j--)
		  {
		   fb+= (coefficient[j] * pow(b,j));
		  }

		  c = ((a * fb) - (b * fa))/(fb-fa) ;

		  cout << "Iteration: "<<i<< " Value of c: "<<c;
		  cout<<"\n";
		  fc = 0;

		  for(int j = power; j>=0 ; j--)
		  {
		   fc+= (coefficient[j] * pow(c,j));
		  }


		if(fc < 0)
		{
		  a = c;
		}
		else if (fc > 0)
		{
		  b = c;
		}
		float dif = b-a ;
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
	falsi a;

	a.menu();

}
