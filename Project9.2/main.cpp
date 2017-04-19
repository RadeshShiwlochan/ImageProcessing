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
	xyCoord(int,int);
	void setXCoord(int);
	void setYCoord(int);
	void setXYCoord(int,int);
	int getXCoord();
	int getYCoord();	
	void printCoord();
};

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

int main(int argc, char* argv[]) {
	return 0;
}






























