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

struct puter {
	long long regA, regB, regC;
	vector<int> program;
	vector<int> outputV;
	int pointer = 0;

	//run next ins, return false if done
	bool runNext() {
		if(pointer >= program.size())
			return false;
		int ins = program[pointer];
		int op = program[pointer + 1];
		switch (ins) {
		case 0://adv
			regA = regA / (static_cast<long long>(0b1) << comboOprtetor(op));
			break;
		case 1://bxl
			regB = regB ^ op;
			break;
		case 2://bst
			regB = comboOprtetor(op) % 8;
			break;
		case 3://jnz
			if (regA == 0)
				break;
			else
				pointer = op - 2;
				break;
		case 4://bxc
			regB = regB ^ regC;
			break;
		case 5://out
			outputV.push_back(comboOprtetor(op) % 8);
			break;
		case 6://bdv
			regB = regA / (static_cast<long long>(0b1) << comboOprtetor(op));
			break;
		case 7://cdv
			regC = regA / (static_cast<long long>(0b1) << comboOprtetor(op));
			break;
		}
		pointer += 2;
		return true;
	}

	long long comboOprtetor(int i) {
		if (i < 4)
			return i;
		if (i == 4)
			return regA;
		if (i == 5)
			return regB;
		if (i == 6)
			return regC;
		return -1;
	}

	void programFromString(string s) {
		program.clear();
		for (int i = 0; i < s.size(); i += 2)
			program.push_back(s[i] - '0');
	}

	string outputString() {
		string output;
		output.push_back((char)(outputV[0] + '0'));
		for (int i = 1; i < outputV.size(); i++) {
			output.push_back(',');
			output.push_back((char)(outputV[i] + '0'));
		}
		return output;
	}
};

long long part2(long long start, int d, puter p);

int main(int argc, char** argv) {
	string part1ans;
	long long part2ans = 0;

	fstream inputFile;

	string line;
	inputFile.open(inputName, ios::in);
	int i = 0;
	puter p;
	while (getline(inputFile, line)) {
		//for each input line
		if (i == 0)
			p.regA = stoll(line.substr(12));
		else if (i == 1) 
			p.regB = stoll(line.substr(12));
		else if (i == 2)
			p.regC = stoll(line.substr(12));
		else if (i == 4)
			p.programFromString(line.substr(9));
		i++;
	}

	puter p2 = p;
	
	while (p.runNext());
	part1ans = p.outputString();

	part2ans = part2(0, p2.program.size() - 1, p2);

	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}

long long part2(long long start, int d, puter p) {
	if (d < 0)
		return start;
	long long check = start << 3;
	int target = p.program[d];
	for (long long maxCheck = check + 8; check < maxCheck; check++) {
		puter p3 = p;
		p3.regA = check;
		while (p3.runNext());
		if (p3.outputV.front() == target) {
			long long child = part2(check, d - 1, p);
			if (child != -1)
				return child;
		}
	}
	return -1;
}