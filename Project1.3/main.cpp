#include<iostream>
#include<fstream>

using namespace std;

class Thresholding {
	private:
		int numRows;
		int numCols;
		int minVal;
		int maxVal;
		int** thr_Array;

	public: 
		Thresholding(string);	
		void computeThreshold(string);
		void printImage(int**); 
		bool errorCheckThresholdVal(int);
		int getInput();
};

Thresholding::Thresholding(string inputFile) {
	int numberFromFile;
	ifstream readFile;
	readFile.open(inputFile);

	readFile >> numRows >> numCols >> minVal >> maxVal;
	
	thr_Array = new int*[numRows];

	for(int i = 0; i < numRows; i++)
		thr_Array[i] = new int[numCols]();

	//readFile.close();
	//computeThreshold(thr_Array, inputFile);
	//printImage(thr_Array);
		
}

void Thresholding::computeThreshold(string inputFile) {
     
	int thr_value = getInput();
    
	ifstream readFile;
	ofstream printBinImage, prettyPrintImg;
	readFile.open(inputFile);
	//printBinImage.open(inputFile[1]), prettyPrintImg.open(inputFile[2]);
	int pixel_val = -1;

	//skip the header
	for(int i = 0; i < 4; i++)
		readFile >> pixel_val;

	for(int i = 0; i < numRows; i++) {
		for(int j = 0; j < numCols; j++) {
			readFile >> pixel_val; 
			//cout << pixel_val << " ";
			if(pixel_val < thr_value)
				thr_Array[i][j] = 0;
			else
				thr_Array[i][j] = 1;
			cout << thr_Array[i][j] << " ";
		}
		printBinImage << endl;	
	}	
}

bool Thresholding::errorCheckThresholdVal(int inputThreshold) {
	if(inputThreshold < 0) {
		cout << "Threshold value given not suitable, Terminating!" << endl;
		return true;
	}
	return false;
}

void Thresholding::printImage(int** arr) {
	for(int i = 0; i < numRows; i++) {
		for(int j = 0; j < numCols; j++)
			cout << arr[i][j] << " ";
	}
	cout << endl;
}

int Thresholding::getInput() {
	int inputValue = 0;
	cout << "Please Enter a Threshold Value " << endl;
	cin >> inputValue;

	//check for a better way to end a program
	//if(!errorCheckThresholdVal(inputValue)) 
	//	return -1;
	//else
		return inputValue;
}

int main(int argc, char* argv[]) {

	//check if 3 files were provided to program
	if(argc != 2) {
		cout << "Program needs 3 arguments" <<endl;
		return 0;
	}

	string inputFile = argv[1];
	//string outputFile1 = argv[2];
	//filesInputted[2] = argv[3];

	Thresholding thresholding(inputFile);
	thresholding.computeThreshold(inputFile);
	return 0;

}