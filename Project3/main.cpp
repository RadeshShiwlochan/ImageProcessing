#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

class ConnectEightCC {

private: 
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int newMin;
	int newMax;
	int newLabel;
	int neighborMin;
	int neighborMax;
	int** zeroFramedAry;
	int* neighborAry;
	int* EqAry;
	struct Property {
		int label;
		int numPixels;
		int minRow;
		int minCol;
		int maxRow;
		int maxCol;
	};
	Property* properties;

public:
	ConnectEightCC(ifstream&);
	~ConnectEightCC();
	void zeroFramed();
	void loadImage(ifstream&);
	void loadNeighbors(int, int, int);
	void connectEightCC_Pass1(ofstream&);
	void connectEightCC_Pass2(ofstream&);
	void connectEightCC_Pass3(ofstream&);
	void updateEqAry();
	void manageEqAry(ofstream&);
	void prettyPrint(ofstream&, int);

};

ConnectEightCC::ConnectEightCC(ifstream& infile) {

	infile >> numRows >> numCols >> minVal >> maxVal;
	int rowSize = numRows + 2;
	int colSize = numCols + 2;
	zeroFramedAry = new int*[rowSize];

	for(int i = 0; i < rowSize; ++i)
		zeroFramedAry[i] = new int[colSize]();

	neighborAry = new int[5];
	EqAry = new int[(numRows * numCols)/2];
	for(int j = 0; j < (numRows * numCols / 2); ++j)
		EqAry[j] = j;

	newMin = 9999;
	newMax = -9999;
	newLabel = 0;

}

ConnectEightCC::~ConnectEightCC() {

	for(int i = 0; i < numRows + 2; i++)
		delete [] zeroFramedAry[i];
	delete [] zeroFramedAry;

	delete [] neighborAry;
	delete [] properties;

}

void ConnectEightCC::zeroFramed() {

	for(int i = 0; i < numRows + 2; ++i) {
		zeroFramedAry[i][0] = 0;
		zeroFramedAry[i][numCols + 1] = 0;
	}

	for(int j = 0; j < numCols; ++j) {
		zeroFramedAry[0][j] = 0;
		zeroFramedAry[numRows + 1][j] = 0;
	}
}

void ConnectEightCC::loadImage(ifstream& infile) {

	for(int i = 0; i < numRows; ++i) {
		for(int j = 0; j < numCols; j++) {
			infile >> zeroFramedAry[i + 1][j + 1];
		}
	}
}

void ConnectEightCC::loadNeighbors(int row, int col, int passNum) {
	vector <int> nonzero = {};
	if(row == 0 || col == 0) {
		cerr << "Invalid index for 3 X 3 neighbors. Terminating!!\n";
		exit(1);
	}
	else {
		if(passNum % 2  == 1) {
			int index = 0;
			for(int i = -1; i < 1; ++i) {
				for(int j = -1; j < 2; j++) {
					if(index > 3)
						break;
					neighborAry[index] = zeroFramedAry[row + i][col + j];
					if(neighborAry[index] != 0)
						nonzero.push_back(neighborAry[index]);
					index++;
				}//for
			}//for
			if(nonzero.empty()) {
				neighborMax = 0;
				neighborMin = 0;
			} else {
				neighborMin = nonzero[0];
				neighborMax = nonzero[0];
				for(int i : nonzero) {
					if(i < neighborMin)
						neighborMin = i;
					if(i > neighborMax)
						neighborMax = i;
				}//for
			}//else
		}//if
		else {
			int index = 0;
			for(int i = 0; i < 2; ++i) {
				for(int j = -1; j < 2; j++) {
					if(i == 0 && j == -1)
						continue;
					if(index > 4)
						break;
					neighborAry[index] = zeroFramedAry[row + i][col + j];
					if(neighborAry[index] != 0)
						nonzero.push_back(neighborAry[index]);
					index++;
				}//for
			}//for
			if(nonzero.empty()) {
				neighborMin = 0;
				neighborMax = 0;
			} else {
				neighborMin = nonzero[0];
				neighborMax = nonzero[0];

				for(int i: nonzero) {
					if(i < neighborMin)
						neighborMin = i;
					if(i > neighborMax)
						neighborMax = i;
				}//for
			}//else
		}//else
	} //else 
}//loadNeighbors

void ConnectEightCC::prettyPrint(ofstream& outfile, int passNum) {
	outfile << "-------------------------------------------------------------" << endl;
	outfile << "Pass " << passNum << ":\n\n" << numRows << " " << numCols << " " << minVal 
	<< " " << maxVal;
	if(maxVal == 0)
		outfile.close();
	else {
		outfile << endl;
		for(int i = 0; i < numRows; ++i) {
			for(int j = 0; j < numCols; ++j) {
				if(zeroFramedAry[i + 1][j + 1] == 0)
					outfile << string("  ");
				else
					outfile << zeroFramedAry[i + 1][j + 1] << " ";
			}//for
			outfile << endl;
		}
	}

	outfile << endl << "EqAry:\n";
	for(int i = 0; i <= newLabel; ++i) {
		outfile << setw(3) << left << i;
	}
	outfile << endl;
	for(int i = 0; i <= newLabel; ++i) {
		outfile << setw(3) << left << EqAry[i];
	}
	outfile << endl << endl;
}








