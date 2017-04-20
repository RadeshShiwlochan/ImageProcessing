#include<iostream>
#include<fstream>
#include<math.h>
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
	void printPrintSet();
	void prettyPrint(string);
	void computeCentroid();	
	void computeXXSecMM();
	void computeYYSecMM();
	void computeXYSecMM();
	double findBestFitAngle();
	double computeT(Point);
	double computeOrthDist(Point);
	void isoClustering();
	void exeIsoDataClustering(string,string);
	int findMin(int*);
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
	xxSecMM = new double[K + 1];
	yySecMM = new double[K + 1];
	xySecMM = new double[K + 1];
	centroid = new xyCoord[K + 1];
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

void KIsoDataClust::computeCentroid() {
	
	int indexVal = -9999;
	int xValInPtSet = 0;
	int xValInTempArr = 0;
	int yValInPtSet   = 0;
	int yValInTempArr = 0;
	int xTotal = 0;
	int yTotal = 0;
	int numOfPtsInGrp = numPts/K;
	Point* tempArr = new Point[K + 1]();
	for(int i = 0; i < numPts; ++i) {
		indexVal = pointSet[i].getClusterID();
		xValInPtSet = pointSet[i].getXCoord();
		xValInTempArr = tempArr[indexVal].getXCoord();
		yValInPtSet = pointSet[i].getYCoord();
		yValInTempArr = tempArr[indexVal].getYCoord();
		xTotal = xValInPtSet + xValInTempArr;
		yTotal = yValInPtSet + yValInTempArr;
	    tempArr[indexVal].setPointCoord(xTotal,yTotal);
	}

	cout << "This is value of numOfPtsInGrp " << numOfPtsInGrp << endl;
	for(int i = 1; i < K + 1; ++i) {
		centroid[i].setXYCoord((tempArr[i].getXCoord()/numOfPtsInGrp), 
			(tempArr[i].getYCoord()/numOfPtsInGrp) );
		cout << "for centroid " << i << " " <<centroid[i].getXCoord() << " " << centroid[i].getYCoord() << endl;
	}
	delete [] tempArr;
}

void KIsoDataClust::computeXXSecMM() {
	int label = 1;
	int numOfPts = numPts/K;
	int* xCoordArr = new int[K + 1];
	while(label <= K) {
		for(int i = 0; i < numPts; ++i) {
			if(pointSet[i].getClusterID() == label)
				xCoordArr[label] += pointSet[i].getXCoord();
		}//for
		xxSecMM[label] = xCoordArr[label]/numOfPts;
		label++;  
    }//while
    delete [] xCoordArr;
}

void KIsoDataClust::computeYYSecMM() {
	int label = 1;
	int numOfPts = numPts/K;
	int* yCoordArr = new int[K + 1];
	while(label <= K) {
		for(int i = 0; i < numPts; ++i) {
			if(pointSet[i].getClusterID() == label)
				yCoordArr[label] += pointSet[i].getYCoord();
		}//for
		yySecMM[label] = yCoordArr[label]/numOfPts;
		label++;
    }//while
}

void KIsoDataClust::computeXYSecMM() {
	int label = 1;
	int numOfPts = numPts/K;
	int* xyCoordArr = new int[K + 1];
	while(label <= K) {
		for(int i = 0; i < numPts; ++i) {
			if(pointSet[i].getClusterID() == label) 
				xyCoordArr[label] += pointSet[i].getXCoord() * pointSet[i].getYCoord();
		}//for
		xySecMM[label] = xyCoordArr[label]/numOfPts;
		label++;
	}
}

double KIsoDataClust::findBestFitAngle() {
	//fix this 
	return 60.0;
}

double KIsoDataClust::computeT(Point pt) {
	double angle = findBestFitAngle();
	double PI = 3.141592653;
	double angleInRadians = angle * (PI/180);
	double T = 0.0;
	int xVal = pt.getXCoord();
	int yVal = pt.getYCoord();
	//maybe absolute value here
	return angleInRadians - atan(yVal/xVal) - (PI/2); 
}

double KIsoDataClust::computeOrthDist(Point pt) {
	double T = computeT(pt);
	return 2.0;
}

void KIsoDataClust::isoClustering() {
	bool changeLabel = false;
	int* tempArr = new int[K];
	for(int i = 0; i < numPts; ++i) {
		//tempArr has to be used for finding the orth distance from Pt to every best fit line
		tempArr[i] = (int)computeOrthDist(pointSet[i]);
	}//have to move this
	int min = findMin(tempArr);
	if(min != pointSet[i].getClusterID())
		pointSet[i].setClusterID(min);

}

void KIsoDataClust::exeIsoDataClustering(string inputFile, string outputFile) {
	loadPointSet(inputFile);
	assignLabel();
	printFunction(outputFile);
	mapPointToImage();
	computeCentroid();
	//prettyPrint(outputFile);
	//printImgArr(outputFile);
}

int KIsoDataClust::findMin(int* arr) {
	int min = arr[0];
	for(int i = 0; i < K; ++i) {
		if(arr[i] < min)
			min = arr[i];
	}//for
	return min;
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

//delete this 
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






























