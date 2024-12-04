#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

string inputName = "input.txt";

int main(int argc, char** argv) {
	int part1ans = 0;
	int part2ans = 0;

	fstream inputFile;

	vector<string> p;

	string line;
	inputFile.open(inputName, ios::in);
	while (getline(inputFile, line)) {
		p.push_back(line);
	}

	int puzzleW = p[0].size();
	int puzzleH = p.size();

	string toFind = "XMAS";
	int toFindSize = toFind.size();

	for (int i = 0; i < puzzleH; i++) {
		for (int j = 0; j < puzzleW; j++) {
			//check each dir
			if (p[i][j] != toFind[0])
				continue;

			bool dOk = puzzleH - toFindSize >= i;
			bool uOk = i + 1 >= toFindSize;
			bool lOk = j+1>=toFindSize;
			bool rOk = toFindSize + j - 1 <= puzzleW;

			//r-
			if (rOk) {
				int pos = 1;
				while (pos < toFindSize && toFind[pos] == p[i][j+pos])
					pos++;
				part1ans += pos == toFindSize;
			}
			
			//ur-
			if (uOk && rOk) {
				int pos = 1;
				while (pos < toFindSize && toFind[pos] == p[i - pos][j + pos])
					pos++;
				part1ans += pos == toFindSize;
			}

			//dr-
			if (dOk && rOk) {
				int pos = 1;
				while (pos < toFindSize && toFind[pos] == p[i + pos][j + pos])
					pos++;
				part1ans += pos == toFindSize;
			}

			//u-
			if (uOk) {
				int pos = 1;
				while (pos < toFindSize && toFind[pos] == p[i - pos][j])
					pos++;
				part1ans += pos == toFindSize;
			}

			//d-
			if (dOk) {
				int pos = 1;
				while (pos < toFindSize && toFind[pos] == p[i + pos][j])
					pos++;
				part1ans += pos == toFindSize;
			}

			//l-
			if (lOk)
			{
				int pos = 1;
				while (pos < toFindSize && toFind[pos] == p[i][j - pos])
					pos++;
				part1ans += pos == toFindSize;
			}

			//ul
			if (uOk && lOk) {
				int pos = 1;
				while (pos < toFindSize && toFind[pos] == p[i - pos][j-pos])
					pos++;
				part1ans += pos == toFindSize;
			}

			//dl
			if (dOk && lOk) {
				int pos = 1;
				while (pos < toFindSize && toFind[pos] == p[i + pos][j - pos])
					pos++;
				part1ans += pos == toFindSize;
			}
		}
	}


	for (int i = 1; i < puzzleH - 1; i++) {
		for (int j = 1; j < puzzleW - 1; j++) {
			if (p[i][j] != 'A')
				continue;
			bool urMas =
				   (p[i - 1][j - 1] == 'M' && p[i + 1][j + 1] == 'S')
				|| (p[i - 1][j - 1] == 'S' && p[i + 1][j + 1] == 'M');
			bool dlMas =
				   (p[i + 1][j - 1] == 'M' && p[i - 1][j + 1] == 'S')
				|| (p[i + 1][j - 1] == 'S' && p[i - 1][j + 1] == 'M');

			part2ans += (urMas && dlMas);
		}
	}



	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}