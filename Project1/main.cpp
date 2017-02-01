#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void prettyPrint(string inputFile) {

	ifstream readInputFile;
	ofstream readOutputFile;
	int numRows, numCols, minValue, maxValue,
	    numInFile, pixel_value;

	//set the name of output file 
	size_t positionOfExt = inputFile.find(".txt");
	string inputFileName = inputFile.substr(0, positionOfExt);
	string outputFile = inputFileName + "_PP.txt";
	
	readInputFile.open(inputFile);
	readOutputFile.open(outputFile);

	//read in header
	readInputFile >> numRows >> numCols >> minValue >> maxValue;

	//read in the input file
	for(int i = 0; i < numRows; i++) {
		for(int j = 0; j < numCols; j++) {
			readInputFile >> numInFile;
			if(numInFile == 0)
				readOutputFile << " ";
			else 
				readOutputFile << numInFile << " ";
		}
	}		
	//close the files
	readOutputFile.close();
	readOutputFile.close();
}//prettyPrint method

int main(int argc, char *argv[]) {

	//Error check to ensure an argument is provided
	if(argc != 2) {
		cout << "Needs an input file as an Argument, Terminating!!";
		return 0;	
	}

	string inputFile = argv[1];
    prettyPrint(inputFile);
    return 0;
}

