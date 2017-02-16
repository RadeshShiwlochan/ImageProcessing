#include<iostream>
#include<fstream>
using namespace std;

class CorPerFilter {
private:
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int newMin;
	int newMax;
	int** mirrorFramedAry;
	int** tempAry;
	int neighborAry[9];
	double neighborAVG[8];

public:
	CorPerFilter(string);
	~CorPerFilter();
	void mirrorFramed();
	void loadImage(string);
	void loadNeighbors(int, int, int);
	double computeAVG();
	double minAVG();
	void findNewMinMax();
	void outputImage(string);
	void cornPrvMethod();
	void getRectShapedNeighbors(int, int, int, int);
	void getTriShapedNghbrsG5(int, int);
	void getTriShapedNghbrsG6(int, int);
	void getTriShapedNghbrsG7(int, int);
	void getTriShapedNghbrsG8(int, int);
};

	CorPerFilter::CorPerFilter(string inputFile) {
		ifstream getHeader;
		getHeader.open(inputFile);
		getHeader >> numRows >> numCols >> minVal >> maxVal;
		int rowSize = numRows + 4;
		int colSize = numCols + 4;
		mirrorFramedAry = new int*[rowSize];
		tempAry = new int*[numRows];
		
		//allocate and initalize arrays
		for(int i = 0; i < rowSize; i++) {
			mirrorFramedAry[i] = new int[colSize]();
		}
		for(int i = 0; i < numCols; i++)
			tempAry[i] = new int[numCols]();		
	}

	CorPerFilter::~CorPerFilter() {

		for(int i = 0; i < numRows; i++) { 	
			delete [] mirrorFramedAry[i + 2];
			delete [] tempAry[i];
		}
		delete [] mirrorFramedAry;
		delete [] tempAry;
    }

	

void CorPerFilter::mirrorFramed() {
	//framing left to right
	for(int i = 0; i <= numRows + 3; i++) {
		mirrorFramedAry[i][0]           = mirrorFramedAry[i][2];
		mirrorFramedAry[i][1]           = mirrorFramedAry[i][2];
		mirrorFramedAry[i][numCols + 2] = mirrorFramedAry[i][numCols + 1];
		mirrorFramedAry[i][numCols + 3] = mirrorFramedAry[i][numCols + 1];
	}
	//framing top to bottom
	for(int j = 0; j <= numCols + 3; j++) {
		 mirrorFramedAry[0][j]           = mirrorFramedAry[2][j];
		 mirrorFramedAry[1][j]           = mirrorFramedAry[2][j];
		 mirrorFramedAry[numRows + 2][j] = mirrorFramedAry[numRows + 1][j];
		 mirrorFramedAry[numRows + 3][j] = mirrorFramedAry[numRows + 1 ][j];
	}
}

void CorPerFilter::loadImage(string inputFile) {

	// fix number of rows here
	ifstream readInputFile;
	readInputFile.open(inputFile);
	int numFromFile;

	//skip the header
	for(int i = 0; i < 4; i++)
		readInputFile >> numFromFile;
	
	for(int i = 2; i < numRows + 2; i++) {
		for(int j = 2; j < numCols + 2; j++) {
			readInputFile >> numFromFile;
			mirrorFramedAry[i][j] = numFromFile;
		}
	}
}

void CorPerFilter::loadNeighbors(int which, int rowIndex, int colIndex) {
	if(which == 0) {
		int startRowIndex = rowIndex - 2;
		int startColIndex = colIndex - 2;
		getRectShapedNeighbors(startRowIndex, rowIndex, startColIndex, colIndex);
		neighborAVG[which] = computeAVG();
	} else if(which == 1) {
		int startRwIndex = rowIndex - 2;
		int endColIndex = colIndex + 2;
		getRectShapedNeighbors(startRwIndex, rowIndex, colIndex, endColIndex);
		neighborAVG[which] = computeAVG();
	} else if(which == 2) {
		int endRwIndex = rowIndex + 2;
		int colStartIndex = colIndex - 2;
		getRectShapedNeighbors(rowIndex, endRwIndex, colStartIndex, colIndex);
		neighborAVG[which] = computeAVG();
	} else if(which == 3) {
		int endRwIndex = rowIndex + 2;
		int endColIndex = colIndex + 2;
		getRectShapedNeighbors(rowIndex, endRwIndex, colIndex, endColIndex);
		neighborAVG[which] = computeAVG();
	} else if(which == 4) {
		getTriShapedNghbrsG5(rowIndex, colIndex);
		neighborAVG[which] = computeAVG();
	} else if(which == 5) {
		getTriShapedNghbrsG6(rowIndex, colIndex);
		neighborAVG[which] = computeAVG();
	} else if(which == 6) {
		getTriShapedNghbrsG7(rowIndex, colIndex);
		neighborAVG[which] = computeAVG();
	} else if(which == 7) {
		getTriShapedNghbrsG8(rowIndex, colIndex);
		neighborAVG[which] = computeAVG();
	}
}

double CorPerFilter::computeAVG() {
	double sum = 0.0;
	for(int i = 0; i < 9; i++)
		sum += neighborAry[i];
	return sum/9.0;

}

double CorPerFilter::minAVG() {
	double min = neighborAVG[1];
	for(int i = 0; i < 8; i++) {
		if (neighborAVG[i] < min)
			min = neighborAVG[i];
	}
	return min;
}

void CorPerFilter::findNewMinMax() {
	 newMax = -1;
	 newMin = maxVal;
	 for(int i = 0; i < numRows; i++) {
	 	for(int j = 0; j < numCols; j++) {
	 		if(newMax < tempAry[i][j])
	 			newMax = tempAry[i][j];

	 		if(newMin > tempAry[i][j])
	 			newMin = tempAry[i][j];
	 	}
	 }
}

void CorPerFilter::outputImage(string outfile) {
	ofstream printer;
	printer.open(outfile);

	printer << numRows << "  " << numCols << "  "
	<< newMin << "  " << newMax << endl;

	for(int i = 0; i < numRows; i++) {
		for(int j = 0; j < numCols; j++) {
			printer << tempAry[i][j] << " ";
		}
		printer << endl;
	}	
}

void CorPerFilter::getRectShapedNeighbors(int startRwIndex, int endRowIndex,int startColIndex, int endColIndex) {
	int index = 0;
	for(int i = startRwIndex; i <= endRowIndex; i++) {
			for(int j = startColIndex; j <= endColIndex; j++) {
				neighborAry[index++] = mirrorFramedAry[i][j];
			}
		}
}

void CorPerFilter::getTriShapedNghbrsG5(int rowIndex, int colIndex) {
	int startRowIndex = rowIndex + 2;
	int endRowIndex = rowIndex;
	int startColIndex = colIndex - 2;
	int endColIndex = colIndex + 2;
	int colstartLim = 0;
	int index = 0;
	for(int i = startRowIndex; i >= endRowIndex; i--) {
		for(int j = startColIndex + colstartLim; j <= (endColIndex - colstartLim) && colstartLim <= 2; j++) {
			neighborAry[index++] = mirrorFramedAry[i][j];
		}	
			colstartLim++;
	}
}

void CorPerFilter::getTriShapedNghbrsG6(int rowIndex, int colIndex) {
	int startRowIndex = rowIndex - 2;
	int endRowIndex = rowIndex + 2;
	int startColIndex = colIndex - 2;
	int endColIndex = colIndex;
	int colstartLim = 0;
	int index = 0;
	for(int j = startColIndex; j <= endColIndex; j++) {
		for(int i = startRowIndex + colstartLim; i <= (endRowIndex - colstartLim) && colstartLim <=2; i++) {
			neighborAry[index++] = mirrorFramedAry[i][j];
		}	
			colstartLim++;
	}
}

void CorPerFilter::getTriShapedNghbrsG7(int rowIndex, int colIndex) {
	int startRowIndex = rowIndex - 2;
	int endRowIndex = rowIndex + 2;
	int colStartIndex = colIndex + 2;
	int colEndIndex = 2;
	int colstartLim = 0;
	int index = 0;
	for(int j = colStartIndex; j >= colIndex; j--) {
		for(int i = startRowIndex + colstartLim; i <= (endRowIndex - colstartLim) && colstartLim <=2; i++) {
			neighborAry[index++] = mirrorFramedAry[i][j];
		}	
			colstartLim++;
	}
}

void CorPerFilter::getTriShapedNghbrsG8(int rowIndex, int colIndex) {
	int startRowIndex = rowIndex - 2;
	int endRowIndex = rowIndex;
	int startColIndex = colIndex - 2;
	int endColIndex = colIndex + 2;
	int colstartLim = 0;
	int index = 0;
	for(int i = startRowIndex; i <= endRowIndex; i++) {
		for(int j = startColIndex + colstartLim; j <= (endColIndex - colstartLim) && colstartLim <=2; j++) {
			neighborAry[index++] = mirrorFramedAry[i][j];
		}	
			colstartLim++;
	}
}

void CorPerFilter::cornPrvMethod() {
	int which = 0;
	for(int i = 2; i < numRows + 2; i++) {
		for(int j = 2; j < numCols + 2; j++) {
			while(which < 8) {
				loadNeighbors(which,i,j);
				which++;
			}
			tempAry[(i - 2)][(j - 2)] = minAVG();
			which = 0;
		}
	}
}

int main(int argc, char* argv[]) {

	if(argc != 3) {
		cout << "Program needs an input and output file";
		return 0;
	}
	string inputFile = argv[1];
	string outputFile = argv[2];
	CorPerFilter corPerFilter(inputFile);
	corPerFilter.loadImage(inputFile);
	corPerFilter.mirrorFramed();
	corPerFilter.cornPrvMethod();
	corPerFilter.findNewMinMax();
	corPerFilter.outputImage(outputFile);
	
	return 0;
}