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
		void printImage();
};

	Image::Image(string inputFile) {
		/**
			inputFile is a textfile with input. Input has a header with amount of rows, 
			columns, minimum value and maximum value
			zeroFramedAry will be initialized to amount of rows + 2 and cols + 2 for 
			zeroFraming 
		*/
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
		//skips the header
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
		cout << "\nsetting row " << rowVal << " col " << colVal << endl;
		row = rowVal;
		col = colVal;
	}

	void Point::printPoint() {
		cout << "row " << row << " " 
		<< "col " << col << endl;
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
		int findNextP(Image&);
		int getNeighCoordVal(int val, Image& img) {
			int row = neighborCoord[val].getPointRow();
			int col = neighborCoord[val].getPointCol();
			cout << "Here is row " << row << " and col " << col << endl;
			return img.getIndexVal(row, col);
		}
		void executeChainCode(Image&, ofstream&, ofstream&);
		bool pointsEqual(Point, Point);
		bool pointsEqualVal(Point, Point, Image&);
		void continueChainCode(Image&, ofstream&, ofstream&);
		void printNghbrs(Image&);
		void printFuncForFileOne(ofstream&, int);
		void printFuncForFileTwo(ofstream&, int, int);
		void printNArr(Image& img) {
			for(int i = 0; i < 8; i++) {
				int rw = neighborCoord[i].getPointRow();
				int cl = neighborCoord[i].getPointCol();
				cout << "index : " << i << " | " <<img.getIndexVal(rw, cl) << " | ";
			}
		}
};

	ChainCode::ChainCode() {

		int tempArr[8] =  {6,0,0,2,2,4,4,6};
		for(int i = 0; i < 8; ++i) {
			neighborCoord[i].setPointRowCol(0,0);
			nextDirTable[i] = tempArr[i];
		}
	}

	void ChainCode::loadNeighborCoord(Point currentP) {
		int row = currentP.getPointRow();
		int col = currentP.getPointCol();
		cout << "This is in loadNeighborCoord, row " << row << " col " << col << endl; 
		neighborCoord[0].setPointRowCol(row, col + 1);
		neighborCoord[1].setPointRowCol(row - 1,col + 1);
		neighborCoord[2].setPointRowCol(row - 1,col);
		neighborCoord[3].setPointRowCol(row - 1,col - 1);
		//changing 4
		neighborCoord[4].setPointRowCol(row,col - 1);
		neighborCoord[5].setPointRowCol(row + 1,col - 1);
		neighborCoord[6].setPointRowCol(row + 1,col);
		neighborCoord[7].setPointRowCol(row + 1,col + 1);
		cout << "\nEnd of loadNeighborCoord" << endl;
	}

	bool ChainCode::pointsEqualVal(Point pt1, Point pt2, Image& img) {
		
		int ptOneVal = img.getIndexVal(pt1.getPointRow(), pt1.getPointCol());
		int ptTwoVal = img.getIndexVal(pt2.getPointRow(), pt2.getPointCol());
	
		if(ptOneVal > 0 && ptOneVal == ptTwoVal)
			return true;
		return false;
	}

	int ChainCode::findNextP(Image& img) {
		
		int chainDir = nextQ;
		int counter = 0;
		loadNeighborCoord(currentP);

		while(counter < 8) {
			if(getNeighCoordVal(chainDir % 8, img) > 0) {
				cout << endl << "========================================" << endl;
				cout << "This is in neighborCoord at chairDir\n";
				neighborCoord[chainDir].printPoint();
				cout << "\nneighborCoord arr \n";
				printNArr(img);
				nextP.setPointRowCol(neighborCoord[chainDir % 8 ].getPointRow(),
					                 neighborCoord[chainDir % 8].getPointCol());
				
				

				cout << "this is counter " << counter << endl;
				cout << " This is chairDir " << chainDir % 8 << endl;
				cout << "This is nextP ";
				nextP.printPoint();
				return chainDir % 8;
			}
			counter++;
			chainDir++;
		}
		return chainDir % 8;
	}

	void ChainCode::executeChainCode(Image& image, ofstream& printToFile1, ofstream& printToFile2) {
		
		int rowSize = image.getNumRows() + 2;
		int colSize = image.getNumCols() + 2;
		
		for(int i = 1; i < rowSize; ++i) {
			for(int j = 1; j < colSize; ++j) {
				if(image.getIndexVal(i,j) > 0) {
					startP.setPointRowCol(i,j);
					currentP.setPointRowCol(i,j);
					lastQ = 4;
					printToFile1 << image.getNumRows() << " " << 
				    image.getNumCols() << " " << image.getMinVal() << " "
				    << image.getMaxVal() << " " << startP.getPointRow() 
				    << " " << startP.getPointCol() << " " << image.getIndexVal(i,j)
				    << endl;
				    printToFile2 << image.getNumRows() << " " << 
				    image.getNumCols() << " " << image.getMinVal() << " "
				    << image.getMaxVal() << "\n" << startP.getPointRow() 
				    << " " << startP.getPointCol() << " " << image.getIndexVal(i,j)
				    << endl;
					continueChainCode(image, printToFile1, printToFile2);
					return;
				}
			}
		}
	}

	void ChainCode::continueChainCode(Image& image, ofstream& printToFile1, ofstream& printToFile2) {
		int counter = 1;
		do {	

			nextQ = (lastQ + 1) % 8;
			cout << "\n This is nextQ " << nextQ << endl;
		    Pchain = findNextP(image);
			printFuncForFileOne(printToFile1, Pchain);
			printFuncForFileTwo(printToFile2, Pchain, counter);
			cout << " this is Pchain " << Pchain << endl; 
			lastQ = nextDirTable[Pchain];
			cout << "This is lastQ " << lastQ << endl;
			currentP = nextP;
			cout << " This is currentP ";
			currentP.printPoint();
			cout << endl << "==========================" << endl;
			counter++;
		} while(startP.getPointRow() != currentP.getPointRow() ||
			  startP.getPointCol() != currentP.getPointCol());	 
	}

	bool ChainCode::pointsEqual(Point pt1, Point pt2) {
		if(pt1.getPointRow() == pt2.getPointRow() && pt1.getPointCol() == pt2.getPointCol())
			return true;
		return false;
	}	

	

	void ChainCode::printNghbrs(Image& img) {
		for(int i = 0; i < 8; ++i) {
			int row = neighborCoord[i].getPointRow();
			int col = neighborCoord[i].getPointCol();
			int val = img.getIndexVal(row, col);
			cout << val << " ";
		}
	}

	void ChainCode::printFuncForFileOne(ofstream& printToFile1, int pChain) {
		printToFile1 << pChain << " ";
	}

	void ChainCode::printFuncForFileTwo(ofstream& printToFile2, int pChain, 
		                                                        int counter) {
		if(counter == 20) 
			printToFile2 << endl;
		printToFile2 << pChain << " ";	
	}	

int main(int argc, char* argv []) {
	if(argc != 4) {
		cout << "Program needs 4 Files: \n" <<
	    "an input File \n" << "and 3 outputfiles \n" 
		<<"Terminating" << endl;
		return 0;
	} 
		
	string inputFile = argv[1];
	ofstream printToFile1;
	ofstream printToFile2;
	printToFile1.open(argv[2]);
	printToFile2.open(argv[3]);
	Image image(inputFile);
	image.zeroFramed();
	image.loadImage(inputFile);
	ChainCode chainCode;
	chainCode.executeChainCode(image,printToFile1,printToFile2);
	printToFile1.close();
	printToFile2.close();
}















