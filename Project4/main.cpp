#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
using namespace std;

class DistTransform {
private: 
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int** zeroFramedAry;
	int** skeletonAry;

public:
	DistTransform(string);
	~DistTransform();
	void loadImage(string);
	void zeroFramed();
	void firstPassDistance();
	void secondPassDistance();
	void computeSkeleton();
	void mapInt2Char(int, ofstream&);
	void prettyPrintDistance(ofstream&, int);
	void prettyPrintDistanceForSkelArr(ofstream&);
	int getMinNghbrPass1(int, int);
	int getMinNghbrPass2(int, int);
	int minimum(int, int);
	bool allNghbrsGreaterOrEq(int, int);
	void distTransfrmImg(string);
	int getCurrentMin();
	int getCurrentMax();
	void printSkeletonImg(string);
	int getMinInSkelArr();
	int getMaxInSkelArr();
	void prettyPrint(string, string);
	void printArr();
};

DistTransform::DistTransform(string inputFile) {
	ifstream readFile;
	readFile.open(inputFile);
	readFile >> numRows >> numCols >> minVal >> maxVal;

	int rowSize = numRows + 2;
	int colSize = numCols + 2; 
	zeroFramedAry = new int*[rowSize];
	skeletonAry   = new int*[rowSize];

	for(int i = 0; i < rowSize; ++i) {
		zeroFramedAry[i] = new int[colSize]();
		skeletonAry[i] = new int[colSize]();
	}
	readFile.close();
}

DistTransform::~DistTransform() {
	for(int i = 0; i < numRows + 2; ++i) {
		delete [] zeroFramedAry[i];
		delete [] skeletonAry[i];
	}
	delete [] zeroFramedAry;
	delete [] skeletonAry;
}

void DistTransform::loadImage(string inputFile) {
	ifstream readFile;
	int numFromFile = -1;
	readFile.open(inputFile);

	//skip the header
	for(int i = 0; i < 4; ++i) {
			readFile >> numFromFile;
	}

	for(int i = 1; i <= numRows ; ++i) {
		for(int j = 1; j <= numCols; ++j) {
			readFile >> numFromFile;
			zeroFramedAry[i][j] = numFromFile;
		}
	}
	readFile.close();
}

void DistTransform::zeroFramed() {

	//zero framing left and right
	for(int i = 0; i <= numRows + 1; i++) {
		zeroFramedAry[i][0]           = zeroFramedAry[i][1];
		zeroFramedAry[i][numCols + 1] = zeroFramedAry[i][numCols];
	}
		//zero framing top and bottom
	for(int j = 0; j <= numCols + 1; j++) {
		zeroFramedAry[0][j]           = zeroFramedAry[1][j];
		zeroFramedAry[numRows + 1][j] = zeroFramedAry[numRows][j];
	}
}

void DistTransform::firstPassDistance() {
	int pixelValue = -9999;
	int min = 9999;
	for(int i = 1; i <= numRows; ++i) {
		for(int j = 1; j <= numCols; ++j) {
			pixelValue = zeroFramedAry[i][j];
			if(pixelValue > 0) {
				min = getMinNghbrPass1(i,j);
				zeroFramedAry[i][j] = min + 1;
			} 
		}
	}
}

void DistTransform::secondPassDistance() {
	int pixelValue = -9999;
	int min = 9999;
	for(int i = numRows; i >= 1; --i) {
		for(int j = numCols; j >= 1; --j) {
			pixelValue = zeroFramedAry[i][j];
			if(pixelValue > 0) {
				min = getMinNghbrPass2(i,j);
				zeroFramedAry[i][j] = minimum(pixelValue, (min + 1));
			}
		}
	}
}

void DistTransform::computeSkeleton() {
	int pixelValue;
	bool allNghbrsEq = false;
	for(int i = 1; i <= numRows; ++i) {
		for(int j = 1; j <= numCols; j++) {
			pixelValue = zeroFramedAry[i][j];
			if(pixelValue > 0 ) {
				allNghbrsEq = allNghbrsGreaterOrEq(i,j);
				if(allNghbrsEq)
					skeletonAry[i][j] = pixelValue;
				else
					skeletonAry[i][j] = 0;
				allNghbrsEq = false;
		 	}
		}
	}

}

void DistTransform::mapInt2Char(int pixelValue, ofstream& printToFile) {
	char buffer[33];
	printToFile << sprintf(buffer, "%d", pixelValue);
	
}

void DistTransform::prettyPrintDistance(ofstream& printToFile, int passNum) {
	printToFile << "This is Pass - " << passNum << endl;
	for(int i = 1; i <= numRows + 1; ++i ) {
		for(int j = 1; j <= numCols + 1; ++j) {
			int pixelValue = zeroFramedAry[i][j];
			if(pixelValue == 0)
				printToFile << "  ";
			else {
				printToFile << pixelValue << "  ";
			}	
		}
		printToFile << endl;
	}
}

void DistTransform::prettyPrintDistanceForSkelArr(ofstream& printToFile) {
	
	printToFile << "skeletonAry prettyDistance Print" << endl << endl;
	for(int i = 1; i <= numRows + 1; ++i ) {
		for(int j = 1; j <= numCols + 1; ++j) {
			if(skeletonAry[i][j] == 0)
				printToFile << "  ";
			else //call mapInt2Char here 
				printToFile << skeletonAry[i][j] << "  ";
		}
		printToFile << endl;
	}
}

int DistTransform::getMinNghbrPass1(int rowIndex, int colIndex) {
	int min = 9999;
	int nghArr[4];
	nghArr[0] = zeroFramedAry[rowIndex - 1][colIndex - 1];
	nghArr[1] = zeroFramedAry[rowIndex - 1][colIndex];
	nghArr[2] = zeroFramedAry[rowIndex - 1][colIndex + 1];
	nghArr[3] = zeroFramedAry[rowIndex][colIndex - 1];

	for(int i = 0; i < 4; ++i) {
		if(min > nghArr[i])
			min = nghArr[i];
	}
	return min;
}

int DistTransform::getMinNghbrPass2(int rowIndex, int colIndex) {
	int min = 9999;
	int nghArr[5];
	nghArr[0] = zeroFramedAry[rowIndex + 1][colIndex - 1];
	nghArr[1] = zeroFramedAry[rowIndex + 1][colIndex];
	nghArr[2] = zeroFramedAry[rowIndex + 1][colIndex + 1];
	nghArr[3] = zeroFramedAry[rowIndex][colIndex + 1];
	nghArr[4] = zeroFramedAry[rowIndex][colIndex];

	for(int i = 0; i < 4; ++i) {
		if(min > nghArr[i])
			min = nghArr[i];
	}
	return min;
}


bool DistTransform::allNghbrsGreaterOrEq(int rowIndex, int colIndex) {
	int nghArr[9];
	
	nghArr[0] = zeroFramedAry[rowIndex - 1][colIndex - 1];
	nghArr[1] = zeroFramedAry[rowIndex - 1][colIndex];
	nghArr[2] = zeroFramedAry[rowIndex - 1][colIndex + 1];
	nghArr[3] = zeroFramedAry[rowIndex][colIndex - 1];
	nghArr[4] = zeroFramedAry[rowIndex][colIndex + 1];
	nghArr[5] = zeroFramedAry[rowIndex + 1][colIndex - 1];
	nghArr[6] = zeroFramedAry[rowIndex + 1][colIndex];
	nghArr[7] = zeroFramedAry[rowIndex + 1][colIndex + 1];
	nghArr[8] = zeroFramedAry[rowIndex][colIndex];

	if(nghArr[8] >= nghArr[0] && nghArr[8] >= nghArr[1] &&
	   nghArr[8] >= nghArr[2] && nghArr[8] >= nghArr[3] &&
	   nghArr[8] >= nghArr[4] && nghArr[8] >= nghArr[5] &&
	   nghArr[8] >= nghArr[6] && nghArr[8] >= nghArr[7]     ) {
	  
		return true;
	}		
	return false;
}

int DistTransform::minimum(int pixelValue, int minNghbrplus1) {

	if (pixelValue <= minNghbrplus1) 
		return pixelValue;
	else 
		return minNghbrplus1;
}

void DistTransform::distTransfrmImg(string outputFile) {
	ofstream printToFile;
	printToFile.open(outputFile);
	int currentMin = getCurrentMin();
	int currentMax = getCurrentMax();

	printToFile << numRows << "  " << numCols << "  "
	<< currentMin << "  " << currentMax << endl << endl;

	for(int i = 1; i <= numRows + 1; ++i) {
		for(int j = 1; j <= numCols + 1; ++j) {
			printToFile << zeroFramedAry[i][j] << "  ";
		}
		printToFile << endl;
	}
}

int DistTransform::getCurrentMin() {
	int min = 9999;
	for(int i = 1; i <= numRows + 1; ++i) {
		for(int j = 1; j <= numCols + 1; ++j) {
			if(zeroFramedAry[i][j] < min)
				min = zeroFramedAry[i][j];
		}
	}
	return min;
}

int DistTransform::getCurrentMax() {
	int max = -9999;
	for(int i = 1; i <= numRows + 1; ++i) {
		for(int j = 1; j <= numCols + 1; ++j) {
			if(zeroFramedAry[i][j] > max)
				max = zeroFramedAry[i][j];
		}
	}
	return max;
}

void DistTransform::printSkeletonImg(string outputFile) {
	int minInSkelArr = getMinInSkelArr();
	int maxInSkelArr = getMaxInSkelArr();
	ofstream printToFile;
	printToFile.open(outputFile);
	printToFile << numRows << "  " << numCols << "  "
	<< minInSkelArr << "  " << maxInSkelArr << endl << endl;
	for(int i = 1; i <= numRows + 1; ++i) {
		for(int j = 1; j <= numCols + 1; ++j) {
			printToFile << skeletonAry[i][j] << "  ";
		}
		printToFile << endl;
	}
	printToFile.close();
}

int DistTransform::getMinInSkelArr() {
	int min = 9999;
	for(int i = 1; i <= numRows + 1; ++i) {
		for(int j = 1; j <= numCols + 1; ++j) {
			if(skeletonAry[i][j] < min)
				min = skeletonAry[i][j];
		}
	}
	return min;
}

int DistTransform::getMaxInSkelArr() {
	int max = -9999;
	for(int i = 1; i <= numRows + 1; ++i) {
		for(int j = 1; j <= numCols + 1; ++j) {
			if(skeletonAry[i][j] > max)
				max = skeletonAry[i][j];
		}
	}
	return max;
}

void DistTransform::prettyPrint(string inputFile, string outputFile) {
	ifstream readFile;
	ofstream printToFile;
	readFile.open(inputFile);
	printToFile.open(outputFile);
	int pixelValue = -1;
	readFile >> pixelValue >> pixelValue >> pixelValue 
	>> pixelValue; 
	printToFile << "This is the Input Image" << endl << endl;

	printToFile << numRows << " " << numCols << " " 
	<< minVal << " " << maxVal << endl << endl;
	for(int i = 0; i < numRows; ++i ) {
		for(int j = 0; j < numCols; ++j) {
			readFile >> pixelValue;
			if(pixelValue == 0)
				printToFile << "  ";
			else 
				printToFile << pixelValue << "  ";
		}
		printToFile << endl;
	}
	readFile.close();
	printToFile.close();
}

void DistTransform::printArr() {
	for(int i = 1; i <= numRows + 1; ++i) {
		for(int j = 1; j <= numCols + 1; ++j) {
			cout << zeroFramedAry[i][j] << " ";
		}
		cout << endl;
	}
}


int main(int argc, char* argv[]) {

	if(argc != 6) {
		cout << "Program needs 5 files: \n" 
		<< " 1 input file \n" 
		<< " 1 output file for result of zeroFramedAry after "
		<< "pass 2 \n" 
		<< " 1 output file for result of the skeletonAry \n" 
		<< " 1 output file for pretty print pass 1, pass 2 " 
		<< "and skeleton \n"
		<<" 1 output File for pretty print input file\n" 
		<< " Terminating ...." << endl;
		return 0;
	}

	ofstream printToFile;
	ofstream prettyPrintInput;

	string inputFile = argv[1];
	string outputFile2 = argv[2];
	string outputFile3 = argv[3];
	string outputFile4 = argv[4];
	string outputFile5 = argv[5];
	printToFile.open(outputFile4);
	
	DistTransform distTransform(inputFile);
	distTransform.prettyPrint(inputFile, outputFile5);
	distTransform.zeroFramed();
	distTransform.loadImage(inputFile);
	distTransform.prettyPrintDistance(prettyPrintInput, 0);
	distTransform.firstPassDistance();

	distTransform.prettyPrintDistance(printToFile, 1);
	distTransform.secondPassDistance();

	distTransform.prettyPrintDistance(printToFile, 2);
	distTransform.distTransfrmImg(outputFile2);
	distTransform.computeSkeleton();
	distTransform.printSkeletonImg(outputFile3);
	distTransform.prettyPrintDistanceForSkelArr(printToFile);
	printToFile.close();
	
	return 0;
}















