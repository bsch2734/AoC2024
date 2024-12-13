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

struct claw {
	pair<long long, long long> bA;
	pair<long long, long long> bB;
	pair<long long, long long> p;
};

pair<long long, long long> solveClaw(const claw& c, bool& success);
pair<long long, long long> solveClaw2(const claw& c, bool& success);

int main(long long argc, char** argv) {
	long long part1ans = 0;
	long long part2ans = 0;

	fstream inputFile;

	string line;

	vector<claw> v;

	inputFile.open(inputName, ios::in);
	while (getline(inputFile, line)) {
		//for each input line
		claw c;
		c.bA = make_pair(stoi(line.substr(line.find('X') + 1)),
						 stoi(line.substr(line.find('Y') + 1)));

		getline(inputFile, line);
		c.bB = make_pair(stoi(line.substr(line.find('X') + 1)),
						 stoi(line.substr(line.find('Y') + 1)));

		getline(inputFile, line);
		c.p = make_pair(stoi(line.substr(line.find('X') + 2)),
						stoi(line.substr(line.find('Y') + 2)));

		v.push_back(c);

		//skip empties
		getline(inputFile, line);
	}

	for (const auto& c : v) {
		bool canWin;
		auto ans = solveClaw(c, canWin);
		if (canWin)
			part1ans += 3 * ans.first + ans.second;
	}

	for (auto& c : v) {
		c.p.first  += 10000000000000;
		c.p.second += 10000000000000;
		bool canWin;
		auto ans = solveClaw2(c, canWin);
		if (canWin)
			part2ans += 3 * ans.first + ans.second;
	}

	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}


pair<long long, long long> solveClaw(const claw& c, bool& success) {
	success = false;
	for (long long i = 0; i < 100; i++)
		if (0 == (c.p.first - c.bA.first * i) % c.bB.first) {
			long long j = (c.p.first - c.bA.first * i) / c.bB.first;
			if (success =(c.bA.second * i + c.bB.second * j == c.p.second))
				return make_pair(i, j);
		}
	return pair<long long, long long>();
}


pair<long long, long long> solveClaw2(const claw& c, bool& success) {
	long long num = -c.bB.second * c.bA.first * c.p.first + c.p.second * c.bB.first * c.bA.first;
	long long den = c.bA.second * c.bB.first - c.bB.second * c.bA.first;

	if (success = ((num % den == 0) && (((num / den) % c.bA.first)==0)))
		return(make_pair((num / den) / c.bA.first, (c.p.second - c.bA.second * (num / den) / c.bA.first) / c.bB.second));
	
	return pair<long long, long long>();
}