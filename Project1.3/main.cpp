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
		Thresholding(string[]);	
		void computeThreshold(int** , string[]);
		void printImage(int**); 
		bool errorCheckThresholdVal(int);
		int getInput();
};

Thresholding::Thresholding(string inputFile[]) {
	int numberFromFile;
	ifstream readFile;
	readFile.open(inputFile[0]);

	readFile >> numRows >> numCols >> minVal >> maxVal;
	
	int** thr_Array = new int*[numRows];

	for(int i = 0; i < numRows; i++)
		thr_Array[i] = new int[numCols]();

	//readFile.close();
	computeThreshold(thr_Array, inputFile);
	printImage(thr_Array);
		
}

void Thresholding::computeThreshold(int** theArray, string inputFile[]) {
     
    //maybe initialize this to a different value; 
	int thr_value = getInput();
	// cout << "Please Enter a Threshold Value " << endl;
	// cin >> thr_value;
	// if(!errorCheckThresholdVal(thr_value)) return;
    
	ifstream readFile;
	ofstream printBinImage, prettyPrintImg;
	readFile.open(inputFile[0]);
	printBinImage.open(inputFile[1]), prettyPrintImg.open(inputFile[2]);
	int pixel_val = -1;

	//skip the header
	for(int i = 0; i < 4; i++)
		readFile >> pixel_val;

	for(int i = 0; i < numRows; i++) {
		for(int j = 0; j < numCols; j++) {
			readFile >> pixel_val; 
			//cout << pixel_val << " ";
			if(pixel_val < thr_value)
				theArray[i][j] = 0;
			else
				theArray[i][j] = 1;
			printBinImage << theArray[i][j] << " ";
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
	if(!errorCheckThresholdVal(inputValue)) 
		return -1;
	else
		return inputValue;
}

int main(int argc, char* argv[]) {

	//check if 3 files were provided to program
	if(argc != 3) {
		cout << "Program needs 3 arguments" <<endl;
		return 0;
	}

	string filesInputted[3];
	filesInputted[0] = argv[1];
	filesInputted[1] = argv[2];
	//filesInputted[2] = argv[3];

	Thresholding thresholding(filesInputted);
	return 0;

}