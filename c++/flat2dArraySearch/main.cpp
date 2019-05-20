#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
using namespace::std;

int abs(int n)
{
	return n > 0 ? n : -n;
}


int flattenXY(int col, int row, int width)
{
	return col + (row * width);
}


void printMap(int* map, int width, int height)
{
	for (int row = 0; row < height; row++) {
		cout << "|";
		for (int col = 0; col < width; col++) {
			int index = flattenXY(col, row, width);
			if (map[index] < 10) {
				cout << " ";
			}
			cout << map[index] << "|";
		}
		cout << endl;
	}
}

void traverseGradient(
	vector<int>* moves,
	int* directedCostMap,
	int xpos, int ypos, int cols, int rows)
{
	int maxIndex = cols * rows;
	int costIndex = flattenXY(xpos, ypos, cols);
	int myCost = directedCostMap[costIndex];
	if (myCost == 0) {
		return;
	}

	int rightIndex = costIndex + 1;
	if (rightIndex < maxIndex) {
		int rightCost = directedCostMap[rightIndex];
		if (rightCost < myCost) {
			cout << "moving right" << endl;
			moves->push_back(rightIndex);
			traverseGradient(moves, directedCostMap, xpos + 1, ypos, cols, rows);
			return;
		}
	}

	int downIndex = costIndex + cols;
	if (downIndex < maxIndex) {
		int downCost = directedCostMap[downIndex];
		if (downCost < myCost) {
			cout << "moving down" << endl;
			moves->push_back(downIndex);
			traverseGradient(moves, directedCostMap, xpos, ypos + 1, cols, rows);
			return;
		}
	}

	int leftIndex = costIndex - 1;
	if (leftIndex > 0) {
		int leftCost = directedCostMap[leftIndex];
		if (leftCost < myCost) {
			cout << "moving left" << endl;
			moves->push_back(leftIndex);
			traverseGradient(moves, directedCostMap, xpos - 1, ypos, cols, rows);
			return;
		}
	}

	int upIndex = costIndex - cols;
	if (upIndex > 0) {
		int upCost = directedCostMap[upIndex];
		if (upCost < myCost) {
			cout << "moving up" << endl;
			moves->push_back(upIndex);
			traverseGradient(moves, directedCostMap, xpos, ypos - 1, cols, rows);
			return;
		}
	}

}


void doGradient(
	vector<int>* moves,
	int* costMap,
	int intMapWidth,
	int intMapHeight,
	int startX,
	int startY,
	int endX,
	int endY)
{
	if (
		startX < 0 || endX < 0 || startY < 0 || endY < 0 ||
		startX >= intMapWidth || endX >= intMapWidth ||
		startY >= intMapHeight || startY >= intMapHeight) {
		cout << "invalid start or end coordinates" << endl;
		return;
	}

	int searchWidth = abs(endX - startX) + 1;
	int searchHeight = abs(endY - startY) + 1;
	int* searchCostMap = (int*) calloc(searchWidth * searchHeight, sizeof(int));
	int lastIndex = (searchWidth * searchHeight) - 1;
	cout << "lsi: " << lastIndex << endl;
	cout << "searchWidth " << searchWidth << endl;
	cout << "searchHeight " << searchHeight << endl;
	cout << endl;

	int ifStartLeft = endX > startX;
	int ifStartTop = endY > startY;
	int leftX = ifStartLeft ? startX : endX;
	int topY = ifStartTop ? startY : endY;
	int realX = startX;
	int realY = startY;
	int dist = 0;
	int costIndex = 0;
	int searchCostIndex = 0;
	int addCost = 0;
	for (int row = 0; row < searchHeight; row++) {
		realY = ifStartTop ? startY + row : startY - row;
		for (int col = 0; col < searchWidth; col++) {
			realX = ifStartLeft ? startX + col : startX - col;
			searchCostIndex = flattenXY(col, row, searchWidth);
			costIndex = flattenXY(realX, realY, intMapWidth);
			addCost = costMap[costIndex];
			dist = (searchWidth - col) + (searchHeight - row) - 2;
			searchCostMap[searchCostIndex] = dist + addCost;
		}
	}
	printMap(searchCostMap, searchWidth, searchHeight);
	cout << endl;

	traverseGradient(moves, searchCostMap, 0, 0, searchWidth, searchHeight);

	free(searchCostMap);
}

int main()
{
	srand(time(NULL));

	// init map of weights, where only < 1 is pathable
	int colMax = 15;
	int rowMax = 15;
	int* map = (int*) calloc(rowMax * colMax, sizeof(int));
	for (int col = 0; col < colMax; col++) {
		for (int row = 0; row < rowMax; row++) {
			int index = flattenXY(col, row, colMax);
			map[index] = 0;
		}
	}

	// set some weights
	map[flattenXY(1, 2, colMax)] = 1;
	map[flattenXY(5, 3, colMax)] = 1;
	map[flattenXY(5, 2, colMax)] = 1;
	printMap(map, colMax, rowMax);

	// build moves, start->end
	vector<int> path;
	doGradient(&path, map, colMax, rowMax, 1, 1, 3, 3);
	cout << "Moves: " << endl;
	for (int i = 0; i < path.size(); i++) {
		cout << path[i] << " ";
	}
	cout << endl;

	free(map);
	return 0;
}