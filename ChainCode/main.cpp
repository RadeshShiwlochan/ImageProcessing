#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

class ImageClass {
	friend class ChainCode;
private: 
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int** zeroFramedAry;

public:
	ImageClass(ifstream&);
	~ImageClass();
	void loadImage(ifstream&);
	void zeroFramed();
	friend class ChainCode;	
};

class CCProperty {
	friend class ChainCode;
private:
	struct Property {
		int label;
		int numPixels;
		int minRow;
		int minCol;
		int maxRow;
		int maxCol;
	};

	Property properties;

public:
	CCProperty();
	CCProperty(string);	
};

class Point {
public:
	int row;
	int col;
	void setPoint(int r, int c) {
		row = r;
		col = c;
	}
};

class ChainCode {
private:
	ImageClass* image;
	CCProperty* propertyfile;
	int currentCC;
	int minRowOffset;
	int maxRowOffset;
	int minColOffset;
	int maxColOffset;
	// struct Point {
	// 	int row;
	// 	int col;
	// };

	Point* neighborCoord;
	const int nextDirTable[8] = {6,0,0,2,2,4,4,6};
	Point currentP;
	Point nextP;
	int nextQ;
	int pChain;
	int lastQ;

public:
	ChainCode(ifstream&, ifstream&, ofstream&, ofstream&);
	~ChainCode();
	void loadNeighborCoord();
	int findNextP();
	void runAlgorithm(ofstream&, ofstream&);

};

void ImageClass::zeroFramed() {
	for(int i = 0; i < numRows + 2; i++) {
		zeroFramedAry[i][0] = 0;
		zeroFramedAry[i][numCols + 1] = 0;
	}
	for(int i = 0; i < numCols + 2; i++) {
		zeroFramedAry[0][i] = 0;
		zeroFramedAry[numRows + 1][i] = 0;
	}
}

ImageClass::ImageClass(ifstream& imageFile) {
	imageFile >> numRows >> numCols >> minVal >> maxVal;
	zeroFramedAry = new int*[numRows + 2];
	for(int i = 0; i < numRows + 2; i++) {
		zeroFramedAry[i] = new int[numCols]();
	}
	zeroFramed();
	loadImage(imageFile);
}

ImageClass::~ImageClass() {
	if(zeroFramedAry != nullptr) {
		delete [] zeroFramedAry;
	}
}

void ImageClass::loadImage(ifstream& imageFile) {
	for(int i = 0; i < numRows; i++) {
		for(int j = 0; j < numCols; j++) {
			imageFile >> zeroFramedAry[i + 1][j + 1];
		}
	}
}

CCProperty::CCProperty() {
	properties.label = 0;
	properties.maxCol = 0;
	properties.maxRow = 0;
	properties.maxCol = 0;
	properties.minRow = 0;
	properties.numPixels = 0;
}

CCProperty::CCProperty(string line) {
	istringstream numList(line);
	numList >> properties.label >> properties.numPixels >> properties.minRow >>
	properties.minCol >> properties.maxRow >> properties.maxCol;
}

ChainCode::ChainCode(ifstream& cc, ifstream& pp, ofstream& chaincode, ofstream& debugFile) {
	debugFile << "ChainCode object initialization beginning ---\n";
	image = new ImageClass(cc);
	debugFile << "Image has just been initialized ..\n";
	propertyfile = new CCProperty[image->maxVal + 1];
	debugFile << "propertyfile created with size " << image->maxVal + 1 << " ...\n";
	string propertyline;
	for(int i = 1; i <= image->maxVal; i++) {
		getline(pp, propertyline);
		debugFile << "Read line from propterty file: \"" << propertyline << "\"...\n";
		propertyfile[i] = CCProperty(propertyline);
	}
	currentCC = 1;
	neighborCoord = new Point[8];
	debugFile << "ChainCode object initialization and instantiation complete \n";
}

ChainCode::~ChainCode() {
	if(image != nullptr) 
		delete image;
	if(propertyfile != nullptr)
		delete [] propertyfile;
	if(neighborCoord != nullptr)
		delete [] neighborCoord;
}

void ChainCode::loadNeighborCoord() {
	neighborCoord[0].row = currentP.row;
	neighborCoord[0].col = currentP.col + 1;
	neighborCoord[1].row = currentP.row - 1; 
	neighborCoord[1].col = currentP.col + 1;
	neighborCoord[2].row = currentP.row - 1;
	neighborCoord[2].col = currentP.col;
	neighborCoord[3].row = currentP.row - 1;
	neighborCoord[3].col = currentP.col - 1;
	neighborCoord[4].row = currentP.row;
	neighborCoord[4].col = currentP.col - 1;
	neighborCoord[5].row = currentP.row + 1;
	neighborCoord[5].col = currentP.col - 1;
	neighborCoord[6].row = currentP.row + 1;
	neighborCoord[6].col = currentP.col;
	neighborCoord[7].row = currentP.row + 1;
	neighborCoord[7].col = currentP.col + 1;
}

int ChainCode::findNextP() {
	loadNeighborCoord();
	int sdir = nextQ;
	do {
		if(image->zeroFramedAry[neighborCoord[sdir % 8].row][neighborCoord[sdir % 8].col] == 
			currentCC)
			break;
		sdir++;
	} while ((sdir % 8) != nextQ % 8);
	return sdir % 8;
}

void ChainCode::runAlgorithm(ofstream& outfile, ofstream& debugFile) {
	debugFile << "Starting the Algorithm" << endl;
	for( currentCC; currentCC <= image->maxVal; currentCC++) {
		debugFile << "currentCC = " << currentCC << ":\n";
		minRowOffset = propertyfile[currentCC].properties.minRow;
		minColOffset = propertyfile[currentCC].properties.minCol;
		maxRowOffset = propertyfile[currentCC].properties.maxRow;
		maxColOffset = propertyfile[currentCC].properties.maxCol;
	
		Point startp;
		for(int col = minColOffset + 1; col <= maxColOffset + 1; col++) {
			if(image->zeroFramedAry[minRowOffset + 1][col] == currentCC) {
				outfile << minRowOffset << " " << col - 1 << " " << currentCC << " ";
				startp.setPoint(minRowOffset, col);
				debugFile << " startp set to (" << startp.row << "," << startp.col << 
				" ) ....\n";
				currentP.setPoint(minRowOffset + 1, col);
				lastQ = 4;
				do {
					nextQ = (lastQ + 1) % 8;
					pChain = findNextP();
					nextP = neighborCoord[pChain];
					outfile << pChain << " ";
					lastQ = nextDirTable[pChain - 1];
					currentP = nextP;
					debugFile << "\ncurrentP set to ( " << currentP.row << " ," 
					<< currentP.col << ") ...\n";
					} while((currentP.row != startp.row) || (currentP.col != startp.col));
				outfile << endl;
				break;
			} 
		}
	}
		debugFile << "ChainCode code Algorithm execution is now complete\n";
}

int main(int argc, char* argv[]) {
	ifstream cc;
	cc.open(argv[1]);
	ifstream pp;
	pp.open(argv[2]);
	ofstream codefile; 
	codefile.open(argv[3]);
	ofstream debugFile;
	debugFile.open(argv[4]);

	ChainCode chain(cc, pp, codefile, debugFile);
	//chain.runAlgorithm(codefile, debugFile);

	cc.close();
	pp.close();
	codefile.close();
	debugFile.close();
	return 0;
}
















