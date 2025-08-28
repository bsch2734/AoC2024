#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <math.h>

using namespace std;

string inputName = "input.txt";

unordered_map<char, int> keys = {
	{'7', 0},
	{'8', 1},
	{'9', 2},
	{'4', 3},
	{'5', 4},
	{'6', 5},
	{'1', 6},
	{'2', 7},
	{'3', 8},
	{'X', 9},
	{'0', 10},
	{'A', 11},

	{'^', 10},
	{'<', 12},
	{'V', 13},
	{'>', 14}
};

vector<string> listPaths(int start, int end);

long long codeLen(string s, int depth);

struct TupleHash {
	std::size_t operator()(const std::tuple<int, int, int>& t) const {
		return std::hash<int>()(std::get<0>(t))
			^ (std::hash<int>()(std::get<1>(t)) << 1)
			^ (std::hash<int>()(std::get<2>(t)) << 2);
	}
};

unordered_map<tuple<int, int, int>, long long, TupleHash> minLengthMap;

long long minMoveLength(char start, char end, int depth);

int main(int argc, char** argv) {
	long long part1ans = 0;
	long long part2ans = 0;

	fstream inputFile;

	string line;
	inputFile.open(inputName, ios::in);
	vector<string> codes;
	while (getline(inputFile, line))
		codes.push_back(line);

	for (string s : codes) {
		part1ans += codeLen(s, 2) * stoi(s);
		part2ans += codeLen(s, 25) * stoi(s);
	}	

	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}

vector<string> listPaths(int start, int end) {
	vector<string> paths;
	if(start == end)
		return { "A" };
	
	int dx = end % 3 - start % 3;
	int dy = end / 3 - start / 3;

	//may divide by zero but will be ignored
	int signDx = dx? dx / abs(dx) : 0;
	int signDy = dy? dy / abs(dy) : 0;

	char xMove = "<>"[(signDx + 1) / 2];
	char yMove = "^V"[(signDy + 1) / 2];
	
	if (dx == 0 || dy == 0) { //go straight
		string output;
		for (int col = end % 3; col != start % 3; col -= signDx)
			output += xMove;
		for (int row = end / 3; row != start / 3; row -= signDy)
			output += yMove;
		paths.push_back(output + 'A');
		return paths;
	}

	//move in x if allowed
	int nextInX = start + signDx;
	if (keys['X'] != nextInX) {
		vector<string> continuations = listPaths(nextInX, end);
		for (string& s : continuations)
			s = xMove + s;
		paths.insert(paths.begin(), continuations.begin(), continuations.end());
	}

	//move in y if allowed
	int nextInY = start + 3 * signDy;
	if (keys['X'] != nextInY) {
		vector<string> continuations = listPaths(nextInY, end);
		for (string& s : continuations)
			s = yMove + s;
		paths.insert(paths.begin(), continuations.begin(), continuations.end());
	}

	return paths;
}

long long codeLen(string s, int depth) {
	long long len = 0;
	s = 'A' + s;
	for (int i = 0; i < s.size() - 1; i++)
		len += minMoveLength(s[i], s[i + 1], depth);
	return len;
}

long long minMoveLength(char start, char end, int depth) {
	//check cache
	auto itemItr = minLengthMap.find({ start, end, depth });
	if (itemItr != minLengthMap.end())
		return itemItr->second;

	auto paths = listPaths(keys[start], keys[end]);
	if (depth == 0)
		return paths[0].size();

	long long shortest = LLONG_MAX;
	for (string p : paths) {
		p = 'A' + p;
		long long len = 0;
		for (int i = 0; i < p.size() - 1; i++)
			len += minMoveLength(p[i], p[i + 1], depth - 1);
		shortest = min(shortest, len);
	}
	minLengthMap[{start, end, depth}] = shortest;
	return shortest;
}