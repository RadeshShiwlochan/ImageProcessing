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
		void loadImage(string);
		int getCountOfDataPts();
		void exePtsExtraction(string);

};

PointsExtraction::PointsExtraction(string inputFile) {
	ifstream readFile;
	readFile.open(inputFile);
	readFile >> numRows >> numCols >> minVal >> maxVal;
	
	zeroFramedAry = new int*[numRows];
	for(int i = 0; i < numRows; ++i) 
		zeroFramedAry[i] = new int[numCols]();
	readFile.close();
}

PointsExtraction::~PointsExtraction() {
	for(int i = 0; i < numRows; ++i) 
		delete [] zeroFramedAry[i];
	delete [] zeroFramedAry;
}

void PointsExtraction::loadImage(string inputFile) {
	ifstream readFile;
	int numFromFile = -9999;
	readFile.open(inputFile);
	//skip the first three numbers
	for(int i = 0; i < 4; ++i)
		readFile >> numFromFile;

	for(int i = 0; i < numRows; ++i) {
		for(int j = 0; j < numCols; ++j) {
			readFile >> numFromFile;
			zeroFramedAry[i][j] = numFromFile;
		}
	}
}

int PointsExtraction::getCountOfDataPts() {
	int count = 0;
	for(int i = 0; i < numRows; ++i) {
		for(int j = 0; j < numCols; ++j) {
			if(zeroFramedAry[i][j] > 0)
				count++;
		}//inner for
	}//outer for
	return count;
}

void PointsExtraction::exePtsExtraction(string outputFile) {
	ofstream printToFile;
	printToFile.open(outputFile);
	int numOfDataPts = getCountOfDataPts();
	printToFile << numOfDataPts << endl;
	for(int i = 0; i < numRows; ++i) {
		for(int j = 0; j < numCols; ++j) {
			if(zeroFramedAry[i][j] > 0)
				printToFile << i << " " << j << endl;
		}
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
	pointsExtraction.loadImage(inputFile);
	pointsExtraction.exePtsExtraction(outputFile);
	return 0;
}




