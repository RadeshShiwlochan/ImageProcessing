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
		void computeThreshold(string, string);
		void printImage(int**); 
		int getInput();
		void prettyPrint(string);
};

Thresholding::Thresholding(string inputFile) {
	int numberFromFile;
	ifstream readFile;
	readFile.open(inputFile);

	readFile >> numRows >> numCols >> minVal >> maxVal;
	
	thr_Array = new int*[numRows];

	for(int i = 0; i < numRows; i++)
		thr_Array[i] = new int[numCols]();

	readFile.close();	
}

void Thresholding::computeThreshold(string inputFile, string outputFile) {
     
	int thr_value = getInput();
	ifstream readFile;
	ofstream printToFile;

	readFile.open(inputFile);
	printToFile.open(outputFile);
	int pixel_val = -1;

	//skip the header
	for(int i = 0; i < 4; i++)
		readFile >> pixel_val;

	for(int i = 0; i < numRows; i++) {
		for(int j = 0; j < numCols; j++) {
			readFile >> pixel_val; 
			if(pixel_val < thr_value)
				thr_Array[i][j] = 0;
			else
				thr_Array[i][j] = 1;
			printToFile << thr_Array[i][j] << " ";
		}
		printToFile << endl;	
	}
	readFile.close();
	printToFile.close();	
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
    return inputValue;
}

void Thresholding::prettyPrint(string outputFile) {

    int pixel_value;
	ofstream readOutputFile;
	readOutputFile.open(outputFile);

	//read in the input file
	for(int i = 0; i < numRows; i++) {
		for(int j = 0; j < numCols; j++) {
			pixel_value = thr_Array[i][j];
			if(pixel_value > 0) 
				readOutputFile << pixel_value << "  ";
			else 
				readOutputFile << "  ";
		}
		readOutputFile << endl;
	}		
	readOutputFile.close();
}//prettyPrint method


int main(int argc, char* argv[]) {

	//check if 3 files were provided to program
	if(argc != 4) {
		cout << "Program needs 3 arguments" <<endl;
		return 0;
	}

	string inputFile = argv[1];
	string outputFile1 = argv[2];
	string outputFile2 = argv[3];

	Thresholding thresholding(inputFile);
	thresholding.computeThreshold(inputFile, outputFile1);
	thresholding.prettyPrint(outputFile2);
	return 0;

}