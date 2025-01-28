#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"

using namespace std;

class clsUtil
{
public:
    enum enCharType 
    {
        SamallChar= 1,
        CapitalChar = 2,
        Digit = 3,
        MixChars = 4,
        SpecialCharacter = 5
    };

    static void Srand()
    {
        //Seeds the random number generator in C++, called only once
        srand((unsigned)time(NULL));
    }

    static int RandomNumber(int From, int To)
    {
        //Function to generate a random number
        int randNum = rand() % (To - From + 1) + From;
        return randNum;
    }

    static char GetRandomCharacter(enCharType CharType)
    {
        //updated this method to accept mixchars
        if (CharType == MixChars)
        {
            //Capital/Samll/Digits only
            CharType = (enCharType)RandomNumber(1, 3);
        }

        switch (CharType)
        {
        case enCharType::SamallChar:
        {
            return char(RandomNumber(97, 122));
            break;
        }
        case enCharType::CapitalChar:
        {
            return char(RandomNumber(65, 90));
            break;
        }
        case enCharType::SpecialCharacter:
        {
            return char(RandomNumber(33, 47));
            break;
        }
        case enCharType::Digit:
        {
            return char(RandomNumber(48, 57));
            break;
        }
        default:
        {
            return char(RandomNumber(65, 90));
            break;
        }
        }
    }

    static string GenerateWord(enCharType CharType, short Length)
    {
        string Word;
        for (short i = 1; i <= Length; i++)
        {
            Word = Word + GetRandomCharacter(CharType);
        }
        return Word;
    }

    static string GenerateKey(enCharType CharType = CapitalChar)
    {
        string Key = "";
        Key = GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4) + "-";
        Key = Key + GenerateWord(CharType, 4);

        return Key;
    }

    static void GenerateKeys(short NumberOfKeys, enCharType CharType)
    {
        for (short i = 1; i <= NumberOfKeys; i++)
        {
            cout << "Key [" << i << "] : ";
            cout << GenerateKey(CharType) << endl;
        }
    }

    static void FillArrayWithRandomNumbers(int arr[100], int arrLength, int From, int To)
    {
        for (short i = 0; i < arrLength; i++)
            arr[i] = RandomNumber(From, To);
    }

    static void FillArrayWithRandomWords(string arr[100], int arrLength, enCharType CharType, short Wordlength)
    {
        for (short i = 0; i < arrLength; i++)
            arr[i] = GenerateWord(CharType, Wordlength);
    }

    static void FillArrayWithRandomKeys(string arr[100], int arrLength, enCharType CharType)
    {
        for (short i = 0; i < arrLength; i++)
            arr[i] = GenerateKey(CharType);
    }

    static void Swap(short& Number1, short& Number2)
    {
        short Temp = Number1;
        Number1 = Number2;
        Number2 = Temp;
    }

    static void Swap(int& Number1, int& Number2)
    {
        int Temp = Number1;
        Number1 = Number2;
        Number2 = Temp;
    }

    static void Swap(float& Number1, float& Number2)
    {
        float Temp = Number1;
        Number1 = Number2;
        Number2 = Temp;
    }

    static void Swap(double& Number1, double& Number2)
    {
        double Temp = Number1;
        Number1 = Number2;
        Number2 = Temp;
    }

    static void Swap(bool& Bool1, bool& Bool2)
    {
        bool Temp = Bool1;
        Bool1 = Bool2;
        Bool2 = Temp;
    }

    static void Swap(char& Char1, char& Char2)
    {
        char Temp = Char1;
        Char1 = Char2;
        Char2 = Temp;
    }

    static void Swap(string& Text1, string& Text2)
    {
        string Temp = Text1;
        Text1 = Text2;
        Text2 = Temp;
    }

    static void Swap(clsDate& Date1, clsDate& Date2)
    {
        clsDate::SwapDates(Date1, Date2);
    }

    static void ShuffleArray(int arr[100], int arrLength)
    {
        for (short i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }
    }

    static void ShuffleArray(string arr[100], int arrLength)
    {
        for (short i = 0; i < arrLength; i++)
        {
            Swap(arr[RandomNumber(1, arrLength) - 1], arr[RandomNumber(1, arrLength) - 1]);
        }
    }

    static string Tabs(short NumberOfTabs)
    {
        string t = "";

        for (short i = 1; i < NumberOfTabs; i++)
        {
            t = t + "\t";
            cout << t;
        }

        return t;
    }

    static string EncryptText(string Text, short EncryptionKey)
    {
        for (short i = 0; i <= Text.length(); i++)
        {
            Text[i] = char((int)Text[i] + EncryptionKey);
        }

        return Text;
    }

    static string DecryptText(string Text, short EncryptionKey)
    {
        for (short i = 0; i <= Text.length(); i++)
        {
            Text[i] = char((int)Text[i] - EncryptionKey);
        }

        return Text;
    }

    static string NumberToText(long long int number)
    {
        if (number == 0)
            return "";

        if (number >= 1 && number <= 19)
        {
           string Numbers[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"
                           ,"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };

		    return Numbers[number] + " ";
        }

        if (number >= 20 && number <= 99)
        {
           string Numbers2[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
            return Numbers2[number / 10] + " " + NumberToText(number % 10);
        }

	    if (number >= 100 && number <= 199)
		    return "One Hundred " + NumberToText(number % 100);
	
	    if (number >= 200 && number <= 999)
		    return NumberToText(number / 100) + " Hundred " + NumberToText(number % 100);

	    if (number >= 1000 && number <= 1999)
		    return  "One Thousand " + NumberToText(number % 1000);

	    if (number >= 2000 && number <= 999999)
		    return  NumberToText(number / 1000) + " Thousand " + NumberToText(number % 1000);

	    if (number >= 1000000 && number <= 1999999)
		    return  "One Million " + NumberToText(number % 1000000);

	    if (number >= 2000000 && number <= 999999999)
		    return NumberToText(number /1000000) + " Million " + NumberToText(number % 1000000);
	
	    if(number >= 1000000000 && number <= 1999999999 )
		    return  "One Billion " + NumberToText(number % 1000000000);
	
	    else 
		    return NumberToText(number / 1000000000) + " Billion " + NumberToText(number % 1000000000);
    }
};
