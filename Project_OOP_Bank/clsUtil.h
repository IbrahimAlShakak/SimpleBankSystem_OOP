#pragma once

#include <iostream>
#include<string>
#include "clsDate.h";
using namespace std;

class clsUtil
{
public:
	static void Srand()
	{
		srand((unsigned)time(NULL));
	}

	static short RandomNumber(short From, short To)
	{
		return rand() % (To - From + 1) + From;
	}

    static enum enCharType { SmallLetter, CapitalLetter, Digit, Special, MixChars};
    static char GetRandomCharacter(enCharType CharType)
    {
        switch (CharType)
        {
        case enCharType::SmallLetter:
            return char(RandomNumber(97, 122));
            break;

        case enCharType::CapitalLetter:
            return char(RandomNumber(65, 90));
            break;

        case enCharType::Special:
            return char(RandomNumber(33, 47));
            break;

        case enCharType::Digit:
            return char(RandomNumber(48, 57));
            break;
        case enCharType::MixChars:
            return GetRandomCharacter((enCharType)RandomNumber(0, 2));
            break;
        defualt:
            {
                return char(RandomNumber(65, 90));
                break;
            }

        }
    }

    static string GenerateWord(enCharType CharType, short Length)
    {
        string Word = "";
        for (short i = 0; i < Length; i++)
            Word += GetRandomCharacter(CharType);
        return Word;
    }

    static string GenerateKey(enCharType CharType)
    {
        string Key = "";
        for (short j = 1; j < 20; j++)
        {
            if (j == 5 || j == 10 || j == 15) Key += '-';
            else Key += GetRandomCharacter(CharType);
        }
        return Key;
    }
    static void GenerateKeys(short Number, enCharType CharType)
    {
        for (short i = 1; i <= Number; i++)
        {
            string Key = GenerateKey(CharType);
            cout << "Key[" << i << "]: " << Key << endl;
        }
    }

    static void Swap(int& Number1, int& Number2)
    {
        int temp = Number1;
        Number1 = Number2;
        Number2 = temp;
    }
    static void Swap(double& Number1, double& Number2)
    {
        double temp = Number1;
        Number1 = Number2;
        Number2 = temp;
    }
    static void Swap(string& S1, string& S2)
    {
        string temp = S1;
        S1 = S2;
        S2 = temp;
    }
    static void Swap(clsDate& Date1, clsDate& Date2)
    {
        short tempDay = Date1.Day;
        short tempMonth = Date1.Month;
        short tempYear = Date1.Year;
        Date1.Day = Date2.Day;
        Date1.Month = Date2.Month;
        Date1.Year = Date2.Year;
        Date2.Day = tempDay;
        Date2.Month = tempMonth;
        Date2.Year = tempYear;
    }

    static void ShuffleArray(int arr[], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);

        }
    }
    static void ShuffleArray(string arr[], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);

        }
    }
    
    static void PrintArray(int arr[], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
            cout << arr[i] << endl;
    }
    static void PrintArray(string arr[], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
            cout << arr[i] << endl;
    }

    static void FillArrayWithRandomNumbers(int arr[], int arrLength, short From, short To)
    {
        for (int i = 0; i < arrLength; i++)
        {
            arr[i] = RandomNumber(From, To);
        }
    }
    static void FillArrayWithRandomWords(string arr[], int arrLength, enCharType CharType, short WordLength)
    {
        for (int i = 0; i < arrLength; i++)
        {
            arr[i] = GenerateWord(CharType, WordLength);
        }
    }
    static void FillArrayWithRandomKeys(string arr[], int arrLength, enCharType CharType)
    {
        for (int i = 0; i < arrLength; i++)
        {
            arr[i] = GenerateKey(CharType);
        }
    }

    static string Tabs(short NumberOfTabs)
    {
        string Tabs = "";
        for (short i = 0; i < NumberOfTabs; i++)
            Tabs += "\t";
        return Tabs;
    }

    static string EncryptText(string Text, short Key)
    {
        string EncryptedText = "";
        for (short i = 0; i < Text.size(); i++)
        {
            int tempLetter = (int)Text[i] + Key;
            EncryptedText += char(tempLetter);
        }
        return EncryptedText;
    }
    static string DecryptText(string Text, short Key)
    {
        string DecryptText = "";
        for (short i = 0; i < Text.size(); i++)
        {
            int tempLetter = (int)Text[i] - Key;
            DecryptText += char(tempLetter);
        }
        return DecryptText;
    }

    static string NumberToText(int Num)
    {
        if (Num == 0) return "";
        if (Num >= 1 && Num <= 19)
        {
            string Arr[] =
            {
                "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
                "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen",
                "Ninteen"
            };
            return Arr[Num] + " ";
        }
        if (Num >= 20 && Num <= 99)
        {
            string Arr[] =
            {
                "", "", "Twenty", "Thirty", "Fourty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
            };
            return Arr[Num / 10] + " " + NumberToText(Num % 10);
        }
        if (Num >= 100 && Num <= 199)
        {
            return "One Hundred " + NumberToText(Num % 100);
        }
        if (Num >= 200 && Num <= 999)
        {
            return NumberToText(Num / 100) + "Hundred " + NumberToText(Num % 100);
        }
        if (Num >= 1000 && Num <= 1999)
        {
            return "One Thousand " + NumberToText(Num % 1000);
        }
        if (Num >= 2000 && Num <= 999999)
        {
            return NumberToText(Num / 1000) + "Thousand " + NumberToText(Num % 1000);
        }
        if (Num >= 1000000 && Num <= 1999999)
        {
            return "One Million " + NumberToText(Num % 1000000);
        }
        if (Num >= 2000000 && Num <= 999999999)
        {
            return NumberToText(Num / 1000000) + "Millions " + NumberToText(Num % 1000000);
        }
        if (Num >= 1000000000 && Num <= 1999999999)
        {
            return "One Billion " + NumberToText(Num % 1000000000);
        }
        else
        {
            return NumberToText(Num / 1000000000) + "Billions " + NumberToText(Num % 1000000000);
        }
    }
};

