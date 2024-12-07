#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <unordered_set>

using namespace std;

string inputName = "input.txt";

bool isValidPlusTimes(vector<long long> s);
bool isValidPlusTimesConc(vector<long long> s);
int base10digitCount(int n);
std::vector<int> convertToBase3(long long number);


int main(int argc, char** argv) {
	long long part1ans = 0;
	long long part2ans = 0;

	fstream inputFile;

	vector<vector<long long>> e;

	string line;
	inputFile.open(inputName, ios::in);
	while (getline(inputFile, line)) {
		//for each input line
		vector<long long> items;
		std::stringstream ss(line);
		long long item;
		while (ss >> item) {
			items.push_back(item);
		}
		e.push_back(items);
		//all of line's items now in items
	}

	for (vector<long long> line : e) {
		bool p1Valid = isValidPlusTimes(line);
		part1ans += p1Valid * line[0];
		part2ans += p1Valid * line[0];
		if (!p1Valid)
			part2ans += isValidPlusTimesConc(line) * line[0];
	}

	cout << endl;
	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}



bool isValidPlusTimes(vector<long long> s) {
	int ops = s.size() - 2;	

	int counterMax = pow(2, ops);
	for (int counter = 0; counter < counterMax; counter++) {
		long long current = s[1];
		for (int position = 2; position < s.size(); position++)
			if ((counter) & (0b0000001 << position - 2))
				current *= s[position];
			else
				current += s[position];
		if (current == s[0])
			return true;
	}


	return false;
}


bool isValidPlusTimesConc(vector<long long> s) {
	int ops = s.size() - 2;

	int counterMax = pow(3, ops);
	for (int counter = 0; counter < counterMax; counter++) {
		vector<int> opArr = convertToBase3(counter);
		long long current = s[1];
		for (int position = 2; position < s.size(); position++) {
			int digit = position - 2 >= opArr.size() ? 0 : opArr[position - 2];

			if (digit == 0)
				current *= s[position];
			else if (digit == 1)
				current += s[position];
			else {
				int rDigs = base10digitCount(s[position]);
				for (int i = 0; i < rDigs; i++)
					current *= 10;
				current += s[position];
			}
		}
		if (current == s[0])
			return true;
	}

	return false;
}

std::vector<int> convertToBase3(long long number) {
	std::vector<int> base3Digits;

	if (number == 0) {
		base3Digits.push_back(0);
		return base3Digits;
	}

	while (number > 0) {
		base3Digits.push_back(number % 3);
		number /= 3;
	}

	return base3Digits;
}

int base10digitCount(int n) {
	return static_cast<int>(std::log10(n)) + 1;
}