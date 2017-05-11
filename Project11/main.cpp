#include <iostream>
#include <fstream>
#include <cmath>

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
	void setXY(int, int);
	int getMaxVotes();
	double getMaxDistance();
	int getCorner();
	void setVotes(int);
	void setMaxDist(double);
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

void BoundaryPt::setXY(int xVal, int yVal) {
	x = xVal;
	y = yVal;
 }

int BoundaryPt::getMaxVotes() { return maxVotes ;}

double BoundaryPt::getMaxDistance() { return maxDistance; }

int BoundaryPt:: getCorner() { return corner; }

void BoundaryPt::setVotes(int val) {
	maxVotes = val;
}

void BoundaryPt::setMaxDist(double newMaxDist) {
	maxDistance = newMaxDist;
}

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
	int currPt;

public:
	ArcChordDistance(int, int);
	~ArcChordDistance();
	void loadData(ifstream&);
	double computeDistance(int, int, int);
	int findMaxDist();
	int computeLocalMaxima();
	int isCorner();
	void printChordArrToDebugFile(ofstream&);
	void printBoundArrToDebugFile(ofstream&); 
	void printP1toP2(ofstream&, int, int);	
	void executeArcChordDistance(ofstream&, string);
	//temp functions
	void printArr(string);
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

void ArcChordDistance::loadData(ifstream& readFile) {
	int rowValue = 0;
	int colValue = 0;
	double dist = 0.0;
	int index = 0;
	while(index < numPts) {
		readFile >> rowValue >> colValue;
		boundaryPtArr[index++].setXY(rowValue, colValue); 
	}
}

double ArcChordDistance::computeDistance(int pt1, int pt2, int currentPt) {
	double d = 0.0;
	BoundaryPt point1 = boundaryPtArr[pt1];
	BoundaryPt point2 = boundaryPtArr[pt2];
	BoundaryPt currPoint = boundaryPtArr[currentPt];
	int A = point2.getY() - point1.getY();
	int B = point1.getX() - point2.getX();
	int C = (point2.getX() * point1.getY()) - (point1.getX() * point2.getY());
	int currPtX = currPoint.getX();
	int currPtY = currPoint.getY();
	d = abs((A * currPtX) + (B * currPtY) + C) / (sqrt(pow(A, 2) + pow(B, 2)));
	return d;
}

int ArcChordDistance::findMaxDist() {
	int maxIndex = 0;
	double maxValue = chordAry[0];
	for(int i = 0; i < kChordLength; ++i) {
		if(maxValue < chordAry[i]) {
			maxValue = chordAry[i];
			maxIndex = i; 
		}//if
	}//for 
	return maxIndex;
}

int ArcChordDistance::computeLocalMaxima() {

	int endPt1 = numPts - 1;
	int endPt2 = numPts - 2;
	int endPt3 = numPts - 3;
	for(int i = 0; i < numPts; ++i) {
		if(i == 0 || i == 1 || i == 2 ) {
			if(boundaryPtArr[i].getMaxVotes() >= boundaryPtArr[i + 1].getMaxVotes() &&
			   boundaryPtArr[i].getMaxVotes() >= boundaryPtArr[i + 2].getMaxVotes() &&
			   boundaryPtArr[i].getMaxVotes() >= boundaryPtArr[i + 3].getMaxVotes()    ) 
				return i;
		} else if(i == endPt1 || i == endPt2 || i == endPt3) {
			if(boundaryPtArr[i].getMaxVotes() >= boundaryPtArr[i - 1].getMaxVotes() &&
			   boundaryPtArr[i].getMaxVotes() >= boundaryPtArr[i - 2].getMaxVotes() &&
			   boundaryPtArr[i].getMaxVotes() >= boundaryPtArr[i - 3].getMaxVotes()    )
				return i;
		} else {
			if(boundaryPtArr[i].getMaxVotes() >= boundaryPtArr[i + 1].getMaxVotes() &&
			   boundaryPtArr[i].getMaxVotes() >= boundaryPtArr[i + 2].getMaxVotes() &&
			   boundaryPtArr[i].getMaxVotes() >= boundaryPtArr[i + 3].getMaxVotes() &&
			   boundaryPtArr[i].getMaxVotes() >= boundaryPtArr[i - 1].getMaxVotes() &&
			   boundaryPtArr[i].getMaxVotes() >= boundaryPtArr[i - 2].getMaxVotes() &&
			   boundaryPtArr[i].getMaxVotes() >= boundaryPtArr[i - 3].getMaxVotes()    )
				return i;
		}//else
	}//for
	return -1;
}

int ArcChordDistance::isCorner() { 
	return 0;
}

void ArcChordDistance::printChordArrToDebugFile(ofstream& printToFile) {
	printToFile << endl << endl;
	for(int i = 0; i < kChordLength; ++i) {
		printToFile << chordAry[i] << endl;
	}
	printToFile << endl << endl;
}

void ArcChordDistance::printBoundArrToDebugFile(ofstream& printToFile) {
	printToFile << endl << endl;

	printToFile << endl << endl;

}

void ArcChordDistance::printP1toP2(ofstream& print, int pt1, int pt2) {
	for(int i = pt1; i <= pt2; ++i)
		print << "X : " << boundaryPtArr[i].getX() << " " 
	          << "Y : "<< boundaryPtArr[i].getY() << " " 
	          <<"maxVotes: "<< boundaryPtArr[i].getMaxVotes() << " " 
	          <<"maxDistance: "<< boundaryPtArr[i].getMaxDistance() << endl;
}

void ArcChordDistance::executeArcChordDistance(ofstream& printToFile, string outputFile) {
	ofstream outputToFile;
	outputToFile.open(outputFile);
	P1 = 0;
	P2 = kChordLength - 1; 
	int index = 0;
	int maxIndex = 0;
	int whichIndex = 0;
	double dist = 0.0;
	int maxVotesAtindx = 0;
	while( P2 != kChordLength/2) {
		index = 0;
		currPt = P1 + 1;
		while(index < kChordLength) {
			dist = computeDistance(P1, P2, currPt);
			chordAry[index++] = dist;
			currPt++;
		}
		printChordArrToDebugFile(printToFile);
		maxIndex = findMaxDist();
		whichIndex = P1 + maxIndex;
		maxVotesAtindx = boundaryPtArr[whichIndex].getMaxVotes();
		boundaryPtArr[whichIndex].setVotes(maxVotesAtindx+1);
		boundaryPtArr[whichIndex].setMaxDist(dist);
		printP1toP2(outputToFile, P1, P2);
		P1 = (P1 + 1) % numPts;
		P2 = (P2 + 1) % numPts;
	}//while
	printBoundArrToDebugFile(printToFile);
}

void ArcChordDistance::printArr(string outputFile) {
	ofstream printToFile;
	printToFile.open(outputFile);
	printToFile << "BoundaryPtArr beginning\n" << "=============\n";
	for(int i = 0; i < numPts; ++i) {
		printToFile << boundaryPtArr[i].getX() << " " << boundaryPtArr[i].getY() << endl;
	}
	printToFile << "BoundaryPtArr ending\n" << "=============\n\n\n";
	printToFile << "chordAry beginning\n" << "=============\n";
	for(int i = 0; i < kChordLength; ++i) {
		printToFile << chordAry[i] << endl;
	}
	printToFile << "chordAry ending" << "=============\n\n\n";
}

int main(int argc, char* argv[]) {
	// if(argc != 4) {
	// 	cout << "Program needs 5 files:\n"
	// 	     << "One inputFile and 4 output " 
	// 	     << "files, Terminating!!" << endl;
	// 	    return 0;
	// }
	string inputFile = argv[1];
	string outputFile1 = argv[2];
	string outputFile2 = argv[3];
	string outputFile3 = argv[4];
	int userInputKChrdLen = 0;
	cout << "Please Enter a positive number for " <<
	"kChordLength: " << endl;
	//cin >> userInputKChrdLen;
	userInputKChrdLen = 11;
	if(userInputKChrdLen < 0)
		return 0;

	ifstream readFile;
	readFile.open(inputFile);
	ofstream debugFile;
	debugFile.open(outputFile2);
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
	arcChordDist.loadData(readFile);
	arcChordDist.printArr(outputFile1);
	arcChordDist.executeArcChordDistance(debugFile, outputFile3);
	return 0;
}



















