#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

string inputName = "input.txt";

int main(int argc, char** argv) {
	int part1ans = 0;
	int part2ans = 0;
	
	fstream inputFile;

	string line;
	inputFile.open(inputName, ios::in);
	while (getline(inputFile, line)) {
		//for each input line
		vector<int> items;
		std::stringstream ss(line);
		int item;
		while (ss >> item) {
			items.push_back(item);
		}
		//all of line's items now in items
	}

	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}