#include<iostream>
#include<fstream>
using namespace std;

class CorPerFilter {
private:
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int newMin;
	int newMax;
	int** mirrorFramedAry;
	int** tempAry;
	int neighborAry[9];
	double neighborAVG[9];

public:
	CorPerFilter(string, string);
	void readInputFile(string);
	void initializeArr();
	void mirrorFramed();
	void loadImage(string);
	void loadNeighbors();
	void computeAVG();
	void minAVG();
	void findNewMinMax();
	void outputImage();
	void printArr(string);

};

	CorPerFilter::CorPerFilter(string inputFile, string outputFile) {
		ifstream getHeader;
		getHeader.open(inputFile);
		getHeader >> numRows >> numCols >> minVal >> maxVal;
		int rowSize = numRows + 4;
		int colSize = numCols + 4;
		mirrorFramedAry = new int*[rowSize];
		tempAry = new int*[colSize];
		
		//allocate and initalize arrays
		for(int i = 0; i < rowSize; i++) {
			mirrorFramedAry[i] = new int[colSize]();
			tempAry[i] = new int[colSize]();
		}		
	}

void CorPerFilter::readInputFile(string inputFile) {
	ifstream readInputFile;
	readInputFile.open(inputFile);
	int numReadIn = 0;
	while(readInputFile >> numReadIn) {
		cout << numReadIn << " ";
	}
} 

void CorPerFilter::initializeArr() {
	int rowSize = numRows + 4;
	int colSize = numCols + 4;
	for(int i = 0; i < rowSize; i++) {
			mirrorFramedAry[i] = new int[colSize]();
			tempAry[i] = new int[colSize]();
	}	
}

void CorPerFilter::mirrorFramed() {
	//framing left to right
	for(int i = 0; i <= numRows + 1; i++) {
		mirrorFramedAry[i][0]           = mirrorFramedAry[i][1];
		mirrorFramedAry[i][numCols + 1] = mirrorFramedAry[i][numCols];
	}
	//framing top to bottom
	for(int j = 0; j <= numCols + 1; j++) {
		mirrorFramedAry[0][j]           = mirrorFramedAry[1][j];
		mirrorFramedAry[numRows + 1][j] = mirrorFramedAry[numRows][j];
	}
}

void CorPerFilter::loadImage(string inputFile) {

	// fix number of rows here
 
	ifstream readInputFile;
	readInputFile.open(inputFile);
	int numFromFile;

	//skip the header
	for(int i = 0; i < 4; i++)
		readInputFile >> numFromFile;
	
	for(int i = 1; i < numRows+ 1; i++) {
		for(int j = 1; j < numCols + 1; j++) {
			readInputFile >> numFromFile;
			mirrorFramedAry[i][j] = numFromFile;
		}
	}
}

void CorPerFilter::loadNeighbors() {

}

void CorPerFilter::computeAVG() {

}

void CorPerFilter::minAVG() {

}

void CorPerFilter::findNewMinMax() {

}

void CorPerFilter::outputImage() {

	//fix number of rows here

	for(int i = 0; i <= numRows + 4; i++ ) {
		for(int j = 0; j <= numCols + 4; j++)
			cout << mirrorFramedAry[i][j] << " ";
		cout << endl;
	}
}

void CorPerFilter::printArr(string outputFile) {
	ofstream printToFile;
	printToFile.open(outputFile);

	for(int i = 0; i < numRows + 4; i++ ) {
		for(int j = 0; j < numCols + 4; j++)
			printToFile << mirrorFramedAry[i][j] << " ";
		printToFile << endl;
	}

}

int main(int argc, char* argv[]) {

	if(argc != 3) {
		cout << "Program needs an input and output file";
		return 0;
	}
	string inputFile = argv[1];
	string outputFile = argv[2];
	CorPerFilter corPerFilter(inputFile, outputFile);
	corPerFilter.loadImage(inputFile);
	corPerFilter.mirrorFramed();
	corPerFilter.printArr(outputFile);

	return 0;
}