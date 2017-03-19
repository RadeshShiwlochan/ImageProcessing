#include<fstream>
#include<iostream>
using namespace std;

class Image {

	private:
		int numRows;
		int numCols;
		int minVal;
		int maxVal;
		int** zeroFramedAry;

	public: 
		Image(string);
		~Image();
		void zeroFramed();
		void loadImage(string);
		int getNumRows();
		int getNumCols();
		int getMinVal();
		int getMaxVal();
		int getIndexVal(int, int);

		//temporary functions
		void printImage();
	};

	Image::Image(string inputFile) {
		ifstream readFile;
		readFile.open(inputFile);
		readFile >> numRows >> numCols >>
		            minVal >> maxVal;
		int rowSize = numRows + 2;
		int colSize = numCols + 2;
		zeroFramedAry = new int*[rowSize];
		for(int i = 0; i < rowSize; ++i)
			zeroFramedAry[i] = new int[colSize](); 

		readFile.close();	           
	}

	Image::~Image() {
		int rowSize = numRows + 2;
		for(int i = 0; i < rowSize; ++i)
			delete [] zeroFramedAry[i];
		delete [] zeroFramedAry;
	}

	void Image::zeroFramed() {
		for(int i = 0; i <= numRows +1; i++) {
			zeroFramedAry[i][0]           = zeroFramedAry[i][1];
			zeroFramedAry[i][numCols + 1] = zeroFramedAry[i][numCols];
		}

		for(int j = 0; j <= numCols + 1; j++) {
			zeroFramedAry[0][j]           = zeroFramedAry[1][j];
			zeroFramedAry[numRows + 1][j] = zeroFramedAry[numRows][j];
		}
	}

	void Image::loadImage(string inputFile) {
		ifstream readFile;
		int pixelValue = -1;
		int rowSize = numRows + 1;
		int colSize = numCols + 1;
		readFile.open(inputFile);
		for(int i = 0; i < 4; ++i)
			readFile >> pixelValue;

		for(int i = 1; i < rowSize; ++i) {
			for(int j = 1; j < colSize; ++j) {
				readFile >> pixelValue;
				zeroFramedAry[i][j] = pixelValue;
			}
		}
		readFile.close();
	}

	int Image::getNumRows() { return numRows; }

	int Image::getNumCols() { return numCols; }

	int Image::getMaxVal() { return maxVal; }

	int Image::getMinVal() { return minVal; }

	void Image::printImage() {
		for(int i = 0; i < numRows + 2; ++i) {
			for(int j = 0; j < numCols + 2; ++j) {
				cout << zeroFramedAry[i][j] << " "; 
			}
			cout << endl;
		 }
		 cout << endl;
	}

	int Image::getIndexVal(int row, int col) {
		return zeroFramedAry[row][col];
	}

class Point {

	private:
		int row;
		int col;

	public: 
		Point();
		Point(int, int);
		int getPointRow();
		int getPointCol();
		void setPointRow(int);
		void setPointCol(int);
		void setPointRowCol(int, int);
		bool pointsNotEqual(Point, Point);
		void printPoint();	
	};

	Point::Point() {
		row = 0;
		col = 0;
	}

	Point::Point(int rowVal, int colVal) {
		row = rowVal;
		col = colVal;
	}

	int Point::getPointRow() { return row; }

	int Point::getPointCol() { return col; }

	void Point::setPointRow(int rowVal) { row = rowVal; }

	void Point::setPointCol(int colVal) { col = colVal; }

	void Point::setPointRowCol(int rowVal, int colVal) {
		row = rowVal;
		col = colVal;
	}

	bool Point::pointsNotEqual(Point pt1, Point pt2) {
		if(pt1.row == pt2.row && pt1.col == pt2.col )
			return true;
		return false;
	}

	void Point::printPoint() {
		cout << "row " << row << " \n" 
		<< " col " << col << endl;
	}

class ChainCode {

	private: 
		Point neighborCoord[8];
		Point startP;
		Point currentP;
		Point nextP;
		int nextDirTable[8];
		int nextDir;
		int Pchain;
		int nextQ;
		int lastQ;


	public: 
		ChainCode();
		void loadNeighborCoord(Point);
		int findNextP();
		void prettyPrint(string);
		void executeChainCode(Image&);
	};

	ChainCode::ChainCode() {

		for(int i = 0; i < 8; ++i) {
			neighborCoord[i].setPointRowCol(0,0);
			nextDirTable[i].setPointRowCol(0,0);
		}
	}

	void ChainCode::loadNeighborCoord(Point currentP) {
		int row = currentP.getPointRow();
		int col = currentP.getPointCol();
		//fix these to match the direction
		neighborCoord[0].setPointRowCol(row, col + 1);
		neighborCoord[1].setPointRowCol(row - 1,col + 1);
		neighborCoord[2].setPointRowCol(row - 1,col);
		neighborCoord[3].setPointRowCol(row - 1,col - 1);
		neighborCoord[4].setPointRowCol(row + 1,col - 1);
		neighborCoord[5].setPointRowCol(row + 1,col - 1);
		neighborCoord[6].setPointRowCol(row + 1,col);
		neighborCoord[7].setPointRowCol(row + 1,col + 1);
	}

	int ChainCode::findNextP() {
		int chainDir = -1;
		loadNeighborCoord(currentP);
		
		return chainDir;

	}

	void ChainCode::prettyPrint(string outputFile) {

		// ofstream printToFile;
		// printToFile.open(outputFile);
		// int pixel_value = -1;
		// 	printToFile << "Input Image Pretty Print" << endl;
		// 	printToFile << endl;
		// 	for(int i = 1; i <= numRows + 1; i++) {
		// 		for(int j = 1; j <= numCols + 1; j++) {
		// 			//pixel_value = firstAry[i][j];
		// 			if(pixel_value == 1) 
		// 				printToFile << pixel_value << " ";
		// 			else 
		// 			    printToFile << "  ";
		// 		}
		// 		printToFile << endl;
		// 	}
	}//prettyPrint method

	void ChainCode::executeChainCode(Image& image) {
		 int rowSize = image.getNumRows();
		 int colSize = image.getNumCols();
		for(int i = 1; i < rowSize; ++i) {
			for(int j = 1; j < colSize; ++j) {
				if(image.getIndexVal(i,j) > 0) {
					cout << image.getIndexVal(i,j) << " ";
					startP.setPointRowCol(i,j);
					currentP.setPointRowCol(i,j);
					lastQ = 4;
				}
			}
			cout << endl;
		}
		while(startP.getPointRow() == currentP.getPointRow() &&
			  startP.getPointCol() == currentP.getPointCol()    ) {
			nextQ = (lastQ + 1) % 8;
			Pchain = findNextP();
			//output Pchain to outputFile1 and outputFile2;

			//lastQ = nextDirTable[Pchain];
			currentP = nextP; 
		}
	}

int main(int argc, char* argv []) {
	if(argc != 4) {
		cout << "Program needs 4 Files: \n" <<
	    "an input File \n" << "and 3 outputfiles \n" 
		<<"Terminating" << endl;
		return 0;
	} 
		
	string inputFile = argv[1];
	string outputFile1 = argv[2];
	string outputFile2 = argv[3];

	Image image(inputFile);
	image.zeroFramed();
	image.loadImage(inputFile);
	image.printImage();
	ChainCode chainCode;
	chainCode.executeChainCode(image);
}















