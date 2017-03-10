#include<fstream>
#include<iostream>
using namespace std;

class Image {

private:
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int** zeroFramedAry;

public: 
	Image(string);
	void zeroFramed();
	void loadImage(string);
	int getNumRows();
	int getNumCols();
	int getMinVal();
	int getMaxVal();
};

Image::Image(string inputFile) {
	ifstream readFile;
	readFile.open(inputFile);
	readFile >> numRows >> numCols >>
	            minVal >> maxVal;
	int rowSize = numRows + 2;
	int colSize = numCols + 2;
	zeroFramedAry = new int*[rowSize];
	for(int i = 0; i < rowSize; ++i)
		zeroFramedAry[i] = new int[colSize](); 

	readFile.close();	           
}

Image::~Image() {
	int colSize = numCols + 2;
	for(int i = 0; i < colSize; ++i)
		delete [] zeroFramedAry[i];
	delete [] zeroFramedAry;
}

void Image::zeroFramed() {
	for(int i = 0; i <= numRows +1; i++) {
		zeroFramedAry[i][0]           = zeroFramedAry[i][1];
		zeroFramedAry[i][numCols + 1] = zeroFramedAry[i][numCols];
	}

	for(int j = 0; j <= numCols + 1; j++) {
		zeroFramedAry[0][j]           = zeroFramedAry[1][j];
		zeroFramedAry[numRows + 1][j] = zeroFramedAry[numRows][j];
	}
}

void Image::loadImage(string inputFile) {
	ifstream readFile;
	int pixelValue = -1;
	readFile.open(inputFile);
	for(int i = 0; i < 4; ++i)
		readFile >> pixelValue;

	for(int i = 1; i < rowSize; ++i) {
		for(int j = 1; j < colSize; ++j) {
			readFile >> pixelValue;
			zeroFramedAry[i][j] = pixelValue;
		}
	}
	readFile.close();
}

int Image::getNumRows() { return numRows; }

int Image::getNumCols() { return numCols; }

int Image::getMaxVal() { return maxVal; }

int Image::getMinVal() { return minVal; }

class Point {

private:
	int row;
	int col;

public: 
	Point(int, int);
	int getPointRow();
	int getPointCol();
	void setPointRow(int);
	void setPointCol(int);	
};

Point::Point(int rowVal, int colVal) {
	row = rowVal;
	col = colVal;
}

int Point::getPointRow() { return row; }

int Point::getPointCol() { return col; }

void Point::setPointRow(int rowVal) { row = rowVal; }

void Point::setPointCol(int colVal) { col = colVal; }

class ChainCode {

private: 
	Point neighborCoord[8];
	Point currentPoint;
	Point nextPoint;
	Point lastQ;
	Point nextDirTable[8];
	Point nextDir;
	Point Pchain;

public: 
	ChainCode();
	void loadNeighborCoord();
	void findNextPoint();
	void prettyPrint();
};

ChainCode::ChainCode() {

	for(int i = 0; i < 8; ++i) {
		neighborCoord[i].setPointRow = 0;
		neighborCoord[i].setPointCol = 0;
		nextDirTable[i].setPointRow  = 0;
		nextDirTable[i].setPointCol  = 0;
	}
}

void ChainCode::prettyPrint(string outputFile) {

	ofstream printToFile;
	printToFile.open(outputFile);
	int pixel_value = -1;
		printToFile << "Input Image Pretty Print" << endl;
		printToFile << endl;
		for(int i = 1; i <= numRows + 1; i++) {
			for(int j = 1; j <= numCols + 1; j++) {
				//pixel_value = firstAry[i][j];
				if(pixel_value == 1) 
					printToFile << pixel_value + " ";
				else 
				    printToFile << "  ";
			}
			printToFile << endl;
		}
}//prettyPrint method


















