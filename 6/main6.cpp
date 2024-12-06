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

enum ds {
	n = 0b0001,
	e = 0b0010,
	s = 0b0100,
	w = 0b1000
};

bool rayLeavesMap(pair<int, int> point, ds dir, vector<string> m);

int main(int argc, char** argv) {
	int part1ans = 0;
	int part2ans = 0;

	fstream inputFile;

	vector<string> map;

	string line;
	inputFile.open(inputName, ios::in);
	pair<int, int> p;
	while (getline(inputFile, line)) {
		int cPos = line.find('^');
		if (cPos != string::npos)
			p = make_pair(map.size(), cPos);
		map.push_back(line);
	}

	int dir = ds::n;

	map[p.first][p.second] = '~';

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			if (map[i][j] != '.')
				continue;
			map[i][j] = '#';
			part2ans += !rayLeavesMap(p, ds::n, map);
			map[i][j] = '.';
		}
	}
	

	//while in bounds
	while (p.first >= 0 && p.second >= 0 && p.first < map.size() && p.second < map[0].size()) {
		pair<int, int> next = p;
		switch (dir) {
		case ds::n:
			next.first--;
			break;
		case ds::e:
			next.second++;
			break;
		case ds::s:
			next.first++;
			break;
		case ds::w:
			next.second--;
			break;
		}
		//if next off map
		if (next.first < 0 || next.second < 0 || next.first >= map.size() || next.second >= map[0].size()) {
			p = next;
			continue;
		}
		if (map[next.first][next.second] != '#') {
			p = next;
			map[next.first][next.second] = '~';
			continue;
		}		

		switch (dir) {
		case ds::n:
			dir = ds::e;
			break;
		case ds::e:
			dir = ds::s;
			break;
		case ds::s:
			dir = ds::w;
			break;
		case ds::w:
			dir = ds::n;
			break;
		}
	}

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++)
			part1ans += map[i][j] == '~';
	}

	std::cout << "part one:" << part1ans << endl;
	std::cout << "part two:" << part2ans << endl;
	return 0;
}

struct PairHash {
	std::size_t operator()(const std::pair<int, int>& p) const {
		return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
	}
};


bool rayLeavesMap(pair<int, int> s, ds dir, vector<string> m) {
	unordered_set<pair<int, int>, PairHash> vn;
	unordered_set<pair<int, int>, PairHash> ve;
	unordered_set<pair<int, int>, PairHash> vs;
	unordered_set<pair<int, int>, PairHash> vw;

	//while p in bounds
	pair<int, int> c = s; //current
	pair<int, int> p = c; //previous
	while (c.first >= 0 && c.second >= 0 && c.first < m.size() && c.second < m[0].size()) {
		if (m[c.first][c.second] == '#') {
			c = p;
			switch (dir) {
			case ds::n:
				dir = ds::e;
				break;
			case ds::e:
				dir = ds::s;
				break;
			case ds::s:
				dir = ds::w;
				break;
			case ds::w:
				dir = ds::n;
				break;
			}
		}
		//c is valid, add to set
		unordered_set<pair<int,int>, PairHash>* toAddTo = nullptr;
		switch (dir) {
		case ds::n:
			toAddTo = &vn;
			break;
		case ds::e:
			toAddTo = &ve;
			break;
		case ds::s:
			toAddTo = &vs;
			break;
		case ds::w:
			toAddTo = &vw;
			break;
		}

		if (toAddTo->contains(c))
			return false;

		toAddTo->insert(c);

		//advance c
		p = c;
		switch (dir) {
		case ds::n:
			c.first--;
			break;
		case ds::e:
			c.second++;
			break;
		case ds::s:
			c.first++;
			break;
		case ds::w:
			c.second--;
			break;
		}
	}

	return true;
}