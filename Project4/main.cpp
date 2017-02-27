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
	void prettyPrintDistance();
	void printArr();
};

DistTransform::DistTransform(string inputFile) {
	ifstream readFile;
	readFile.open(inputFile);
	readFile >> numRows >> numCols >> minVal >> maxVal;

	int rowSize = numRows + 2;
	int colSize = numCols + 2; 
	zeroFramedAry = new int*[rowSize];
	for(int i = 0; i < rowSize; ++i)
		zeroFramedAry[i] = new int[colSize]();

	readFile.close();
}

DistTransform::~DistTransform() {
	for(int i = 0; i < numRows + 2; ++i)
		delete [] zeroFramedAry[i];
	delete [] zeroFramedAry;
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

	//zero frame from left and right
	for(int i = 0; i <= numRows + 1; i++) {
			zeroFramedAry[i][0]           = zeroFramedAry[i][1];
			zeroFramedAry[i][numCols + 1] = zeroFramedAry[i][numCols];
		}
		//framing top and bottom
		for(int j = 0; j <= numCols + 1; j++) {
			 zeroFramedAry[0][j]           = zeroFramedAry[1][j];
			 zeroFramedAry[numRows + 1][j] = zeroFramedAry[numRows][j];
		}
}

void DistTransform::firstPassDistance() {

}

void DistTransform::secondPassDistance() {

}

void DistTransform::computeSkeleton() {

}

void DistTransform::mapInt2Char() {

}

void DistTransform::prettyPrintDistance() {

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
	string inputFile = argv[1];
	DistTransform distTransform(inputFile);
	distTransform.zeroFramed();
	distTransform.loadImage(inputFile);
	distTransform.printArr();
	return 0;
}















