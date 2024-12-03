#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <regex>

using namespace std;

string inputName = "input.txt";
int performMul(string input);


int main(int argc, char** argv) {
	int part1ans = 0;
	int part2ans = 0;
	
	fstream inputFile;

	std::regex pattern(R"(mul\(\d{1,3},\d{1,3}\))");
	std::regex patternPt2(R"(mul\(\d{1,3},\d{1,3}\)|do\(\)|don't\(\))");

	string line;
	inputFile.open(inputName, ios::in);
	std::vector<std::string> matches;
	std::vector<std::string> matchesPt2;
	while (getline(inputFile, line)) {
		//for each input line

		sregex_iterator begin = sregex_iterator(line.begin(), line.end(), pattern);
		sregex_iterator end   = sregex_iterator();
		for (sregex_iterator it = begin; it != end; ++it)
			matches.push_back(it->str());

		begin = sregex_iterator(line.begin(), line.end(), patternPt2);
		end = sregex_iterator();
		for (sregex_iterator it = begin; it != end; ++it)
			matchesPt2.push_back(it->str());
	}

	for (string s : matches) {
		part1ans += performMul(s);
	}

	bool isCounting = true;
	for (string s : matchesPt2) {
		char det = s[2];
		if (det == '(')
			isCounting = true;
		else if (det == 'n')
			isCounting = false;
		else if (isCounting)
			part2ans += performMul(s);
	}

	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}

int performMul(string input) {
	return stoi(input.substr(4)) * stoi(input.substr(input.find(',') + 1));
}

