#include <iostream>
#include <map>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;


class DNA
{
private:
	// my original DNA map 
	map<char, char> dnaMap = { {'0', 'A'} , {'1','T' } , {'2', 'G'}, {'3','C'} };
	//map used for objective 2
	map<char, char> rnaMap = { {'0', 'A'} , {'1','U' } , {'2', 'G'}, {'3','C'} };
	// my map used objective 4 ...my complement map...A to T ...G to C and the inverse of course 
	map<char, char> complementDNAMap = { {'A', 'T'} , {'T','A' } , {'G', 'C'}, {'C','G'} };
	//map used to help get ascii values notices i flipped the keys and values here 
	map<char, int> letterToNumDNAMap = { {'A', 0} , {'T',1 } , {'G', 2}, {'C',3} };

public:
	/*THESE 3 FUNCTIONS BELOW HELPED W/ OBJECTIVE 1 & 2
	------base4String gets ASCII value of char and coverts it to a base 4 string
	----- i used base4 because it would give me a unique base 4 value for each possible charater in ASCII
	------ convertToDRNAStrand determines if is DNA or RNA also converts a char to the combination of ATGC
	------ endodeDRNA uses the first 2 functions above to create the complete encoded string of the input
	*/
	string base4String(int asciiValue)
	{
		string stringBase4 = "";
		while (asciiValue > 0)
		{
			//simple method of converting value to base4
			//remainer tell you what the value should be (either 0, 1 , 2 or 3)
			stringBase4 = to_string(asciiValue % 4) + stringBase4;
			//keep diving by 4 until you cant divide it no more
			asciiValue = asciiValue / 4;

		}

		return  stringBase4;

	}
	string convertToDRNAStrand(string value, bool isDNA)
	{
		string key = "";
		//ternary operator that helps figure out wether to use our DNA or RNA map
		map<char, char> tempMap = (isDNA) ? dnaMap : rnaMap;

		for (int i = 0; i < value.length(); i++)
		{
			//gets value one by one maps it to correct letter
			char temp = value[i];
			key += tempMap[temp];

		}

		return key;

	}
	string endodeDRNA(string code, bool isDNA)
	{
		string decoded = "";
		for (int i = 0; i < code.length(); i++)
		{
			//iterates through thee whole string passed using the 2 previous functions to get the complete encoding
			//append each letter to decode variable 
			char temp = code[i];
			// line below stores the ascii value of the char 
			int asciiValue = int(temp);
			string letterInBase4 = base4String(asciiValue);
			decoded += (isDNA) ? convertToDRNAStrand(letterInBase4, true) : convertToDRNAStrand(letterInBase4, false);
		}
		return decoded;
	}
	//


	//used for OBJECTIVE 3 ...used built in string function to find index of substring if it exist otherwise return -1
	int findIndex(string bigString, string substring)
	{
		auto value = bigString.find(substring);

		if (value == 4294967295) {
			return -1;
		}
		return value;
	}

	/*THESE NEXT 2 METHODS HELPED ME W/ OBJECTIVE 4
	I ASSUMED THAT A SUBSTRING COULD START ANYWHERE FOR EXAMPLE:
	"ATGCCATG"
	SUBSTRING COULD BE "GCC"
	THEN I WOULD RETURN 2 AS THE INDEX SINCE THE LONG STRING HAS GCC STARTING AT 2

	----stringToAscii used to convert a base4 string to its ascii value
	----flipString does the rest...it gets the complement of the call ...then uses the stringToAscii method to convert it ascii value then cast it to the actula
	character

	*/
	auto stringToAscii(string str)
	{
		//starting with exponent at 3 deducing 1 every iteration
		int exponent = 3;
		int value = 0;
		for (int i = 0; i < str.length(); i++)
		{
			//value turns out to be the complete sum of the base4 number: turns to its ascii equvilent 
			//pow is built in exponent function
			//letterToNumDNAMap used to get the value associated with the chars
			value += pow(4, exponent) * letterToNumDNAMap[str[i]];
			//deduce exponent so we can get the right POW
			exponent--;
		}
		return value;

	}


	auto flipString(string str)
	{
		// helps flip the string thats given (basically gets the compliment)
		for (int i = 0; i < str.length(); i++)
			str[i] = complementDNAMap[str[i]];


		string finalString = "";
		int iter = 0;
		while (iter < str.length())
		{
			//going 4 by 4 to get the 4 encoded letters
			string temp = str.substr(iter, 4);
			//cast the ASCII value to the actual character and append to finalString
			finalString += static_cast<char>(stringToAscii(temp));
			//move on to next 4
			iter += 4;


		}
		return finalString;
	}

	//function help for OBJECTIVE 5
	auto findLongestSubsequence(string strand1, string strand2)
	{
		auto len1 = strand1.length();
		auto len2 = strand2.length();

		int** arr = new int*[len1 + 1];
		//creating and initializing a 2D array of size len1 * len2 of the strands
		for (int i = 0; i < len1 + 1; i++)
			arr[i] = new int[len2 + 1];
		//initializing each value to 0
		for (int i = 0; i < len1 + 1; i++)
		{
			for (int j = 0; j < len2 + 1; j++)
			{
				arr[i][j] = 0;
			}
		}



		for (int i = 1; i <= len1; i++)
		{
			for (int j = 1; j <= len2; j++)
			{
				//if the character of strand 1 at index i is the same as the one in strand 2 at index j
				//we add 1 to the value of arr[i][j] to the value of arr[i-1][j-1] which is the current max count of
				//matching characters
				if (strand1[i - 1] == strand2[j - 1])
				{
					arr[i][j] = arr[i - 1][j - 1] + 1;
				}
				else
				{
					//if the characters didn't match, we just use the max value of the left or top value in the array
					arr[i][j] = max(arr[i - 1][j], arr[i][j - 1]);
				}
			}
		}

		//arr[len1+1][len2+1] will hold the length of the longest subsequence
		vector<char> longestSeq;
		int iter1 = len1;
		int iter2 = len2;

		//this while loop will get the longest subsequence in our array
		while (iter1 > 0 && iter2 > 0)
		{
			//if the characters match, we add it to the longestSeq array and decrement both
			//iterators
			if (strand1[iter1 - 1] == strand2[iter2 - 1])
			{
				longestSeq.push_back(strand1[iter1 - 1]);
				iter1--;
				iter2--;
			}
			else if (arr[iter1][iter2 - 1] >= arr[iter1 - 1][iter2])
			{
				//decrement iter2 if the above condition holds
				iter2--;
			}
			else
			{
				iter1--;
			}
		}

		string commonSub = "";

		for (int i = longestSeq.size() - 1; i >= 0; i--)
		{
			commonSub += longestSeq[i];

		}

		cout << commonSub << endl;

		return commonSub;

	}
};



int main()
{
	DNA dna1;



	string userInput;
	string methodInput; //obj2
	string subString;// obj3
	string longstring;//for 1-3
	string strand1; //obj 5
	string strand2; //obj5
	string obj4; //obj4
	cout << "OBJECTIVE 1" << endl << "Please input a string:";
	cin >> userInput;
	longstring = dna1.endodeDRNA(userInput, true);
	cout << "The ENCODED version of this string is: " << longstring << endl;

	cout << "OBJECTIVE 2" << endl << "Please input a medthod('RNA' or 'DNA' case sensitive):";
	cin >> methodInput;


	if (methodInput == "DNA")
		cout << "The ENCODED version of this string is: " << longstring << endl;
	else if (methodInput == "RNA")
		cout << "The ENCODED version of this string is: " << dna1.endodeDRNA(userInput, false) << endl;

	else
		cout << "user did not type DNA or RNA , moving on to objective 3" << endl;

	cout << "Objective 3" << endl;
	cout << "input the substring you're looking for and i'll tell you the index of where it starts" << endl;
	cin >> subString;
	cout << "The Index is " << dna1.findIndex(longstring, subString) << endl;

	cout << "Objective 4" << endl;
	cout << "Input a DNA strand that you would like to be decoded" << endl;
	cin >> obj4;

	cout << "The ASCII equivilant of the strand is (the first user input)  " << dna1.flipString(obj4) << endl;

	cout << "objective 5" << endl;
	cout << "Please input 2 DNA strands and i'll find the longest sub-sequence of it : " << endl;
	cin >> strand1;
	cout << "input the 2nd strand" << endl;
	cin >> strand2;
	cout << "the  longest subsequence is :" << dna1.findLongestSubsequence("AGGTAB", "GXTXAYB");
	//cout << dna1.findLongestSubsequence();






	return 0;
}