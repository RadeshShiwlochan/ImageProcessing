#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void PrettyPrint(string input) {

	ifstream readInputFile;
	ofstream readOutputFile;
	int rows, columns, minValue, maxValue, numsInFile, pixel_val;
	int count = 0;
	size_t posOfExt = input.find(".txt");
	string inputFileName = input.substr(0,posOfExt);
	string outputFile = inputFileName + "_PP.txt";
	
	readInputFile.open(input);
	readOutputFile.open(outputFile);

	while(readInputFile >> numsInFile) {
		if(count == 0) {
			rows = numsInFile;
			count++;
		} else if(count == 1) {
			columns = numsInFile;
			count++;
		} else if(count == 2) {
			minValue = numsInFile;
			count++;
		} else if(count == 3) {
			maxValue = numsInFile;
			count++;
		} else 
		   readOutputFile << numsInFile << " ";
	}
}

int main(int argc, char *argv[]) {

	if(argc != 2) {
		cout << "Needs an input file as an Argument, Terminating!!";
		return 0;	
	}

    string inputFile = argv[1];
    PrettyPrint(inputFile);
    return 0;
}

