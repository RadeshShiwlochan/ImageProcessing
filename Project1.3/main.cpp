#include<iostream>
#include<fstream>

using namespace std;

class Thresholding {
	private:
		int numRows;
		int numCols;
		int minVal;
		int maxVal;

	public: 
		Thresholding(string inputFile);	
		int* setFields(string inputFile);
		void getNumsFromInFile(ifstream inputFileReader);
};

int* Thresholding::setFields (string inputFile) {
	ifstream readInputFile;
	int static headerArr[4];
	readInputFile.open(inputFile);
	readInputFile >> headerArr[0];
	readInputFile >> headerArr[1];
	readInputFile >> headerArr[2];
	readInputFile >> headerArr[3];

	return headerArr;
}

void Thresholding::getNumsFromInFile(ifstream inputFileReader) {
	int num;
	int** thr_Array = new int[numRows][numCols]();
	for(int i = 0; i < numRows; i++) {
		for(int j = 0; j < numCols; j++) {
			inputFileReader >> num; 
			thr_Array[i][j] = num;
		}	
	}
}

Thresholding::Thresholding(string inputFile) {
	//int arrFields[4];
	int* arrFields = setFields(inputFile); 
	numRows = * (arrFields + 0);
	numCols = * (arrFields + 1);
	minVal  = * (arrFields + 2);
	maxVal  = * (arrFields + 3);

	cout << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;  
}

int main(int argc, char* argv[] ) {

	//check if 3 files were provided to program
	if(argc != 2) {
		cout << "Program needs 3 arguments" <<endl;
		return 0;
	}

	string inputFile = argv[1];
	Thresholding thresholding(inputFile);

}