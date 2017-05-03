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
	void connectEightCC_Pass3(ofstream&, ofstream&, ofstream&);
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
	vector <int> nonzero;
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

void ConnectEightCC::connectEightCC_Pass1(ofstream& outfile) {
	for(int i = 1; i <= numRows; ++i) {
		for(int j = 1; j <= numCols; ++j) {
			if(zeroFramedAry[i][j] != 0) {
				loadNeighbors(i,j,1);
				if(neighborMin == 0 && neighborMax == 0) {
					newLabel++;
					zeroFramedAry[i][j] = newLabel;
				}
				else if(neighborMin == neighborMax) {
					zeroFramedAry[i][j] = neighborMin;
				} else {
					zeroFramedAry[i][j] = neighborMin;
					EqAry[zeroFramedAry[i][j]] = neighborMin;
					zeroFramedAry[i][j] = neighborMin;
				}
			}
		}
	}
	maxVal = newLabel;
	prettyPrint(outfile, 1);
}

void ConnectEightCC::connectEightCC_Pass2(ofstream& outfile) {
	for(int i = numRows  + 1; i > 0; --i) {
		for(int j = numCols + 1; j > 0; j--) {
			if(zeroFramedAry[i][j] != 0) {
				loadNeighbors(i, j, 2);
				if(neighborMin != neighborMax) {
					EqAry[zeroFramedAry[i][j]] = neighborMin;
					if(zeroFramedAry[i][j] == maxVal)
						maxVal = neighborMin;
					zeroFramedAry[i][j] = neighborMin;
				}
			}
		}
	}
	prettyPrint(outfile, 2);
}

void ConnectEightCC::manageEqAry(ofstream& outfile) {
	int numLabelUsed = 1; 
	for(int i = 1; i < (numRows * numCols) / 2; ++i) {
		if(i == EqAry[i])
			EqAry[i] = numLabelUsed++;
		else
			EqAry[i] = EqAry[EqAry[i]];
	}
	outfile << endl << "EqAry:\n";
	for(int i = 0; i <= newLabel; i++) {
		outfile << setw(3) << left << i;
	}
	outfile << endl;
	for(int i = 0; i <= newLabel; ++i) {
		outfile << setw(3) << left << EqAry[i];
	}
	outfile << endl << endl;
}

void ConnectEightCC::connectEightCC_Pass3(ofstream& outfile, ofstream& imageout, ofstream& propertyout) {
	properties = new Property[newLabel + 1];
	for(int i = 0; i <= newLabel; ++i) {
		properties[i].label = i;
		properties[i].numPixels = 0;
		properties[i].minRow = numRows + 1; 
		properties[i].minCol = numCols + 1;
		properties[i].maxRow = 0;
		properties[i].maxCol = 0;
	}
	int data;
	for(int i = 1; i < numRows + 2; ++i) {
		for(int j = 1; j < numCols + 2; ++j) {
			if(zeroFramedAry[i][j] != 0) {
				zeroFramedAry[i][j] = EqAry[zeroFramedAry[i][j]];
				data = zeroFramedAry[i][j];
				properties[data].numPixels++;
				if(i < properties[data].minRow)
					properties[data].minRow = i - 1;
				else if(i > properties[data].maxRow)
					properties[data].maxRow = i - 1;
				if(j < properties[data].minCol)
					properties[data].minCol = j - 1;
				else if(j > properties[data].maxCol)
					properties[data].maxCol = j - 1;
			}
		}
	}
	maxVal = EqAry[maxVal];
	prettyPrint(outfile, 3);

	for(int i = 1; i <= EqAry[newLabel]; ++i) {
		propertyout << properties[i].label << " " << properties[i].numPixels << " " << 
		properties[i].minRow << " " << properties[i].minCol << " " << properties[i].maxRow <<
		" " << properties[i].maxCol;
		if(i < EqAry[newLabel])
			propertyout << "\n";
	}
	imageout << numRows << " " << numCols << " " << minVal << " " << EqAry[newLabel] << endl;
	for(int i = 1; i <= numRows; ++i) {
		for(int j = 1; j <= numCols; j++) {
			imageout << zeroFramedAry[i][j] << " ";
		}
		if(i != numRows)
			imageout << endl;
	}
}

int main(int argc, char* argv []) {
	ifstream infile;
	infile.open(argv[1]);
	ofstream outfile1;
	outfile1.open(argv[2]);
	ofstream outfile2;
	outfile2.open(argv[3]);
	ofstream outfile3;
	outfile3.open(argv[4]);

	ConnectEightCC* cc = new ConnectEightCC(infile);
	cc -> loadImage(infile);
	cc -> connectEightCC_Pass1(outfile1);
	cc -> connectEightCC_Pass2(outfile1);
	cc -> manageEqAry(outfile1);
	cc -> connectEightCC_Pass3(outfile1, outfile2, outfile3);

	infile.close();
	outfile1.close();
	outfile2.close();
	outfile3.close();
	delete  cc;
	return 0;

}





