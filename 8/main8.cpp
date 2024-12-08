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


pair<int, int> subtractPairs(pair<int, int> l, pair<int, int> r);
pair<int, int> addPairs(pair<int, int> l, pair<int, int> r);

int main(int argc, char** argv) {
	int part1ans = 0;
	int part2ans = 0;

	fstream inputFile;

	map<char, vector<pair<int, int>>> locs;
	vector<string> m;

	string line;
	inputFile.open(inputName, ios::in);
	while (getline(inputFile, line)) {
		//for each input line
		for (int i = 0; i < line.size(); i++)
			if(line[i] != '.')
				locs[line[i]].push_back(make_pair(m.size(), i));

		m.push_back(line);
	}
	vector<string> voidMap = m;
	vector<string> voidMap2 = m;

	//part 1
	for (auto a : locs) {
		auto pairVec = a.second;
		for (int i = 0; i < pairVec.size(); i++)
			for (int j = 0; j < pairVec.size(); j++) {
				if (i == j)
					continue;
				auto voidSpot = addPairs(subtractPairs(pairVec[i], pairVec[j]), pairVec[i]);
				if (voidSpot.first >= 0 && voidSpot.second >= 0
					&& voidSpot.first < m.size() && voidSpot.second < m[0].size())
					voidMap[voidSpot.first][voidSpot.second] = '#';				
			}
	}

	//part 2
	for (auto a : locs) {
		auto pairVec = a.second;
		for (int i = 0; i < pairVec.size(); i++)
			for (int j = 0; j < pairVec.size(); j++) {
				if (i == j)
					continue;

				auto voidSpot = pairVec[i];
				auto voidOffset = subtractPairs(pairVec[i], pairVec[j]);

				do {
					voidMap2[voidSpot.first][voidSpot.second] = '#';
					voidSpot = addPairs(voidSpot, voidOffset);
				} while (voidSpot.first >= 0 && voidSpot.second >= 0
					&& voidSpot.first < m.size() && voidSpot.second < m[0].size());
			}
	}

	for (string s : voidMap)
		for (char c : s)
			part1ans += c == '#';

	for (string s : voidMap2)
		for (char c : s)
			part2ans += c == '#';


	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}

pair<int, int> subtractPairs(pair<int, int> l, pair<int, int> r) {
	return make_pair(l.first - r.first, l.second - r.second);
}

pair<int, int> addPairs(pair<int, int> l, pair<int, int> r) {
	return make_pair(l.first + r.first, l.second + r.second);
}