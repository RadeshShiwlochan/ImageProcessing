#include<iostream>
#include<fstream>
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
	void mapInt2Char();
	void prettyPrintDistance(ofstream&);
	int getMinNghbrPass1(int, int);
	int getMinNghbrPass2(int, int);
	int minimum(int, int);
	bool allNghbrsGreaterOrEq(int, int);
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
			allNghbrsEq = allNghbrsGreaterOrEq(i,j);
			if(pixelValue > 0 && allNghbrsEq )
				skeletonAry[i][j] = pixelValue;
			else
				skeletonAry[i][j] = 0;
			allNghbrsEq = false;
		}
	}

}

void DistTransform::mapInt2Char() {

}

void DistTransform::prettyPrintDistance(ofstream& printToFile) {
	for(int i = 1; i <= numRows + 1; ++i ) {
		for(int j = 1; j <= numRows + 1; ++j) {
			if(zeroFramedAry[i][j] == 0)
				printToFile << "  ";
			else //call mapInt2Char here 
				printToFile << zeroFramedAry[i][j] << "  ";
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
	int nghArr[5];
	
	nghArr[0] = zeroFramedAry[rowIndex - 1][colIndex - 1];
	nghArr[1] = zeroFramedAry[rowIndex - 1][colIndex];
	nghArr[2] = zeroFramedAry[rowIndex - 1][colIndex + 1];
	nghArr[3] = zeroFramedAry[rowIndex][colIndex - 1];
	nghArr[4] = zeroFramedAry[rowIndex][colIndex];
	
	if(nghArr[4] >= nghArr[0] && nghArr[4] >= nghArr[1] &&
	   nghArr[4] >= nghArr[2] && nghArr[4] >= nghArr[3]   )
		return true;
	return false;
}

int DistTransform::minimum(int pixelValue, int minNghbrplus1) {
	//check this again
	return pixelValue <= minNghbrplus1 ? pixelValue : minNghbrplus1;
}

void DistTransform::printArr() {

	for(int i = 0; i < numRows + 2; ++i) {
		for(int j = 0; j < numCols + 2; ++j) {
			cout << zeroFramedAry[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}


int main(int argc, char* argv[]) {

	// if(argc != 5) {
	// 	cout << "Program needs 4 files, Terminating!";
	// 	return 0;
	// }
	ofstream printToFile;

	string inputFile = argv[1];
	//this needs to be in argv[4];
	string outputFile1 = argv[2];
	printToFile.open(outputFile1);

	DistTransform distTransform(inputFile);
	distTransform.zeroFramed();
	distTransform.loadImage(inputFile);
	distTransform.firstPassDistance();
	distTransform.printArr();
	distTransform.prettyPrintDistance(printToFile);
	distTransform.secondPassDistance();
	distTransform.printArr();
	distTransform.prettyPrintDistance(printToFile);
	return 0;
}















