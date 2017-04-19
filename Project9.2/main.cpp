#include<iostream>
#include<fstream>
using namespace std;

class Point {
private:
	int xCoordinate;
	int yCoordinate;
	int clusterID;
	double distance;

public:
	Point();
	int getXCoord();
	int getYCoord();
	int getClusterID();
	double getDistance();
	void setXCoord(int);
	void setYCoord(int);
	void setClusterID(int);
	void setPointCoord(int,int);	
	void printPoint();
};


Point::Point() {
	xCoordinate = 0;
	yCoordinate = 0;
	clusterID = 1;
	distance = 0.0;
}

int Point::getXCoord() { return xCoordinate; }

int Point::getYCoord() { return yCoordinate; }

int Point::getClusterID() { return clusterID; }

double Point::getDistance() { return distance; }

void Point::setXCoord(int x) { 
	xCoordinate = x;
}

void Point::setYCoord(int y) {
	yCoordinate = y;
}

void Point::setClusterID(int ID) {
	clusterID = ID;
}

void Point::setPointCoord(int x, int y) {
	xCoordinate = x;
	yCoordinate = y;
}

void Point::printPoint() {
	cout << xCoordinate << endl << yCoordinate <<
	endl << clusterID << endl << distance << endl;
}

class xyCoord {

private:
	int xCoord;
	int yCoord;

public:
	xyCoord();
	void setXCoord(int);
	void setYCoord(int);
	void setXYCoord(int,int);
	int getXCoord();
	int getYCoord();	
	void printCoord();
};

xyCoord::xyCoord() {
	xCoord = 0;
	yCoord = 0;
}

void xyCoord::setXCoord(int x) { xCoord = x; }

void xyCoord::setYCoord(int y) { yCoord = y; }

void xyCoord::setXYCoord(int x, int y) {
	xCoord = x;
	yCoord = y;
}

int xyCoord::getXCoord() { return xCoord; }

int xyCoord::getYCoord() { return yCoord; }

void xyCoord::printCoord() {
	cout << xCoord << endl << yCoord << endl;
}

class KIsoDataClust {
private:
	int K;
	int numPts;
	Point* pointSet;
	xyCoord* centroid;
	double* xxSecMM;
	double* yySecMM;
	double* xySecMM;
	int numRows;
	int numCols;
	int** imageArr;

public:
	KIsoDataClust(string,int);
	~KIsoDataClust();
	void loadPointSet(string);
	void assignLabel();
	void mapPointToImage();
	void isoClustering();
	void printPrintSet();
	void prettyPrint(string);	
	void exeIsoDataClustering(string,string);
	//delete these
	void printFunction(string);
	void printImgArr(string);
};

KIsoDataClust::KIsoDataClust(string inputFile, int kVal) {
	ifstream readFile;
	int numOfDataPts = -9999;
	readFile.open(inputFile);
	readFile >> numOfDataPts;
	K = kVal;
	numPts = numOfDataPts;
	pointSet = new Point[numOfDataPts];
	xxSecMM = new double[K];
	yySecMM = new double[K];
	xySecMM = new double[K];
	centroid = new xyCoord[K];
	numRows = numPts;
	numCols = numPts;
	imageArr = new int*[numRows];
	for(int i = 0; i < numRows; ++i)
		imageArr[i] = new int[numCols]();
	readFile.close();
}

KIsoDataClust::~KIsoDataClust() {
	for(int i = 0; i < numRows; i++) 
			delete [] imageArr[i];
	delete [] imageArr;
	delete [] xxSecMM;
	delete [] yySecMM;
	delete [] xySecMM;
	delete [] centroid;
	delete [] pointSet;
}

void KIsoDataClust::loadPointSet(string inputFile) {
	ifstream readFile;
	readFile.open(inputFile);
	int dataPoints = -9999;
	int xPoint = -9999;
	int yPoint = -9999;
	//skip the amount of data points
	readFile >> dataPoints;

	for(int i = 0; i < numPts; ++i) {
		readFile >> xPoint >> yPoint;
		pointSet[i].setPointCoord(xPoint, yPoint);
	}
}

void KIsoDataClust::assignLabel() {
	int label = 1;
	for(int i = 0; i < numPts; ++i) {
		pointSet[i].setClusterID(label);
		label++;
		if(label > K)
			label = 1;
	}
}

void KIsoDataClust::prettyPrint(string outputFile) {
		
	ofstream printToFile;
	printToFile.open(outputFile);
	for(int row = 0; row < numRows; ++row) {
		for(int col = 0; col < numCols; ++col) {
			if(imageArr[row][col] > 0 && imageArr[row][col] < 10) 
				printToFile << imageArr[row][col] << " ";
			else if(imageArr[row][col] > 9)
				printToFile << imageArr[row][col] << "  ";
			else 
				printToFile << " ";
			}
		printToFile << endl;
	}
	printToFile.close();
}

void KIsoDataClust::exeIsoDataClustering(string inputFile, string outputFile) {
	loadPointSet(inputFile);
	assignLabel();
	//printFunction(outputFile);
	mapPointToImage();
	prettyPrint(outputFile);
	//printImgArr(outputFile);
}

void KIsoDataClust::mapPointToImage() {
	int rowVal = -9999;
	int colVal = -9999;
	int label  = -9999;
	for(int i = 0; i < numPts; ++i) {
		rowVal = pointSet[i].getXCoord();
		colVal = pointSet[i].getYCoord();
		label  = pointSet[i].getClusterID();
		imageArr[rowVal][colVal] = label;
	}
}

//delete this
void KIsoDataClust::printFunction(string outputFile) {
	ofstream printToFile;
	printToFile.open(outputFile);
	for(int i = 0; i < numPts; ++i) {
		if(pointSet[i].getXCoord() != 0 || 
		   pointSet[i].getYCoord() != 0     )
			printToFile << " + " << endl; 
	}

	for(int i = 0; i < numPts; ++i) {
		if(pointSet[i].getXCoord() != 0 || 
		   pointSet[i].getYCoord() != 0     )
		   cout << pointSet[i].getXCoord() << " " 
				<< pointSet[i].getYCoord() <<  " "
				   << pointSet[i].getClusterID() << endl; 
	}
	printToFile.close();
}

void KIsoDataClust::printImgArr(string outputFile) {
	ofstream printToFile;
	printToFile.open(outputFile);

	for(int i = 0; i < numRows; ++i) {
		for(int j = 0; j < numCols; ++j) {
			if(imageArr[i][j] != 0)
				printToFile << imageArr[i][j] << " ";
		}
		printToFile << endl;
	}
	printToFile.close();
}

int main(int argc, char* argv[]) {
	string inputFile  = argv[1];
	string outputFile = argv[2];
	int userPutForK = 0;
	cout << "Please enter a value for K:\n";
	cin >> userPutForK;
	KIsoDataClust kIsoDataClust(inputFile, userPutForK);
	kIsoDataClust.exeIsoDataClustering(inputFile, outputFile);
	return 0;
}






























