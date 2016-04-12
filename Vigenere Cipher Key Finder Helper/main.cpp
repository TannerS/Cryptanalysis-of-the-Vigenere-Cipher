#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

// 48 for chiper 
static int len = 48;
void processString(int, int, std::fstream&);
void printElement(std::string, double, const int&, std::fstream&);
double getIC(const int, std::string);

int main()
{
	std::fstream input;
	std::fstream output;
	// starting key length
	int index = 2;

	for (int j = 2; j < 48; j++)
	{
		output.open("output.txt", std::ios::out | std::ios::app);
		output << "Key len = " << j << std::endl;
		output.close();
		index = j;
		for (int i = 0; i < index; i++)
		{
			input.open("file.txt", std::ios::in);
			processString(index, i, input);
			input.close();
		}
	}
	return 0;
}

void processString(int inc, int i, std::fstream& input)
{
	char next;
	int counter = 0;
	int offset = 0;
	std::vector<char> vec;
	std::fstream output;

		while (input >> next)
		{
			if (counter == (i + offset))
			{
				offset += inc;
				vec.push_back(next);
			}
			counter++;
		}

		output.open("output.txt", std::ios::out | std::ios::app);

		std::string temp;

		for (int i = 0; i < vec.size(); i++)
		{
			temp += vec.at(i);
		}

		printElement(temp, getIC(temp.size(), temp), temp.size(), output);

		output << std::endl;

		output.close();
	}

double getIC(const int size, std::string cipher)
{
	// plaintext = document.getElementById("p").value.toLowerCase().replace(/ [^a - z] / g, "");
	// i think this is a string after all char are lowercase and gets rid of anything not a char a-z, g = means global (all matches)
	const int english_alpha_size = 26;
	int char_count = 0;
	int counts[english_alpha_size] = { 0 };
	double sum = 0.0;
	double ic = 0.0;

	for (int i = 0; i < english_alpha_size; i++)
	{
		counts[i] = 0;
	}

	// size of ciphertext
	for (int i = 0; i < size; i++) 
	{
		int index = (int)(cipher.at(i) - 97);
		counts[index]++;
		char_count++;
	}

	for (int i = 0; i < english_alpha_size; i++)
	{
		sum += counts[i] * (counts[i] - 1);
	}

	ic = (double)sum / (double)(char_count*(char_count - 1));

	return ic;
}

void printElement(std::string t, double s, const int& width, std::fstream& stream)
{
	stream << std::fixed << std::setprecision(10) << std::left << t << std::setw(width) << " | " << s;
}

	