#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>

using namespace sf;
using namespace std;

class CollisionMap {
private:
	vector<int> MapArray;
	int Nstb;
	int Nstr;
public:
	int getRows() { return Nstr; }

	int getCols() { return Nstb; }

	int* getPtr() { return &MapArray[0]; }

	void update(vector<int> mapArr, int str, int stb) {
		MapArray = mapArr;
		Nstr = str;
		Nstb = stb;
	}

	void updateElem(int i, int j, int val) {
		int nstr = i * Nstr;
		int nstb = j;
		int pos = nstr + nstb;
		MapArray[pos] = val;
	}

	int getElem(int i, int j) {
		int nstr = i * Nstr;
		int nstb = j;
		int pos = nstr + nstb;
		return MapArray[pos];
	}

	void createNewSize(int size) {
		vector<int> lvl(size * size, 2);
		for (int i = 0; i < size; i++) lvl[i] = 3;
		for (int i = size; i <= size * size - size; i += size) {
			lvl[i] = 3; lvl[i - 1] = 3;
		}
		for (int i = size * size - size; i < size * size; i++) lvl[i] = 3;
		MapArray = lvl;
		Nstb = size;
		Nstr = size;
	}

	void createBlank(int size, int n = 0) {
		vector<int> lvl(size * size, n);
		MapArray = lvl;
		Nstb = Nstr = size;
	}
};