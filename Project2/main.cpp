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


};

	CorPerFilter::CorPerFilter(string inputFile, string outputFile) {
		ifstream getHeader;
		getHeader.open(inputFile);
		getHeader >> numRows >> numCols >> minVal >> maxVal;
		mirrorFramedAry = new int*[numRows + 2];
		tempAry = new int*[numRows + 2];
		initializeArr();	
		readInputFile(inputFile);
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
	int rowSize = numRows + 2;
	int colSize = numCols + 2;
	for(int i = 0; i < rowSize; i++) {
			mirrorFramedAry[i] = new int[colSize]();
			tempAry[i] = new int[colSize]();
	}	
}

void CorPerFilter::mirrorFramed() {

}

void CorPerFilter::loadImage(string inputFile) {

	// fix number of rows here
	 
	ifstream readInputFile;
	readInputFile.open(inputFile);
	int numFromFile;
	for(int i = 1; i < numRows+ 2; i++) {
		for(int j = 1; j < numCols + 2; j++) {
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

	for(int i = 0; i < numRows + 2; i++ ) {
		for(int j = 0; j < numCols + 2; j++)
			cout << mirrorFramedAry[i][j] << " ";
		cout << endl;
	}
}

int main(int argc, char* argv[]) {

	if(argc != 3) {
		cout << "Program needs an input and output file";
		return 0;
	}
	string inputFile = argv[1];
	string outputFile = argv[2];
	CorPerFilter CorPerFilter(inputFile, outputFile);
}