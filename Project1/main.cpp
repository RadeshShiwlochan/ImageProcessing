#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class PrettyPrint {

private: 
	int numRows;
	int numCols;
	int minValue;
	int maxValue;

public: 
	PrettyPrint(string theInputFile);
	void prettyPrint(string input);	

};

PrettyPrint::PrettyPrint(string theInputFile) {
	prettyPrint(theInputFile);
}//constructor

void PrettyPrint::prettyPrint(string input) {

	ifstream readInputFile;
	ofstream readOutputFile;
	int numsInFile, pixel_value;

	size_t positionOfExt = input.find(".txt");
	string inputFileName = input.substr(0,positionOfExt);
	string outputFile = inputFileName + "_PP.txt";
	
	readInputFile.open(input);
	readOutputFile.open(outputFile);

	//read in header
	readInputFile >> numRows >> numCols >> minValue >> maxValue;

	while(readInputFile >> numsInFile) {
		
		readOutputFile << numsInFile << " ";
	}
	readOutputFile.close();
	readOutputFile.close();
}//prettyPrint method

int main(int argc, char *argv[]) {

	if(argc != 2) {
		cout << "Needs an input file as an Argument, Terminating!!";
		return 0;	
	}

	string inputFile = argv[1];

    PrettyPrint ppObj(inputFile);
    return 0;
}

