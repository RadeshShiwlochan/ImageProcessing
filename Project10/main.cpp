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
	void zeroFramed();
	void loadImage();
	void copyAry();
	void doExpansion();
	void northExpansion();
	void southExpansion();
	void westExpansion();
	void eastExpansion();
	void prettyPrint();	

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