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

struct PairHash {
	std::size_t operator()(const std::pair<int, int>& p) const {
		return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
	}
};
void trailScoreR(const pair<int, int>& s, const vector<string>& m, int d, unordered_set<pair<int, int>, PairHash>& found, int& count);

int main(int argc, char** argv) {
	int part1ans = 0;
	int part2ans = 0;

	fstream inputFile;

	vector<string> m;

	string line;
	inputFile.open(inputName, ios::in);
	while (getline(inputFile, line)) 
		m.push_back(line);


	for (int i = 0; i < m.size(); i++)
		for (int j = 0; j < m[0].size(); j++)
			if (m[i][j] == '0') {
				unordered_set<pair<int, int>, PairHash> found;
				trailScoreR(make_pair(i, j), m, 1, found, part2ans);
				part1ans += found.size();
			}

	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}

void trailScoreR(const pair<int, int>& s, const vector<string>& m, int d, unordered_set<pair<int, int>, PairHash>& found, int& count) {
	int trailScore = 0;
	for (int dir = 0; dir < 4; dir++) {
			auto n = s;
		if (dir == 0)
			n.first--;
		else if (dir == 1)
			n.second--;
		else if (dir == 2)
			n.first++;
		if (dir == 3)
			n.second++;

		//if not in bounds
		if (n.first < 0 || n.first >= m.size() || n.second < 0 || n.second >= m[0].size())
			continue;
		//if number right
		if (m[n.first][n.second] != d + '0')
			continue;

		if (d == 9) {
			found.insert(n);
			count++;
		}
		else
			trailScoreR(n, m, d + 1, found, count);
	}
}