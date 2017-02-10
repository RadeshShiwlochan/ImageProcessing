#include<iostream>
#include<fstream>
using namespace std;

class MedianFilter {
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

public:
	MedianFilter(string, string);
	void readInputFile(string);

};

	MedianFilter::MedianFilter(string inputFile, string outputFile) {
		readInputFile(inputFile);
	}

void MedianFilter::readInputFile(string inputFile) {
	ifstream readInputFile;
	readInputFile.open(inputFile);
	int numReadIn = 0;
	while(readInputFile >> numReadIn) {
		cout << numReadIn << " ";
	}
} 

int main(int argc, char* argv[]) {
	string inputFile = argv[1];
	string outputFile = argv[2];
	MedianFilter medianFilter(inputFile, outputFile);
}