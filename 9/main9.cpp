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

vector<int> expand(string s);
vector<int> squash(vector<int> v);
vector<int> squash2(vector<int> v);
long long calcSum(vector<int> v);

int main(int argc, char** argv) {
	long long part1ans = 0;
	long long part2ans = 0;

	fstream inputFile;

	string line;
	inputFile.open(inputName, ios::in);
	while (getline(inputFile, line));

	auto e = expand(line);
	auto s = squash(e);

	auto s2 = squash2(e);

	part1ans = calcSum(s);
	part2ans = calcSum(s2);


	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}


vector<int> expand(string s) {
	vector<int> answer;

	for (int i = 0; i < s.size(); i++)
		for (int j = 0; j < s[i] - '0'; j++)
			if (i % 2)
				answer.push_back(-1);
			else
				answer.push_back(i / 2);

	return answer;
}


vector<int> squash(vector<int> v) {
	int l = 0;
	int r = v.size() - 1;
	while (l < r) {
		//get to first opening
		if (v[l] != -1) {
			l++;
			continue;
		}
		if (v[r] == -1) {
			r--;
			continue;
		}
		v[l] = v[r];
		v[r] = -1;
	}
	return v;
}


vector<int> squash2(vector<int> v) {
	int maxMovePos = v.size() - 1;
	for (int currToMove = v.back(); currToMove > 0; currToMove--) {
		//find start/ end of currToMove block
		while (v[maxMovePos] != currToMove)
			maxMovePos--;
		int currBlockEnd = maxMovePos;
		while (v[maxMovePos] == currToMove)
			maxMovePos--;
		int blockLen = currBlockEnd - maxMovePos;

		//try to move block
		int i = 0;
		bool inserted = false;
		int currOpenLen = 0;
		while (!inserted && i <= maxMovePos) {
			if (v[i] != -1)
				currOpenLen = 0;
			else
				currOpenLen++;
			if (currOpenLen == blockLen) {
				inserted = true;
				for (int j = 0; j < blockLen; j++) {
					v[j + i - blockLen + 1] = currToMove;
					v[j + maxMovePos + 1] = -1;
				}
			}
			i++;
		}
	}
	return v;
}


long long calcSum(vector<int> v) {
	long long answer = 0;

	for (int i = 0; i < v.size(); i++) {
		if (v[i] == -1)
			continue;
		answer += i * v[i];
	}

	return answer;
}