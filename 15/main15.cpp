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

bool makeMove(vector<string>& m, char c, pair<int, int>& p);
bool makeMoveThicc(vector<string>& nm, char c, pair<int, int>& p, bool actuallyMove);
pair<int, int> moveToOffset(char c);
vector<string> thiccify(vector<string> m);

int main(int argc, char** argv) {
	long long part1ans = 0;
	int part2ans = 0;

	fstream inputFile;

	vector<string> m;
	vector<char> s;
	bool mapDone = false;
	pair<int, int> p;
	int lineN = 0;

	string line;
	inputFile.open(inputName, ios::in);
	while (getline(inputFile, line)) {
		if (line.empty())
			mapDone = true;
		else if (!mapDone) {
			int robotAt = line.find('@');
			if (robotAt != string::npos)
				p = { lineN, robotAt };
			m.push_back(line);			
		}
		else
			for (char c : line)
				s.push_back(c);
		lineN++;
	}

	auto t = thiccify(m);
	auto p2 = p;
	p2.second *= 2;

	for (char c : s)
		makeMove(m, c, p);

	for (int i = 0; i < m.size(); i++) 
		for (int j = 0; j < m[0].size(); j++) 
			if (m[i][j] == 'O') 
				part1ans += 100 * i + j;

	for (char c : s)
		makeMoveThicc(t, c, p2, true);

	for (int i = 0; i < t.size(); i++)
		for (int j = 0; j < t[0].size(); j++)
			if (t[i][j] == '[')
				part2ans += 100 * i + j;


	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}


bool makeMove(vector<string>& m, char c, pair<int, int>& p) {
	auto offSet = moveToOffset(c);
	bool shouldMove = false;
	pair<int, int> next = { p.first + offSet.first, p.second + offSet.second };
	switch (m[next.first][next.second]) {
	case '#':
		shouldMove = false;
		break;
	case '.':
		shouldMove = true;
		break;
	case 'O':
		auto dummy = next;
		shouldMove = makeMove(m, c, dummy);
		break;
	}

	if (shouldMove) {
		m[next.first][next.second] = m[p.first][p.second];
		m[p.first][p.second] = '.';
		p = next;
	}

	return shouldMove;
}

pair<int, int> moveToOffset(char c) {
	switch (c) {
	case '<':
		return { 0, -1 };
		break;
	case '>':
		return { 0, 1 };
		break;
	case 'v':
		return { 1, 0 };
		break;
	case '^':
		return { -1, 0 };
		break;
	}
	return pair<int, int>();
}


vector<string> thiccify(vector<string> m) {
	vector<string> output;
	for (string s : m) {
		string line;
		for (char c : s)
			switch (c) {
			case '#':
				line.push_back('#');
				line.push_back('#');
				break;
			case 'O':
				line.push_back('[');
				line.push_back(']');
				break;
			case '.':
				line.push_back('.');
				line.push_back('.');
				break;
			case '@':
				line.push_back('@');
				line.push_back('.');
				break;
			}
		output.push_back(line);
	}
	return output;
}


bool makeMoveThicc(vector<string>& m, char c, pair<int, int>& p, bool actuallyMove){
	auto offSet = moveToOffset(c);
	bool shouldMove = false;
	pair<int, int> next = { p.first + offSet.first, p.second + offSet.second };
	switch (m[next.first][next.second]) {
	case '#':
		shouldMove = false;
		break;
	case '.':
		shouldMove = true;
		break;
	case '[':
	case ']':
		auto dummy = next;
		auto dummy2 = next;
		dummy2.second += (m[next.first][next.second] == '[') * 2 - 1;

		//horizontal push, same as non thicc
		if (offSet.first == 0)
			shouldMove = makeMoveThicc(m, c, dummy, true);
		//vertical push, more deps.
		else {
			shouldMove = makeMoveThicc(m, c, dummy, false) && makeMoveThicc(m, c, dummy2, false);
			if (shouldMove && actuallyMove)
				makeMoveThicc(m, c, dummy, true) && makeMoveThicc(m, c, dummy2, true);
		}

		break;
	}

	if (shouldMove && actuallyMove) {
		m[next.first][next.second] = m[p.first][p.second];
		m[p.first][p.second] = '.';
		p = next;
	}

	return shouldMove;
}