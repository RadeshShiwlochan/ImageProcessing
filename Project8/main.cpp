class Image {

private:
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int** mirrorFramedAry;

public:
	Image();
	void loadImage();
	void mirrorFramed();
	void prettyPrint();	

};

class Edge {

private:
	int maskVertical[3][3];
	int maskHorizontal[3][3];
	int maskRightDiag[3][3];
	int maskLeftDiag[3][3];
	int** SobelVertical;
	int** SobelHorizontal;
	int** SobelRightDiag;
	int** SobelLeftDiag;
	int** GradiantEdge;

public:
	void convolute(int,int); //needs mask as an argument
	void computeGradient(int,int);	
};