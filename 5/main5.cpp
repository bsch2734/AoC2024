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

bool isUpdateValid(vector<int> update, map<int, unordered_set<int>> rules);
void makeUpdateValid(vector<int>& update, map<int, unordered_set<int>> rules);

int main(int argc, char** argv) {
	int part1ans = 0;
	int part2ans = 0;

	fstream inputFile;

	map<int, unordered_set<int>> o;

	string line;
	bool isRules = true;
	vector<vector<int>> updates;
	inputFile.open(inputName, ios::in);
	while (getline(inputFile, line)) {
		if (line.size() == 0) {
			isRules = false;
			continue;
		}
		if (isRules) {
			o[stoi(line)].insert(stoi(line.substr(3)));
		}
		else {
			vector<int> update;
			for (int i = 0; i < line.size(); i += 3)
				update.push_back(stoi(line.substr(i, 2)));
			updates.push_back(update);
		}		
	}

	for (vector<int> u : updates) {
		if (isUpdateValid(u, o))
			part1ans += u[u.size() / 2];
		else {
			makeUpdateValid(u, o);
			part2ans += u[u.size() / 2];
		}
	}

	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}


bool isUpdateValid(vector<int> update, map<int, unordered_set<int>> rules){
	//check each page
	for (int i = update.size() - 1; i >= 0; i--)
		for (int j = i - 1; j >=0; j--)
			if ((rules[update[i]]).find(update[j]) != rules[update[i]].end())
				return false;
	return true;
}


void makeUpdateValid(vector<int>& update, map<int, unordered_set<int>> rules) {
	int numOrdered = 0;

	while (numOrdered < update.size() - 1) {
		//find the one nothing has to go after it
		for (int i = 0; i < update.size() - numOrdered; i++) {
			//testing if i is it
			//see if i has deps
			int num = update[i];
			//check if each j is a dep of i
			bool found = true;
			for (int j = 0; j < update.size() - numOrdered; j++)
				if (rules[update[i]].find(update[j]) != rules[update[i]].end()) {
					found = false;
					break;
				}
			if (found)
				swap(update[i], update[update.size() - ++numOrdered]);
		}
	}
}