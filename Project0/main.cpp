class Point {
private:
	int XCoord;
	int YCoord;
	int ClusterLabel;
	double distance;
	Point next;

public:
	Point();
	~Point();
	void setNode(int,int,int,double,Point);
	int getXCoord();
	int getYCoord();
	int getClustLabel();
	double getDistance();
	void printNode();



};

class LinkedList {
private:
	Point Head;

public:
	LinkedList();
	~LinkedList();
	void insertion();
	void deletion();
	void printList();	
};

class KMeans {
private:
	int K;
	int* kCentroids;
	LinkedList linkedlist;
	int numRow;
	int numCol;
	int imageArr**;
	void executeKMeans();
	void displayImage();

};

int main(int argc, char* argv[]) {
	return 0;
}