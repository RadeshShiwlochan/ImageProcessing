#include <iostream>
#include <sstream>
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

class ChainCode {
private:
	ImageClass* image;
	CCProperty* propertyfile;
	int currentCC;
	int minRowOffset;
	int maxRowOffset;
	int minColOffset;
	int maxColOffset;
	struct Point {
		int row;
		int col;
	};

	Point* neighborCoord;
	const int nextDirTable[8];
	Point currentP;
	Point nextP;
	int nextQ;
	int pChain;
	int lastQ;

public:
	ChainCode(ifstream& ofstream&, ofstream&, ofstream&);
	~ChainCode();
	void loadNeighborCoord();
	int findNextP();
	void runAlgorithm(ofstream&, ofstream&);

};

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

















