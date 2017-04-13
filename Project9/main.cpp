#include<iostream>
#include<fstream>
using namespace std;

class PointsExtraction {
private:
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int numOfDataPts;
	int** zeroFramedAry;

public:
	PointsExtraction(string);
	~PointsExtraction();
	void loadImage(string);

};

PointsExtraction::PointsExtraction(string inputFile) {
	ifstream readFile;
	readFile.open(inputFile);
	readFile >> numOfDataPts >> numRows >> numCols;
	int rowSize = numRows + 2; 
	int colSize = numCols + 2;

	zeroFramedAry = new int*[rowSize];
	for(int i = 0; i < rowSize; ++i) 
		zeroFramedAry[i] = new int[colSize]();
	readFile.close();
}

PointsExtraction::~PointsExtraction() {
	for(int i = 0; i < numRows + 2; ++i) 
		delete [] zeroFramedAry[i];
	delete [] zeroFramedAry;
}

void PointsExtraction::loadImage(string inputFile) {
	ifstream readFile;
	int numFromFile = -9999;
	readFile.open(inputFile);
	//skip the first three numbers
	for(int i = 0; i < 3; ++i)
		readFile >> numFromFile;

	for(int i = 1; i < numRows + 2; ++i) {
		for(int j = 1; j < numRows + 2; ++j) {
			readFile >> numFromFile;
			zeroFramedAry[i][j] = numFromFile;
		}
	}
}







