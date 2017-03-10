class Image {
private:
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int** zeroFramedAry;

public: 
	Image();
	void zeroFramed();
	void loadImage();

};

class Point {
private:
	int row;
	int col;
public: 
	int getPointRow();
	int getPointCol();
	void setPointRow(int);
	void setPointCol(int);	
};

class ChainCode {
private: 
	Point neighborCoord[8];
	Point currentPoint;
	Point nextPoint;
	Point lastQ;
	Point nextDirTable[8];
	Point nextDir;
	Point Pchain;

public: 
	ChainCode();
	void loadNeighborCoord();
	void findNextPoint();
	void prettyPrint();

};