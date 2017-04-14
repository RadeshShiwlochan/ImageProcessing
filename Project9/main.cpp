#include<iostream>
#include<fstream>
using namespace std;

class PointsExtraction {
	private:
		int numRows;
		int numCols;
		int minVal;
		int maxVal;
		int** zeroFramedAry;

	public:
		PointsExtraction(string);
		~PointsExtraction();
		void zeroFramed();
		void loadImage(string);
		void outputImage(string);

};

PointsExtraction::PointsExtraction(string inputFile) {
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

PointsExtraction::~PointsExtraction() {
	for(int i = 0; i < numRows + 2; ++i) 
		delete [] zeroFramedAry[i];
	delete [] zeroFramedAry;
}

void PointsExtraction::zeroFramed() {
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

void PointsExtraction::loadImage(string inputFile) {
	ifstream readFile;
	int numFromFile = -9999;
	readFile.open(inputFile);
	//skip the first three numbers
	for(int i = 0; i < 4; ++i)
		readFile >> numFromFile;

	for(int i = 1; i < numRows + 2; ++i) {
		for(int j = 1; j < numRows + 2; ++j) {
			readFile >> numFromFile;
			zeroFramedAry[i][j] = numFromFile;
		}
	}
}

void PointsExtraction::outputImage(string outputFile) {
	ofstream printToFile;
	printToFile.open(outputFile);
	printToFile << numRows << " " << numCols << " "
	<< minVal << " " << maxVal << endl;

	for(int i = 1; i < numRows + 2; ++i) {
		for(int j = 1; j < numCols + 2; ++j) {
			printToFile << zeroFramedAry[i][j] << " ";
		}
		printToFile << endl;
	}
	printToFile.close();
}


int main(int argc, char* argv[]) {
	if(argc != 3) {
		cout << "Program needs 2 files!! \n" <<
		" one file as input and the next as output " <<
		"\n Terminating!!!" << endl;
		return 0;
	}
	string inputFile = argv[1];
	string outputFile = argv[2];
	PointsExtraction pointsExtraction(inputFile);
	//pointsExtraction.zeroFramed();
	pointsExtraction.loadImage(inputFile);
	pointsExtraction.outputImage(outputFile);
	return 0;
}




