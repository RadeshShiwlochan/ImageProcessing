//Radesh Shiwlochan

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void prettyPrint(string inputFile, string outFile) {

	ifstream readInputFile;
	ofstream readOutputFile;
	int numRows, numCols, minValue, maxValue,
	    pixel_value;

	//set the name of output file 
	size_t positionOfExt = inputFile.find(".txt");
	string inputFileName = inputFile.substr(0, positionOfExt);
	string outputFile = inputFileName + "_PP.txt";
	
	readInputFile.open(inputFile);
	readOutputFile.open(outFile);

	//read in header
	readInputFile >> numRows >> numCols >> minValue >> maxValue;

	readOutputFile << numRows << "  " << numCols << "  " <<
	minValue << "  " << maxValue << endl << endl;

	//read in the input file
	for(int i = 0; i < numRows; i++) {
		for(int j = 0; j < numCols; j++) {
			readInputFile >> pixel_value;
			if(pixel_value > 0 && pixel_value < 9) 
				readOutputFile << pixel_value << "  ";
			else if(pixel_value > 9)
				readOutputFile << pixel_value << " ";
			else
				readOutputFile << "  ";
		}
		readOutputFile << endl;
	}		
	//close the files
	readOutputFile.close();
	readOutputFile.close();
}//prettyPrint method

int main(int argc, char *argv[]) {

	//Error check to ensure an argument is provided
	if(argc != 3) {
		cout << "Needs an input file as an Argument, Terminating!!";
		return 0;	
	}

	string inputFile = argv[1];
	string outputFile = argv[2];
    prettyPrint(inputFile,outputFile);
    return 0;
}

