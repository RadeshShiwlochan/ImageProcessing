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
};

Thresholding::Thresholding(string inputFile) {
	int numberFromFile;
	ifstream readFile;
	readFile.open(inputFile);

	readFile >> numRows >> numCols >> minVal >> maxVal;
	
	int** thr_Array = new int*[numRows];

	for(int i = 0; i < numRows; i++)
		thr_Array[i] = new int[numCols]();

	for(int i = 0; i < numRows; i++) {
		for(int j = 0; j < numCols; j++) {
			readFile >> numberFromFile; 
			cout << numberFromFile << " ";
			thr_Array[i][j] = numberFromFile;
		}	
	}	
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