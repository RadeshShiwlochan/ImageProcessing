#include<iostream>
#include<fstream>
#include<stdio.h>     
#include<stdlib.h>
#include<math.h>

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
		int getNumRows();
		int getNumCols();
		int getIndexVal(int,int);

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

int Image::getNumRows() {
	return numRows;
}

int Image::getNumCols() {
	return numCols;
}

int Image::getIndexVal(int rowIndex, int colIndex) {
	return mirrorFramedAry[rowIndex][colIndex];
}

class Edge {

	private:
		int ImgRows;
		int ImgCols;
		int maskVertical[3][3];
		int maskHorizontal[3][3];
		int maskRightDiag[3][3];
		int maskLeftDiag[3][3];
		int** SobelVertical;
		int** SobelHorizontal;
		int** SobelRightDiag;
		int** SobelLeftDiag;
		int** GradientEdge;


	public:
		Edge(int, int);
		~Edge();
		void initalizeVertMask();
		void initalizeHortMask();
		void initalizeRightMask();
		void initalizeLeftMask();
		void executeSobel(Image&);
		int convolute(int,int, int [][3], Image&); 
		int loadNeighbors(int,int,Image&);
		void printImages(string[],int,int);
		void printSobelArr(string, int**, int,int);
		//deete mask
		void printMask();
		void printTempArr(int[][3]);
		//
		int computeGradient(int,int,Image&);	

};

Edge::Edge(int img_Rows, int img_Cols) {
	ImgRows = img_Rows;
	ImgCols = img_Cols;
	initalizeVertMask();
	initalizeHortMask();
	initalizeRightMask();
	initalizeLeftMask();
	SobelVertical = new int*[ImgRows];
	SobelHorizontal = new int*[ImgRows];
	SobelRightDiag = new int*[ImgRows];
	SobelLeftDiag = new int*[ImgRows];
	GradientEdge = new int*[ImgRows];

	for(int i = 0; i < ImgRows; ++i) {
		SobelVertical[i] = new int[ImgCols]();
		SobelHorizontal[i] = new int[ImgCols]();
		SobelRightDiag[i] = new int[ImgCols]();
		SobelLeftDiag[i] = new int[ImgCols]();
		GradientEdge[i] = new int[ImgCols]();
	}
	
}

Edge::~Edge() {
	//delete this
	cout << "Edge Destructor called " << endl;
	for(int i = 0; i < ImgRows; ++i) {
		delete [] SobelVertical[i];
		delete [] SobelHorizontal[i];
		delete [] SobelRightDiag[i];
		delete [] SobelLeftDiag[i];
		delete [] GradientEdge[i];
	}
	    delete [] SobelVertical;
		delete [] SobelHorizontal;
		delete [] SobelRightDiag;
		delete [] SobelLeftDiag;
		delete [] GradientEdge;

}
	
void Edge::initalizeVertMask() {

	maskVertical[0][0] = 1;
	maskVertical[0][1] = 2;
	maskVertical[0][2] = 1;
	maskVertical[1][0] = 0;
	maskVertical[1][1] = 0;
	maskVertical[1][2] = 0;
	maskVertical[2][0] = -1;
	maskVertical[2][1] = -2;
	maskVertical[2][2] = -1;

}

void Edge::initalizeHortMask() {

	maskHorizontal[0][0] = 1;
	maskHorizontal[0][1] = 0;
	maskHorizontal[0][2] = -1;
	maskHorizontal[1][0] = 2;
	maskHorizontal[1][1] = 0;
	maskHorizontal[1][2] = -2;
	maskHorizontal[2][0] = 1;
	maskHorizontal[2][1] = 0;
	maskHorizontal[2][2] = -1;
		
}

void Edge::initalizeRightMask() {
	//right diagonal
	maskRightDiag[0][0] = 0;
	maskRightDiag[0][1] = 1;
	maskRightDiag[0][2] = 2;
	maskRightDiag[1][0] = -1;
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

void Edge::executeSobel(Image& imageObj) {
	int rowLimit = imageObj.getNumRows() + 1;
	int colLimit = imageObj.getNumCols() + 1;
	
	for(int i = 1; i < rowLimit; i++) {
		for(int j = 1; j < colLimit; j++) {
			SobelVertical[i][j]    = abs(convolute(i,j,maskVertical,imageObj));
			SobelHorizontal[i][j]  = abs(convolute(i,j,maskHorizontal,imageObj));
			SobelRightDiag[i][j]   = abs(convolute(i,j,maskRightDiag,imageObj));
			SobelLeftDiag[i][j]    = abs(convolute(i,j,maskLeftDiag,imageObj));
			GradientEdge[i][j]    = computeGradient(i,j,imageObj);
		}
	}
} 	

int Edge::convolute(int rowIndex, int colIndex, int maskArray[][3], Image& imgObj) {
	
	//int* neighborArr = loadNeighbors(rowIndex,colIndex,imgObj);
	int tempArray[3][3];
	int result = 0;
	tempArray[0][0] = imgObj.getIndexVal(rowIndex - 1, colIndex - 1);
	tempArray[0][1] = imgObj.getIndexVal(rowIndex - 1, colIndex);
	tempArray[0][2] = imgObj.getIndexVal(rowIndex - 1, colIndex + 1);
	tempArray[1][0] = imgObj.getIndexVal(rowIndex, colIndex - 1);
	tempArray[1][1] = imgObj.getIndexVal(rowIndex, colIndex);
	tempArray[1][2] = imgObj.getIndexVal(rowIndex, colIndex + 1);
	tempArray[2][0] = imgObj.getIndexVal(rowIndex + 1, colIndex - 1);
	tempArray[2][1] = imgObj.getIndexVal(rowIndex + 1, colIndex);
	tempArray[2][2] = imgObj.getIndexVal(rowIndex + 1, colIndex + 1);

	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3; ++j) {
			result += tempArray[i][j] * maskArray[i][j]; 
		}
	}
	//printTempArr(neighborArr);
	return result;
}

int Edge::computeGradient(int rowValue, int colValue, Image& imgObj) {
	int gradientNghbrArr[4];
	int pixel = 0;
	int gradient = 0;
	int a = 0;
	int b = 0;
	gradientNghbrArr[0] = imgObj.getIndexVal(rowValue, colValue);
	gradientNghbrArr[1] = imgObj.getIndexVal(rowValue, colValue + 1);
	gradientNghbrArr[2] = imgObj.getIndexVal(rowValue + 1, colValue);
	gradientNghbrArr[3] = imgObj.getIndexVal(rowValue + 1, colValue + 1);
	pixel = gradientNghbrArr[0];
	a = gradientNghbrArr[1];
	b = gradientNghbrArr[2];
	gradient = sqrt( pow((pixel - b),2) + pow((pixel - a),2));
	return gradient;
}	

int loadNeighbors(int rowIndex, int colIndex, Image& imgObj) {
	
	return 0;
}

void Edge::printImages(string files[],int rows, int cols) {
	
	printSobelArr(files[0], SobelVertical, rows, cols);
	printSobelArr(files[1], SobelHorizontal, rows, cols);
	printSobelArr(files[2], SobelRightDiag, rows, cols);
	printSobelArr(files[3], SobelLeftDiag, rows, cols);
	printSobelArr(files[4], GradientEdge, rows, cols);
}

void Edge::printSobelArr(string file, int** arr, int rows, int cols) {
	ofstream printToFile;
	printToFile.open(file);

	for(int i = 0; i < rows; ++i) {
		for(int j = 0; j < cols; ++j) {
			if(arr[i][j] > 9) {
				printToFile << arr[i][j] << " ";	
			} else {
				printToFile << arr[i][j] << "  ";
			}
		}
		printToFile << endl;
	}

}

void Edge::printMask() {

	cout << " maskVertical : " << endl;

	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3;++j) {
			if(maskVertical[i][j] > 9 || maskVertical[i][j] < 0) 
				cout << maskVertical[i][j] << " ";
			else 
				cout << maskVertical[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;

	cout << " maskHorizontal: " << endl;

	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3;++j) {
			if(maskHorizontal[i][j] > 9 || maskHorizontal[i][j] < 0) 
				cout << maskHorizontal[i][j] << " ";
			else 
				cout << maskHorizontal[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;

	cout << " maskRightDiag : " << endl;

	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3;++j) {
			if(maskRightDiag[i][j] > 9 || maskRightDiag[i][j] < 0) 
				cout << maskRightDiag[i][j] << " ";
			else 
				cout << maskRightDiag[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;

	cout << " maskLeftDiag : " << endl;

	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3;++j) {
			if(maskLeftDiag[i][j] > 9 || maskLeftDiag[i][j] < 0) 
				cout << maskLeftDiag[i][j] << " ";
			else 
				cout << maskLeftDiag[i][j] << "   ";
		}
		cout << endl;
	}
	cout << endl;
}

void Edge::printTempArr(int arr[][3]) {
	cout << endl;
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3; ++j) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main(int argc, char* argv[]) {

	if(argc != 7) {
		cout << "Needs 6 input files, terminating!! \n";
		return 0;
	}
	string inputFile = argv[1];
	string outputFile1 = argv[2];
	string outputFile2 = argv[3];
	string outputFile3 = argv[4];
	string outputFile4 = argv[5];
	string outputFile5 = argv[6];
	string files[5];
	files[0] = argv[2];
	files[1] = argv[3];
	files[2] = argv[4];
	files[3] = argv[5];
	files[4] = argv[6];
	Image image(inputFile);
	image.loadImage(inputFile);
	image.mirrorFramed();
	int numOfRows = image.getNumRows() + 2;
	int numOfCols = image.getNumCols() + 2;
	Edge edge(numOfRows,numOfCols);
	edge.executeSobel(image);
	edge.printImages(files, numOfRows, numOfCols);

}