#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <unordered_set>
#include <chrono>

using namespace std;

string inputName = "input.txt";

struct PairHash {
	std::size_t operator()(const std::pair<int, int>& p) const {
		return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
	}
};

void inflate(vector<string>& m);
vector<pair<int, int>> floodFill(vector<string> m, pair<int, int> start);
int countSides(unordered_set<pair<int, int>, PairHash> s);

int main(int argc, char** argv) {
	int part1ans = 0;
	int part2ans = 0;

	fstream inputFile;

	vector<string> m;
	vector<pair<char, vector<pair<int, int>>>> c;
	
	string line;
	inputFile.open(inputName, ios::in);
	while (getline(inputFile, line))
		//for each input line
		m.push_back('~' + line + '~');

	m.push_back("");
	m.insert(m.cbegin(), "");
	for (int i = 0; i < m[1].size(); i++) {
		m.back().push_back('~');
		m.front().push_back('~');
	}

	inflate(m);
	auto found = m;

	for (int i = 0; i < m.size(); i++) {
		for (int j = 0; j < m[i].size() ; j++) {
			if (found[i][j] != '~') {
				auto inc = floodFill(m, make_pair(i, j));
				c.push_back(make_pair(found[i][j], inc));
				for (auto p : inc)
					found[p.first][p.second] = '~';
			}
		}
	}

	for (auto v : c) {
		unordered_set<pair<int, int>, PairHash> s;
		for (auto p : v.second)
			for (int j = -2; j <= 2; j+=2) 
				for (int k = -2; k <= 2; k+=2)
					if ((j == 0) ^ (k == 0)) 
						if (m[p.first + j][p.second + k] != v.first)
							s.insert(make_pair(p.first + j/2, p.second + k/2));
		
		int area = v.second.size();
		int perm = s.size();
		int sides = countSides(s);

		part1ans += area * perm;
		part2ans += area * sides;
	}

	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}



void inflate(vector<string>& m) {
	string fillString;
	for (int i = 0; i < m[0].size(); i++)
		fillString += '~';
	for (int i = m.size() - 1; i > 0; i--)
		m.insert(m.begin() + i, fillString);
	for (int i = m[0].size() - 1; i > 0; i--)
		for (int j = 0; j < m.size(); j++)
			m[j].insert(m[j].begin() + i, '~');
}

vector<pair<int, int>> floodFill(vector<string> m, pair<int, int> start) {
	vector<pair<int, int>> inc;
	vector < pair<int, int>> q;
	char c = m[start.first][start.second];
	q.push_back(start);
	while (q.size()) {
		auto e = q.back();
		q.pop_back();
		if (m[e.first][e.second] == c) {
			inc.push_back(e);
			m[e.first][e.second] = '~';
			q.push_back(make_pair(e.first + 2, e.second));
			q.push_back(make_pair(e.first, e.second + 2));
			q.push_back(make_pair(e.first - 2, e.second));
			q.push_back(make_pair(e.first, e.second - 2));
		}
	}
	return inc;
}


int countSides(unordered_set<pair<int, int>, PairHash> s) {
	int sides = 0;
	auto so = s;
	while (!s.empty()) {
		sides++;
		auto c = s.begin();
		if (c->first % 2) {
			//horriz
			int offset = 2;
			while (!so.contains(make_pair(c->first - 1, c->second + offset - 1))
				&& !so.contains(make_pair(c->first + 1, c->second + offset - 1))
				&&   s.contains(make_pair(c->first, c->second + offset))) {
				s.erase(make_pair(c->first, c->second + offset));
				offset += 2;
			}
			offset = -2;
			while (!so.contains(make_pair(c->first - 1, c->second + offset + 1))
				&& !so.contains(make_pair(c->first + 1, c->second + offset + 1))
				&&   s.contains(make_pair(c->first, c->second + offset))) {
				s.erase(make_pair(c->first, c->second + offset));
				offset -= 2;
			}
		}
		else {
			//vert
			int offset = 2;
			while (!so.contains(make_pair(c->first + offset - 1, c->second - 1))
				&& !so.contains(make_pair(c->first + offset - 1, c->second + 1))
				&&   s.contains(make_pair(c->first + offset, c->second))) {
				s.erase(make_pair(c->first + offset, c->second));
				offset += 2;
			}
			offset = -2;
			while (!so.contains(make_pair(c->first + offset + 1, c->second - 1))
				&& !so.contains(make_pair(c->first + offset + 1, c->second + 1))
				&&   s.contains(make_pair(c->first + offset, c->second))) {
				s.erase(make_pair(c->first + offset, c->second));
				offset -= 2;
			}
		}
		s.erase(make_pair(c->first, c->second));
	}
	return sides;
}