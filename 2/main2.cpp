#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

string inputName = "input.txt";

bool isReportSafe(string report);
bool isReportSafe2(string report);

int main(int argc, char** argv) {
	int part1ans = 0;
	int part2ans = 0;
	
	fstream inputFile;

	string line;
	inputFile.open(inputName, ios::in);
	while (getline(inputFile, line)) {
		//for each input line
		part1ans += isReportSafe(line);
		part2ans += isReportSafe2(line);
	}

	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}


bool isReportSafe(string report) {
	vector<int> numbers;
	std::stringstream ss(report);
	int number;
	while (ss >> number) {
		numbers.push_back(number);
	}
	bool inc = numbers.back() > numbers.front();
	for (int i = 1; i < numbers.size(); i++) {
		int adjDif = inc ? numbers[i] - numbers[i - 1] : numbers[i - 1] - numbers[i];
		if (adjDif <= 0 || adjDif > 3) {
			return false;
		}
	}

	return true;
}

bool isReportSafe2(string report) {
	vector<int> numbers;
	vector<int> numbersCopy;
	vector<int> numbersCopy2;
	std::stringstream ss(report);
	int number;
	while (ss >> number) {
		numbers.push_back(number);
	}
	numbersCopy = numbers;
	numbersCopy2 = numbers;
	numbersCopy2.erase(numbersCopy2.begin());
	bool inc = numbers.back() > numbers.front();
	bool oops = 0;
	bool failedOut = false;
	for (int i = 1; i < numbers.size(); i++) {
		int adjDif = inc ? numbers[i] - numbers[i - 1] : numbers[i - 1] - numbers[i];
		//cout << "comp:" << numbers[i-1] << ':' << numbers[i] << endl;
		if (adjDif <= 0 || adjDif > 3) {
			//cout << "oops" << oops << endl;
			if (oops == 0)
				numbers.erase(numbers.begin() + i-- - oops++);
			else {
				//cout << "fail";
				failedOut = true;
				break;
			}
		}
	}

	if (!failedOut)
		return true;

	failedOut = false;

	inc = !inc;
	oops = 0;
	for (int i = 1; i < numbersCopy.size(); i++) {
		int adjDif = inc ? numbersCopy[i] - numbersCopy[i - 1] : numbersCopy[i - 1] - numbersCopy[i];
		//cout << "comp:" << numbersCopy[i-1] << ':' << numbersCopy[i] << endl;
		if (adjDif <= 0 || adjDif > 3) {
			//cout << "oops" << oops << endl;
			if (oops == 0)
				numbersCopy.erase(numbersCopy.begin() + i-- - oops++);
			else {
				failedOut = true;
				//cout << "fail";
				break;
			}
		}
	}

	if (!failedOut)
		return true;

	inc = numbersCopy2.back() > numbersCopy2.front();
	for (int i = 1; i < numbersCopy2.size(); i++) {
		int adjDif = inc ? numbersCopy2[i] - numbersCopy2[i - 1] : numbersCopy2[i - 1] - numbersCopy2[i];
		//cout << "comp:" << numbersCopy2[i-1] << ':' << numbersCopy2[i] << endl;
		if (adjDif <= 0 || adjDif > 3) {
			return false;
		}
	}
	

	return true;
}