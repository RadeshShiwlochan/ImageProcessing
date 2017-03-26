#include<iostream>
#include<fstream>
using namespace std;

class Image {

	private:
		int numRows;
		int numCols;
		int minVal;
		int maxVal;
		int** mirrorFramedAry;

	public:
		Image(string);
		~Image();
		void loadImage(string);
		void mirrorFramed();
		void prettyPrint();	
		//delete these
		void printImg(string);

};

Image::Image(string inputFile) {
	ifstream readFile;
	readFile.open(inputFile);
	readFile >> numRows >> numCols >>
	minVal >> maxVal;
	int rowSize = numRows + 2;
	int colSize = numCols + 2;
	mirrorFramedAry = new int*[rowSize];
	for(int i = 0; i < rowSize; ++i)
		mirrorFramedAry[i] = new int[colSize]();
	readFile.close();
}

Image::~Image() {
	int rowSize = numRows + 2;
	for(int i = 0; i < rowSize; ++i)
		delete [] mirrorFramedAry[i];
	delete [] mirrorFramedAry;
}

void Image::mirrorFramed() {

	for(int i = 0; i <= numRows +1; ++i) {
		mirrorFramedAry[i][0]           = mirrorFramedAry[i][1];
		mirrorFramedAry[i][numCols + 1] = mirrorFramedAry[i][numCols];
	}

	for(int j = 0; j <= numCols + 1; ++j) {
		mirrorFramedAry[0][j]           = mirrorFramedAry[1][j];
		mirrorFramedAry[numRows + 1][j] = mirrorFramedAry[numRows][j];
	}
}

void Image::prettyPrint() {

}

void Image::loadImage(string inputFile) {
	ifstream readFile;
	readFile.open(inputFile);
	int pixelValue = -1;
	int rowSize = numRows + 1;
	int colSize = numCols + 1;
	
	//skip the header	
	for(int i = 0; i < 4; ++i)
		readFile >> pixelValue;

	for(int i = 1; i < rowSize; ++i) {
		for(int j = 1; j < colSize; ++j) {
			readFile >> pixelValue;
			mirrorFramedAry[i][j] = pixelValue;
		}
	}
	readFile.close();
}

void Image::printImg(string outputFile) {
	ofstream printToFile;
	printToFile.open(outputFile);
	int rowSize = numRows + 2;
	int colSize = numCols + 2;
	for(int i = 0; i < rowSize; ++i) {
		for(int j = 0; j < colSize; ++j) {
			if(mirrorFramedAry[i][j] > 9)
				printToFile << mirrorFramedAry[i][j] << " ";
			else 
				printToFile << mirrorFramedAry[i][j] << "  ";
		}
		printToFile << endl;
	}
	printToFile.close();
}

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
		Edge();
		void convolute(int,int); //needs mask as an argument
		void initalizeVertMask();
		void initalizeHortMask();
		void initalizeRightMask();
		void initalizeLeftMask();
		void computeGradient(int,int);	

};

Edge::Edge() {
	initalizeVertMask();
	initalizeHortMask();
	initalizeRightMask();
	initalizeLeftMask();
	
}
	
	

	

	void Edge::initalizeVertMask() {
		maskHorizontal[0][0] = 1;
		maskHorizontal[0][1] = 2;
		maskHorizontal[0][2] = 1;
		maskHorizontal[1][0] = 0;
		maskHorizontal[1][1] = 0;
		maskHorizontal[1][2] = 0;
		maskHorizontal[2][0] = -1;
		maskHorizontal[2][1] = -2;
		maskHorizontal[2][2] = -1;
	
	}

	void Edge::initalizeHortMask() {

		maskVertical[0][0] = 1;
		maskVertical[0][1] = 0;
		maskVertical[0][2] = -1;
		maskVertical[1][0] = 2;
		maskVertical[1][1] = 0;
		maskVertical[1][2] = -2;
		maskVertical[2][0] = 1;
		maskVertical[2][1] = 0;
		maskVertical[2][2] = -1;
		
	}

	void Edge::initalizeRightMask() {
		//right diagonal
		maskRightDiag[0][0] = 0;
		maskRightDiag[0][1] = 1;
		maskRightDiag[0][2] = 2;
		maskRightDiag[1][1] = 0;
		maskRightDiag[1][2] = 1;
		maskRightDiag[2][0] = -2;
		maskRightDiag[2][1] = -1;
		maskRightDiag[2][2] = 0;
		
	}

	void Edge::initalizeLeftMask() {
		//left diagonal
		maskLeftDiag[0][0] = 2;
		maskLeftDiag[0][1] = 1;
		maskLeftDiag[0][2] = 0;
		maskLeftDiag[1][0] = 1;
		maskLeftDiag[1][1] = 0;
		maskLeftDiag[1][2] = -1;
		maskLeftDiag[2][0] = 0;
		maskLeftDiag[2][1] = -1;
		maskLeftDiag[2][2] = -2;
		
	}

int main(int argc, char* argv[]) {
	string inputFile = argv[1];
	string outputFile = argv[2];
	Image image(inputFile);
	image.loadImage(inputFile);
	image.mirrorFramed();
	image.printImg(outputFile);

}