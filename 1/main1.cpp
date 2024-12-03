#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

std::string inputName = "input.txt";

int main(int argc, char** argv) {
	int part1ans = 0;
	int part2ans = 0;
	
	std::fstream inputFile;

	std::vector<int> left;
	std::vector<int> right;

	std::string line;
	inputFile.open(inputName, std::ios::in);
	while (getline(inputFile, line)) {
		//for each input line
		left.push_back(std::stoi(line.substr(0, 5)));
		right.push_back(std::stoi(line.substr(8)));
	}

	std::sort(left.begin(), left.end());
	std::sort(right.begin(), right.end());

	std::map<int, int> rightCount;

	for (int rNum : right) {
		rightCount[rNum]++;
	}

	for (int i = 0; i < left.size(); i++) {
		part1ans += std::abs(left[i] - right[i]);
		part2ans += rightCount[left[i]] * left[i];
	}


	std::cout << "part one:" << part1ans << std::endl;
	std::cout << "part two:" << part2ans << std::endl;
	return 0;
}