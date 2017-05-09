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
	Image(int, int, int, int);
	~Image();
	int getNumRows();
	int getNumCols();
	int getMinVal();
	int getMaxVal();
	int getIndexVal(int,int);
	void setIndexVal(int, int, int);
	void loadPtImage();
	void prettyPrint(ofstream&);	
};

Image::Image(int rows, int cols, int minValue, int maxValue) {
	numRows = rows;
	numCols = cols;
	minVal = minValue;
	maxVal = maxValue;
	imageAry = new int*[numRows];
	for(int i = 0; i < numRows; ++i)
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

void Image::prettyPrint(ofstream& printer) {

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
	//BoundaryPt(int, int, int, double, int);
	int getX();
	int getY();
	int getMaxVotes();
	double getMaxDistance();
	int getCorner();
	void printBoundaryPt();
};

// BoundaryPt::BoundaryPt(int xVal, int yVal, int maxVotesVal, 
// 	double maxDistanceVal, int cornerVal)                  {
// 	x = xVal;
// 	y = yVal;
// 	maxVotes = maxVotesVal;
// 	maxDistance = maxDistanceVal;
// 	corner = cornerVal;
// }

int BoundaryPt::getX() { return x; }

int BoundaryPt::getY() { return y; }

int BoundaryPt::getMaxVotes() { return maxVotes ;}

double BoundaryPt::getMaxDistance() { return maxDistance; }

int BoundaryPt:: getCorner() { return corner; }

void BoundaryPt::printBoundaryPt() {
	cout << "x: " << x << "\n" << "y: " << y << "\n" << "maxVotes: "
	<< maxVotes << "\n" << "maxDistance: " << maxDistance << "\n" 
	<< "corner: " << corner << endl;
}

class ArcChordDistance {
private:
	int kChordLength;
	int numPts;
	double* chordAry;
	BoundaryPt* boundaryPtArr;
	int P1;
	int P2;

public:
	ArcChordDistance(int, int);
	~ArcChordDistance();
	void loadData();
	double computeDistance();
	int findMaxDist();
	int computeLocalMaxima();
	int isCorner(); 	
};

ArcChordDistance::ArcChordDistance(int amntOfPts, int userInputKChrdLen) {
	kChordLength = userInputKChrdLen;
	numPts = amntOfPts;
	chordAry = new double[userInputKChrdLen];
	boundaryPtArr = new BoundaryPt[amntOfPts];
	for(int i = 0; i < numPts; ++i)
		chordAry[i] = 0.0;
	P1 = 0;
	P2 = 0;
}

ArcChordDistance::~ArcChordDistance() {
	delete [] chordAry;
}

void ArcChordDistance::loadData() {

}

double ArcChordDistance::computeDistance() {
	return 0.0;
}

int ArcChordDistance::findMaxDist() {
	return 0;
}

int ArcChordDistance::computeLocalMaxima() {
	return 0;
}

int ArcChordDistance::isCorner() { 
	return 0;
}


int main(int argc, char* argv[]) {
	// if(argc != 4) {
	// 	cout << "Program needs 5 files:\n"
	// 	     << "One inputFile and 4 output " 
	// 	     << "files, Terminating!!" << endl;
	// 	    return 0;
	// }
	string inputFile = argv[1];
	// string outputFile1 = argv[2];
	// string outputFile2 = argv[3];
	// string outputFile3 = argv[4];
	int userInputKChrdLen = 0;
	cout << "Please Enter a positive number for " <<
	"kChordLength: " << endl;
	//cin >> userInputKChrdLen;
	userInputKChrdLen = 4;
	if(userInputKChrdLen < 0)
		return 0;

	ifstream readFile;
	readFile.open(inputFile);
	int rows = 0;
	int cols = 0;
	int minValue = 0;
	int maxValue = 0;
	int label = 0;
	int amntOfPts = 0;
	readFile >> rows >> cols >> minValue >> maxValue >>
	label >> amntOfPts;
	Image image(rows, cols, minValue, maxValue);
	ArcChordDistance arcChordDist(amntOfPts, userInputKChrdLen);
	return 0;
}



















