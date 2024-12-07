#pragma once
#include <iostream>
#include "clsDate.h";
using namespace std;

class clsInputValidate
{
public:
	static bool IsNumberBetween(short Number, short From, short To)
	{
		return (Number >= From && Number <= To);
	}
	static bool IsNumberBetween(int Number, int From, int To)
	{
		return (Number >= From && Number <= To);
	}
	static bool IsNumberBetween(double Number, double From, double To)
	{
		return (Number >= From && Number <= To);
	}
	static bool IsDateBetween(clsDate Date, clsDate Date1, clsDate Date2)
	{
		bool Answer = ((clsDate::IsDate1AfterDate2(Date, Date1) &&
			clsDate::IsDate1BeforeDate2(Date, Date2))
			|| (clsDate::IsDate1AfterDate2(Date, Date2) &&
				clsDate::IsDate1BeforeDate2(Date, Date1)));
			return Answer;
	}

	static int ReadIntNumber(string Text = "Invalid Input, Try Again!")
	{
		int Number;
		cin >> Number;
		while (cin.fail())
		{
			// user didn't input a number
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << Text << endl;
			cin >> Number;
		}
		return Number;
	}
	static short ReadShortNumber(string Text = "Invalid Input, Try Again!")
	{
		short Number;
		cin >> Number;
		while (cin.fail())
		{
			// user didn't input a number
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << Text << endl;
			cin >> Number;
		}
		return Number;
	}
	static float ReadFloatNumber(string Text = "Invalid Input, Try Again!")
	{
		float Number;
		cin >> Number;
		while (cin.fail())
		{
			// user didn't input a number
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << Text << endl;
			cin >> Number;
		}
		return Number;
	}
	static double ReadDblNumber(string Text = "Invalid Input, Try Again!")
	{
		double Number;
		cin >> Number;
		while (cin.fail())
		{
			// user didn't input a number
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << Text << endl;
			cin >> Number;
		}
		return Number;
	}
	static int ReadIntNumberBetween(int From, int To, string Text =  "Invalid Input, Try Again!")
	{
		int Number;
		do
		{
			Number = ReadIntNumber();
			if(!IsNumberBetween(Number, From, To))
				cout << Text << endl;
		} while (!IsNumberBetween(Number, From, To));
		return Number;
	}
	static int ReadDblNumberBetween(int From, int To, string Text = "Invalid Input, Try Again!")
	{
		int Number;
		do
		{
			Number = ReadDblNumber();
			if (!IsNumberBetween(Number, From, To))
				cout << Text << endl;
		} while (!IsNumberBetween(Number, From, To));
		return Number;
	}

	static string ReadString(string Text = "")
	{	
		string InputString = "";
		if (Text != "")
			cout << Text << endl;
		getline(cin >> ws, InputString);
		return InputString;
	}
	static bool IsValideDate(clsDate Date)
	{
		return clsDate::IsValidDate(Date);
	}
	static short ReadShortNumberBetween(short From, short To, string Text)
	{
		short Number;
		do
		{
			Number = ReadShortNumber();
			if (!IsNumberBetween(Number, From, To))
				cout << Text << endl;
		} while (!IsNumberBetween(Number, From, To));
		
		return Number;

	}
};

