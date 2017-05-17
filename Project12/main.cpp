#include <iostream>
#include <fstream>
using namespace std;

class Morphology {

private:
	int numRowsIMG;
	int numColsIMG;
	int minValIMG;
	int maxValIMG;
  	int nRowsSE;
	int nColsSE; 
	int minValSE; 
	int maxValSE;
	int rowOrigin;
	int colOrigin;
	int rowFrameSize;
	int colFrameSize;
	int** imgAry; 
	int** morphAry;
    int** structElemArr;

public:
	Morphology(string, string);
	~Morphology();
	void computeFrameSize();  
	void loadImage(string);  
	void loadstruct(string);  
    void zeroFrameImage(); 
    void setMorphArrZero();
	void dilation(); 
	void erosion (); 
	void closing();
	void opening();   
	bool checkIfEq(int, int);
	void prettyPrint(int**, int, int, string);
	void outPutResult(string, string);
	void executeMorphology(string arr[]); 

};

Morphology::Morphology(string inputImage, string inputSE) {

	//read in the image
	ifstream readImg;
	ifstream readFile;
	readImg.open(inputImage);
	readImg >> numRowsIMG >> numColsIMG >> minValIMG >> maxValIMG;
	
	//read in the structuring element
	readFile.open(inputSE);
	readFile >> nRowsSE >> nColsSE >> minValSE >> maxValSE >> rowOrigin >>
	colOrigin >> rowFrameSize >> colFrameSize;
	computeFrameSize();

	imgAry = new int*[rowFrameSize];
	morphAry = new int*[rowFrameSize];
	for(int i = 0; i < rowFrameSize; ++i) {
		imgAry[i] = new int[colFrameSize]();
		morphAry[i] = new int[colFrameSize]();
	}

	structElemArr = new int*[nRowsSE];
	for(int i = 0; i < nRowsSE; ++i)
		structElemArr[i] = new int[nColsSE]();

	readFile.close();
	readImg.close();
          
}

Morphology::~Morphology() {

	// for(int i = 0; i < rowFrameSize; ++i) {
	// 	delete [] imgAry[i];
	// 	delete [] morphAry[i];
	// }
	// delete [] imgAry;
	// delete [] morphAry;

	// for(int i = 0; i < nRowsSE; ++i)
	// 	delete [] structElemArr[i];
	// delete [] structElemArr;
}

void Morphology::computeFrameSize() {
	rowFrameSize = (nRowsSE * 2) + numRowsIMG;
	colFrameSize = (nColsSE * 2) + numColsIMG;
}

void Morphology::loadImage(string inputImage) {

	ifstream readImg;
	int pixel = -1;
	readImg.open(inputImage);
	
	//skip the header
	for(int i = 0; i < 3; ++i)
		readImg >> pixel;

	for(int i = nRowsSE; i < numRowsIMG + 3; ++i) {
		for(int j = nColsSE; j < numColsIMG + 3; ++j) {
			readImg >> pixel;
			imgAry[i][j] = pixel;
		}//for
	}//for
	//set morphArr to all zeroes;
	setMorphArrZero();
	readImg.close();
}

void Morphology::loadstruct(string inputStrElem) {

	ifstream readStrElem;
	int pixel = -1;
	readStrElem.open(inputStrElem);

	//skip the header
	for(int i = 0; i < 6; ++i)
		readStrElem >> pixel;

	for(int i = 0; i < nRowsSE; ++i) {
		for(int j = 0; j < nColsSE; ++j) {
			readStrElem >> pixel;
			structElemArr[i][j] = pixel;
		}
	}//for
	readStrElem.close();
}

void Morphology::zeroFrameImage() {

	for(int i = 0; i < rowFrameSize; i++) {
		imgAry[i][0]              = 0;
		imgAry[i][numColsIMG + nColsSE - 1] = 0;
		morphAry[i][0]            = 0;
		morphAry[i][numColsIMG + nColsSE - 1] = 0;

	}

	for(int j = 0; j < colFrameSize; j++) {
		 imgAry[0][j]               = 0;
		 imgAry[numRowsIMG + nRowsSE - 1][j]     = 0;
		 morphAry[0][j]             = 0;
		 morphAry[numRowsIMG + nRowsSE - 1][j]   = 0;
	}
}

void Morphology::setMorphArrZero() {

	for(int i = 0; i < rowFrameSize; ++i) {
		for(int j = 0; j < colFrameSize; ++j) {
			morphAry[i][j] = 0;
		}//for
	}//for
}

void Morphology::dilation() {
	for(int i = nRowsSE; i < numRowsIMG + 3; ++i) {
		for(int j = nColsSE; j < numColsIMG + 3; ++j) {
			if(imgAry[i][j] > 0) {
				for(int seRow = 0; seRow < nRowsSE; ++seRow) {
					for(int seCol = 0; seCol < nColsSE; ++seCol) {
						if(structElemArr[seRow][seCol] == 1) {
							morphAry[i - rowOrigin + seRow][j - colOrigin + seCol] =
											structElemArr[seRow][seCol];
						}//if statement
					}//for 
				}//for 
			}//if 	
		}
	}

}

void Morphology::erosion() {
	for(int i = nRowsSE; i < numRowsIMG + 3; ++i) {
		for(int j = nColsSE; j < numColsIMG + 3; ++j) {
			if(imgAry[i][j] > 0) {
				if(checkIfEq(i,j))
					morphAry[i][j] = 1;
				else
					morphAry[i][j] = 0;
			}//if statment	
		}
	}

}

bool Morphology::checkIfEq(int i, int j) {
	for(int seRow = 0; seRow < nRowsSE; ++seRow) {
		for(int seCol = 0; seCol < nColsSE; ++seCol) {
			if(structElemArr[seRow][seCol] == 1 &&
					imgAry[i - rowOrigin + seRow][j - colOrigin + seCol] == 0) 
				return false;	
		}//for 
	}//for 
	return true;
}

void Morphology::closing() {

	dilation();
	erosion();
}

void Morphology::opening() {

	erosion();
	dilation();
}

void Morphology::prettyPrint(int** arr, int rows, int cols, 
											string description) {

	cout << endl << endl << description << endl << endl;
	for(int row = 0; row < rows; ++row) {
		for(int col = 0; col < cols; ++col) {
			if(arr[row][col] > 0 ) 
				cout << arr[row][col] << " ";
			 else 
			 	cout << "  ";
		}
		cout << endl;
	}
	cout << endl << endl;

}

void Morphology::outPutResult(string outputFile, string description) {
	ofstream printToFile;
	printToFile.open(outputFile);
	printToFile << description << endl << endl;
	for(int i = 0; i < rowFrameSize ; ++i) {
		for(int j = 0; j < colFrameSize; ++j) {
			printToFile << morphAry[i][j] << " ";
		}
		printToFile << endl;
	}
	printToFile.close();
}

void Morphology::executeMorphology(string files []) {
	prettyPrint(imgAry, rowFrameSize, colFrameSize, "image Array");
	
	prettyPrint(structElemArr, nRowsSE, nColsSE, "structing element");
	dilation();
	outPutResult(files[0], "Dilation Results");
	prettyPrint(morphAry, rowFrameSize, colFrameSize, "Dilation Results");
	setMorphArrZero();

	erosion();
	outPutResult(files[1], "Erosion Results");
	prettyPrint(morphAry, rowFrameSize, colFrameSize, "Erosion Results");
	setMorphArrZero();

	closing();
	outPutResult(files[2],"Closing Results");
	prettyPrint(morphAry, rowFrameSize, colFrameSize, "Closing Results");
	setMorphArrZero();

	opening();
	outPutResult(files[3], "Opening Result");
	prettyPrint(morphAry, rowFrameSize, colFrameSize, "Opening Results");

}


int main(int argc, char* argv[]) {
	if(argc != 7) {
		cout << "Program needs 5 files:\n"
		     << "One inputFile and 4 output " 
		     << "files, Terminating!!" << endl;
		    return 0;
	}
	string inputimage = argv[1];
	string inputStrctElmnt = argv[2];
	string files[4];
	files[0] = argv[3];
	files[1] = argv[4];
	files[2] = argv[5];
	files[3] = argv[6]; 
	Morphology morhology(inputimage, inputStrctElmnt);
	morhology.zeroFrameImage();
	morhology.loadImage(inputimage);
	morhology.loadstruct(inputStrctElmnt);
	morhology.executeMorphology(files);
}




















