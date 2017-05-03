#include <iostream>
#include <fstream>
using namespace std;

class Expansion {
private:
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	bool changeFlag;
	int cycleCount;
	int** objectAry;
	int** firstAry;
	int** secondAry;

public:
	Expansion(string, string);
	~Expansion();
	void zeroFramed();
	void loadImage(string,string);
	void copyAry();
	void doExpansion();
	void northExpansion();
	void southExpansion();
	void westExpansion();
	void eastExpansion();
	void prettyPrint();	
	//temporary functionss
	void printImage(string, string);

};

Expansion::Expansion(string input1, string input2) {

	ifstream readFile1;
	ifstream readFile2;
	readFile1.open(input1);
	readFile2.open(input2);

	readFile1 >> numRows >> numCols >> minVal >> maxVal;
	objectAry = new int*[numRows + 2];
	for(int i = 0; i < numRows + 2; ++i) 
		objectAry[i] = new int[numCols + 2]();

	readFile2 >> numRows >> numCols >> minVal >> maxVal;
	firstAry = new int*[numRows + 2];
	secondAry = new int*[numCols + 2];
	for(int i = 0; i < numRows + 2; ++i) {
		firstAry[i] = new int[numCols + 2]();
		secondAry[i] = new int[numCols + 2]();
	}
	readFile1.close();
	readFile2.close();
}

Expansion::~Expansion() {

	for(int i = 0; i < numRows + 2; ++i) {
		delete [] objectAry[i];
		delete [] firstAry[i];
		delete [] secondAry[i];
	}
	delete [] objectAry;
	delete [] firstAry;
	delete [] secondAry;
}

void Expansion::zeroFramed() {
	for(int i = 0; i <= numRows +1; i++) {
		objectAry[i][0]           = 0;
		objectAry[i][numCols + 1] = 0;
		firstAry[i][0]            = 0;
		firstAry[i][numCols + 1]  = 0;
		secondAry[i][0]           = 0;
		secondAry[i][numCols + 1] = 0;
	}

	for(int j = 0; j <= numCols + 1; j++) {
		 objectAry[0][j]           = 0;
		 objectAry[numRows + 1][j] = 0;
		 firstAry[0][j]            = 0;
		 firstAry[numRows + 1]     = 0;
		 secondAry[0][j]           = 0;
		 secondAry[numRows + 1]    = 0;
	}
}

void Expansion::loadImage(string inputFile1, string inputFile2) {

	ifstream readFile1;
	ifstream readFile2;
	readFile1.open(input1);
	readFile2.open(input2);
	int numFromFile = -9999;
	//skip the header
	readFile1 >> numRows >> numCols >> minVal >> maxVal;
	for(int i = 1; i < numRows + 2; ++i) {
		for(int j = 1; j < numCols + 2; ++j) {
			readFile1 >> numFromFile;
			objectAry[i][j] = numFromFile;
	    }
	}
	readFile2 >> numRows >> numCols >> minVal >> maxVal;
	for(int i = 1; i < numRows + 2; ++i) {
		for(int j = 1; j < numCols + 2; ++j) {
			readFile2 >> numFromFile;
			firstAry[i][j] = numFromFile;
		}
	}
	readFile1.close();
	readFile2.close();
}

void Expansion::copyAry() {
	for(int i = 0; i < numRows + 2; ++i) {
		for(int j = 0; j < numCols + 2; ++j) {
			firstAry[i][j] = secondAry[i][j];
		}
	}
}

void Expansion::printImage(string output1, string output2) {
	
	ofstream printToFile1;
	ofstream printToFile2;
	printToFile1.open(output1);
	printToFile2.open(output2);
	for(int i = 0 i < numRows + 2; ++i) {
		for(int j = 0; j < numCols + 2; ++j) {
			printToFile1 << objectAry[i][j] << " ";
			printToFile2 << firstAry[i][j] << " ";
		}
		printToFile1 << endl;
		printToFile2 << endl;
	}
	printToFile1.close();
	printToFile2.close();

}

int main(int argc, char* argv[]) {

	if(argc != 5) {
		cout << "Program needs 4 files:\n" <<
		"Two input files and two outputfiles" << 
		<<" , Terminating!" << endl;
		return 0;
	}
	string inputFile1  = argv[1];
	string inputFile2  = argv[2];
	string outputFile1 = argv[3];
	string outputFile2 = argv[4];
	Expansion expansion(argv[1], argv[2]);

}