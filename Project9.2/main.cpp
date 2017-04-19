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
	Point(int);
	Point(int,int);
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

Point::Point(int x) {
	xCoordinate = x;
}

Point::Point(int x, int y) {
	xCoordinate = x;
	yCoordinate = y;
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
	xyCoord(int);
	xyCoord(int,int);
	void setXCoord(int);
	void setYCoord(int);
	void setXYCoord(int,int);
	int getXCoord();
	int getYCoord();	
	void printCoord();
};

xyCoord::xyCoord(int x) {
	xCoord = x;
}

xyCoord::xyCoord(int x, int y) {
	xCoord = x;
	yCoord = y;
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
	void loadPointSet();
	void assignLabel();
	void mapPointToImage();
	void isoClustering();
	void printPrintSet();
	void prettyPrint();	
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

int main(int argc, char* argv[]) {
	string inputFile  = argv[1];
	string outputFile = argv[2];
	int userPutForK = 0;
	cout << "Please enter a value for K:\n";
	cin >> userPutForK;
	KIsoDataClust kIsoDataClust(inputFile, userPutForK);
	return 0;
}






























