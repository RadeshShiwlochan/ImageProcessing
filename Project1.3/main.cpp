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
		void computeThreshold(int** , string);
		void printImage(int**); 
};

Thresholding::Thresholding(string inputFile) {
	int numberFromFile;
	ifstream readFile;
	readFile.open(inputFile);

	readFile >> numRows >> numCols >> minVal >> maxVal;
	
	int** thr_Array = new int*[numRows];

	for(int i = 0; i < numRows; i++)
		thr_Array[i] = new int[numCols]();

	//readFile.close();
	computeThreshold(thr_Array, inputFile);
	printImage(thr_Array);
	// for(int i = 0; i < numRows; i++) {
	// 	for(int j = 0; j < numCols; j++) {
	// 		readFile >> numberFromFile; 
	// 		cout << numberFromFile << " ";
	// 		thr_Array[i][j] = numberFromFile;
	// 	}	
	// }	
}

void Thresholding::computeThreshold(int** theArray, string inputFile) {

	ifstream readFile;
	readFile.open(inputFile);
	int pixel_val;
	for(int i = 0; i < numRows; i++) {
		for(int j = 0; j < numCols; j++) {
			readFile >> pixel_val; 
			//cout << pixel_val << " ";
			theArray[i][j] = pixel_val;
		}	
	}	
}

void Thresholding::printImage(int** arr) {
	for(int i = 0; i < numRows; i++) {
		for(int j = 0; j < numCols; j++)
			cout << arr[i][j] << " ";
	}
	cout << endl;
}

int main(int argc, char* argv[]) {

	//check if 3 files were provided to program
	if(argc != 2) {
		cout << "Program needs 3 arguments" <<endl;
		return 0;
	}

	string inputFile = argv[1];
	Thresholding thresholding(inputFile);
	return 0;

}