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

void blink(vector<long long>& stones);
long long base10digitCount(long long n);

//map numer to depth-len pair
map<long long, map<long long, long long>> c;

long long evolve(long long n, long long d);

int main(long long argc, char** argv) {
	long long part1ans = 0;
	long long part2ans = 0;

	fstream inputFile;

	string line;
	inputFile.open(inputName, ios::in);
	vector<long long> stones;
	while (getline(inputFile, line)) {
		//for each input line
		std::stringstream ss(line);
		long long item;
		while (ss >> item)
			stones.push_back(item);
	}
	vector<long long> stones2 = stones;

	//for (long long i = 0; i < 25; i++)
	//	blink(stones);

	//part1ans = stones.size();

	for (long long n : stones2)
		part2ans += evolve(n, 75);

	cout << "part one:" << part1ans << endl;
	cout << "part two:" << part2ans << endl;
	return 0;
}


void blink(vector<long long>& stones) {
	for (long long i = 0; i < stones.size(); i++) {
		long long currStone = stones[i];
		if (currStone == 0)
			stones[i] = 1;
		else if (base10digitCount(currStone) % 2 == 0) {
			long long factor = 1;
			for (long long j = 0; j < base10digitCount(currStone) / 2; j++)
				factor *= 10;
			stones[i++] = currStone / factor;
			stones.insert(stones.begin() + i, currStone % factor);
		}
		else
			stones[i] *= 2024;
	}
}

long long evolve(long long n, long long d) {
	//if cached
	if (c.contains(n) && c[n].contains(d))
		return c[n][d];
	else
		if (d == 1) {
			vector<long long> vll;
			vll.push_back(n);
			blink(vll);
			c[n][1] = vll.size();
			return(vll.size());
		}
		else {
			long long sum = 0;
			vector<long long> vll;
			vll.push_back(n);
			blink(vll);
			for (long long i = 0; i < vll.size(); i++)
				sum += evolve(vll[i], d-1);
			//add to cache
			c[n][d] = sum;
			return sum;
		}
}


long long base10digitCount(long long n) {
	return static_cast<long long>(std::log10(n)) + 1;
}