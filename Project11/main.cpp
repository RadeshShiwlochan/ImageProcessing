#include <iostream>
#include <fstream>

using namespace std;

class Image {
private:
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int** imageAry;

public:
	Image(string);
	~Image();
	int getNumRows();
	int getNumCols();
	int getMinVal();
	int getMaxVal();
	int getIndexVal(int,int);
	void setIndexVal(int, int, int);
	void loadPtImage();
	void prettyPrint(oftream&);	
};

Image::Image(string inputFile) {
	ifstream readFile;
	readFile.open(inputFile);
	readFile >> numRows >> numCols >> minVal >>
			 >> maxVal;
	imageAry = new int*[numRows];
	for(int i = 0; i < numCols; ++i)
		imageAry[i] = new int[numCols]();
}

Image::~Image() {
	for(int i = 0; i < numRows; ++i)
		delete [] imageAry[i];
	delete [] imageAry;
}

int Image::getNumRows() { return numRows; }

int Image::getNumCols() { return numCols; }

int Image::getMinVal() { return minVal;   }

int Image::getMaxVal() { return maxVal;   }

int Image::getIndexVal(int row, int col) { 
	return imageAry[row][col]; 
}

void Image::setIndexVal(int row, int col, int val) {
	imageAry[row][col] = val;
}

void Image::loadPtImage() {

}

void Image::prettyPrint(printer& ofstream) {

	printer << line << " cycleCount " << cycleCount <<  endl << endl;
	for(int row = 0; row < numRows; ++row) {
		for(int col = 0; col < numCols; ++col) {
			if(imageAry[row][col] > 0 ) 
				printer << imageAry[row][col] << " ";
			else 
				printer<< "  ";
		}
		printer << endl;
	}
	printer << endl << endl;
}

class BoundaryPt {
private:
	int x;
	int y;
	int maxVotes;
	double maxDistance;
	int corner;

public:
	BoundaryPt(int, int, int, double, int);
	int getX();
	int getY();
	int getMaxVotes();
	double getMaxDistance();
	int getCorner();
	void printBoundaryPt();
};


























