//Calculator with functions like Addition, Subtraction,
//Multiplication, division, percentage and even Power.

#include<iostream>
#include<math.h>
#include<conio.h>

using namespace std;

void main()
{
	long double x,y;
	char ch,ar;
	do
       {
	
	cout<<"*WELCOME*";
	cout<<"This is a Calculator containing the following functions:" <<endl;
	cout<<"Addition, Subtraction, Multiplication, Division, Percentage and Power"<<endl;
	cout<<"Type [+] for Addition [-] for Subtraction [*] for Multiplication"<<endl;
	cout<<"[/] for Division [%] for Percentage [^] for Power"<<endl;
	cout<<" Enter Function To use =  ";
	cin>>ch;
	cout<<(char)7;
	cout<<endl;

	//For Addition
       if(ch=='+')
		{
		cout<<" You are using Addition";
		cout<<" Enter First Number= ";
		cin>>x;

		cout<<"Enter Second Number= ";
		cin>>y;

		cout<<"Your answer is ";
		cout<<x+y;
		cout<<(char)7;
		}
	// For Subtraction
	 if(ch=='-')
		{
		cout<<" You are using Subtraction";
		cout<<" Enter First Number= ";
		cin>>x;
		cout<<"Enter Second Number= ";
		cin>>y;
		cout<<"Your answer is ";
		cout<<x-y;
		cout<<(char)7;
		}
	// For Multiplication
	 if(ch=='*')
		{
		cout<<" You are using Multiplication";
		cout<<" Enter First Number= ";
		cin>>x;
		cout<<"Enter Second Number= ";
		cin>>y;
		cout<<"Your answer is ";
		cout<<x*y;
		cout<<(char)7;
		}
	// For Division
	 if(ch=='/')
		{
		cout<<" You are using Division";
		cout<<" Enter First Number= ";
		cin>>x;
		cout<<"Enter Second Number= ";
		cin>>y;
		cout<<"Your answer is ";
		cout<<x/y;
		cout<<(char)7;
		}
		// For Percentage
	 if(ch=='%')
		{
		cout<<"You are using Percentage";
		cout<<" Enter Number= ";
		cin>>x;
		cout<<"Enter Percentage= ";
		cin>>y;
		cout<<"Your answer is ";
		cout<<y/100*x;
		cout<<(char)7;
	}
		//For Power
	if(ch=='^')
		{
		cout<<"You are using Power";
		cout<<" Enter Number= ";
		cin>>x;
		cout<<"Enter Power= ";
		cin>>y;
		cout<<"Your answer is ";
		cout<<pow(x,y);
		cout<<(char)7;
	}
		cout<<endl;
		cout<<"Do you want to continue..Y/N?";
		cin>>ar;

		}
		while(ar=='Y'|| ar=='y');
		if(ar=='N' || ar=='n')
		{
			cout<<" Thankyou for using this Calculator.Good Bye.";
			cout<<"Press any key to exit.......";
		}

		getch();
		cout<<(char)7;

}