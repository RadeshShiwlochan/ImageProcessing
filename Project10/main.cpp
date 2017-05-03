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
	void doExpansion(int,int,int);
	void executeExpanAlg(string, string);
	void northExpansion();
	void southExpansion();
	void westExpansion();
	void eastExpansion();
	void prettyPrint(ofstream&, int**, string);
	void printFinalImg(ofstream&);	
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
	secondAry = new int*[numRows + 2];
	for(int i = 0; i < numRows + 2; ++i) {
		firstAry[i] = new int[numCols + 2]();
		secondAry[i] = new int[numCols + 2]();
	}
	readFile1.close();
	readFile2.close();
	changeFlag = true;
}

Expansion::~Expansion() {

	// for(int i = 0; i < numRows + 2; ++i) {
	// 	delete [] objectAry[i];
	// 	delete [] firstAry[i];
	// 	delete [] secondAry[i];
	// }
	// delete [] objectAry;
	// delete [] firstAry;
	// delete [] secondAry;
}

void Expansion::zeroFramed() {

	for(int i = 0; i < numRows + 2; i++) {
		objectAry[i][0]           = 0;
		objectAry[i][numCols + 1] = 0;
		firstAry[i][0]            = 0;
		firstAry[i][numCols + 1]  = 0;
		secondAry[i][0]           = 0;
		secondAry[i][numCols + 1] = 0;
	}

	for(int j = 0; j < numCols + 2; j++) {
		 objectAry[0][j]           = 0;
		 objectAry[numRows + 1][j] = 0;
		 firstAry[0][j]            = 0;
		 firstAry[numRows + 1][j]     = 0;
		 secondAry[0][j]           = 0;
		 secondAry[numRows + 1][j]    = 0;
	}
}

void Expansion::loadImage(string inputFile1, string inputFile2) {

	ifstream readFile1;
	ifstream readFile2;
	readFile1.open(inputFile1);
	readFile2.open(inputFile2);
	int numFromFile = -9999;
	//skip the header
	readFile1 >> numRows >> numCols >> minVal >> maxVal;
	for(int i = 1; i < numRows + 2; ++i) {
		for(int j = 1; j < numCols + 2; ++j) {
			readFile1 >> numFromFile;
			objectAry[i][j] = numFromFile;
	    }
	}
	readFile1.close();
	int data = -9999;
	readFile2 >> numRows >> numCols >> minVal >> maxVal;
	for(int i = 1; i < numRows + 2; ++i) {
		for(int j = 1; j < numCols + 2; ++j) {
			readFile2 >> data;
			firstAry[i][j]  = data;
			secondAry[i][j] = data;
			cout << data << " ";
		}
		cout << endl;
	}
	
	readFile2.close();
}

void Expansion::copyAry() {

	for(int i = 0; i < numRows + 2; ++i) {
		for(int j = 0; j < numCols + 2; ++j) {
			firstAry[i][j] = secondAry[i][j];
		}
	}
}

void Expansion::doExpansion(int row, int col, int label) {

	if(objectAry[row][col] > 0) {
		secondAry[row][col] = label;
		changeFlag = true;
	}
}

void Expansion::executeExpanAlg(string outputFile1, string outputFile2) {

	ofstream printer1;
	ofstream printer2;
	printer1.open(outputFile1);
	printer2.open(outputFile2);
	cycleCount = 0;
	string line = "This is objectAry:";
	prettyPrint(printer1, objectAry, line);
	while(changeFlag) {
		string line2 = "This is firstAry:";
		if(cycleCount == 0 || cycleCount == 3 || cycleCount == 5) {
			prettyPrint(printer1, firstAry, line2);
			if(cycleCount == 5)
				cycleCount = 0;
		}
		changeFlag = false;
		cycleCount++;
		northExpansion();
		southExpansion();
		westExpansion();
		eastExpansion();
	}
	string finalOutputLine = "firstAry, final output:";
	prettyPrint(printer1, firstAry, finalOutputLine);
	printFinalImg(printer2);
	printer1.close();
	printer2.close();
}

void Expansion::northExpansion() {

	for(int i = 1; i < numRows + 2; ++i) {
		for(int j = 1; j < numCols + 2; ++j) {
			if(firstAry[i][j] > 0 && firstAry[i - 1][j] == 0)
				doExpansion(i - 1, j, firstAry[i][j]);
		}
	}
	copyAry();
}

void Expansion::southExpansion() {

	for(int i = 1; i < numRows + 2; ++i) {
		for(int j = 1; j < numCols + 2; ++j) {
			if(firstAry[i][j] > 0 && firstAry[i + 1][j] == 0)
				doExpansion(i + 1, j, firstAry[i][j]);
		}
	}
	copyAry();
}

void Expansion::westExpansion() {

	for(int i = 1; i < numRows + 2; ++i) {
		for(int j = 1; j < numCols + 2; ++j) {
			if(firstAry[i][j] > 0 && firstAry[i][j - 1] == 0)
				doExpansion(i, j - 1, firstAry[i][j]);
		}
	}
	copyAry();
}

void Expansion::eastExpansion() {

	for(int i = 1; i < numRows + 2; ++i) {
		for(int j = 1; j < numCols + 2; ++j) {
			if(firstAry[i][j] > 0 && firstAry[i][j + 1] == 0)
				doExpansion(i, j + 1, firstAry[i][j]);
		}
	}
	copyAry();
}

void Expansion::prettyPrint(ofstream& printer, int** arr, string line) {

	printer << line << endl << endl;
	for(int row = 1; row < numRows + 1; ++row) {
		for(int col = 1; col < numCols + 1; ++col) {
			if(arr[row][col] > 0 ) 
				printer << arr[row][col] << " ";
			else 
				printer<< "  ";
		}
		printer << endl;
	}
	printer << endl << endl;
}

void Expansion::printFinalImg(ofstream& printer2) {

	printer2 << numRows << " " << numCols << " " << minVal <<
	         " " << maxVal << endl;
	for(int i = 1; i < numRows + 2; ++i) {
		for(int j = 1; j < numCols + 2; ++j) {
			printer2 << firstAry[i][j] << " ";
		}
		printer2 << endl;
	}         
}

int main(int argc, char* argv[]) {

	if(argc != 5) {
		cout << "Program needs 4 files:\n" <<
		"Two input files and two outputfiles" << 
		" , Terminating!" << endl;
		return 0;
	}
	string inputFile1  = argv[1];
	string inputFile2  = argv[2];
	string outputFile1 = argv[3];
	string outputFile2 = argv[4];
	Expansion expansion(argv[1], argv[2]);
	expansion.zeroFramed();
	expansion.loadImage(inputFile1, inputFile2);
	expansion.executeExpanAlg(outputFile1, outputFile2);

}