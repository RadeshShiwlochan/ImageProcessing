#include <iostream>
#include <fstream>
using namespace std;

class Morphology {
private:
	int numRowsIMG;
	int numColsIMG;
	int minValIMG;
	int maxValIMG;
  	int numRowsStrctElem;
	int numColsStrctElem;
	int minValStrctElem; 
	int maxValStrctElem;
	int rowOrigin;
	int colOrigin;
	int rowFrameSize;
	int colFrameSize;
	int** imgAryl; 
	int** morphAry;
    int** structElem;

public:
	Morphology(string, string);
	~Morphology();
	void computeFrameSize();  
	void loadImage();  
	void loadstruct();  
    void zeroFrameImage(); 
	void dilation(int , int); 
	void erosion (int ,int); 
	void closing(int,int);
	void opening(int,int);   
	void prettyPrint();
	void outPutResult(); 

};

Morphology::Morphology(string inputImage, string inputStrElem) {
	ifstream readImg;
	ifstream readStrElem;
	readImg.open(inputImage);
	readStrElem.open(inputStrElem);
	readImg >> numRowsIMG >> numColsIMG >> minValIMG >> maxValIMG;
	readStrElem >> numRowsStrctElem >> numColsStrctElem >> minValStrctElem 
	            >> maxValStrctElem >> rowOrigin >> colOrigin;
	 readImg.close();
	 readStrElem.close();           
}

Morphology::~Morphology() {

}
/** 
	rowFrameSize set to numRowsStrctElem (half to the top and half to the bottom) 
	colFrameSize set to numColsStrctElem (half to the left and half to the right) 
*/
void Morphology::computeFrameSize() {
	rowFrameSize = (numRowsStrctElem * 2) + numRowsIMG;
	colFrameSize = (numColsStrctElem * 2) = numColsIMG;
}

// load imgAry from input1
void Morphology::loadImage(string inputImage) {
	ifstream readImg;
	int pixel = -1;
	readImg.open(inputImage);
	imgAry = new int*[rowFrameSize];
	for(int i = 0; i < rowFrameSize; ++i)
		imgAry[i] = new int[colFrameSize]();
	//skip the header
	for(int i = 0; i < 3; ++i)
		readImg >> pixel;

	for(int i = numRowsStrctElem; i < rowFrameSize; ++i) {
		for(int j = numColsStrctElem; j < colFrameSize; ++j) {
			readImg >> pixel;
			imgAry[i][j] = pixel;
		}
	}//for
	readImg.close();
}

// load structAry from input2
void Morphology::loadstruct(string inputStrElem) {
	ifstream readStrElem;
	int pixel = -1;
	readImg.open(inputStrElem);
	structAry = new int*[numRowsStrctElem];
	for(int i = 0; i < numRowsStrctElem; ++i)
		imgAry[i] = new int[numColsStrctElem]();
	//skip the header
	for(int i = 0; i < 6; ++i)
		readImg >> pixel;

	for(int i = 0; i < numRowsStrctElem; ++i) {
		for(int j = 0; j < numColsStrctElem; ++j) {
			readImg >> pixel;
			structAry[i][j] = pixel;
		}
	}//for
	readStrElem.close();
}

void Morphology::zeroFrameImage() {

}

// at pixel(i,j), i begins at numRowsStrctElem / 2, and j begins at numColsStrctElem / 2
void Morphology::dilation(int pixel1, int pixel2) {

}

// at pixel(i,j)
void Morphology::erosion(int pixel1, int pixel2) {

}

// at pixel(i,j)
void Morphology::closing(int pixel1, int pixel2) {

}

// at pixel(i,j)
void Morphology::opening(int pixel1, int pixel2) {

}

void Morphology::prettyPrint() {

}

void Morphology::outPutResult() {

}


int main(int argc, char* argv[]) {
	// if(argc != 4) {
	// 	cout << "Program needs 5 files:\n"
	// 	     << "One inputFile and 4 output " 
	// 	     << "files, Terminating!!" << endl;
	// 	    return 0;
	// }
	string inputimage = argv[1];
	string inputStrctElmnt = argv[2];
	//string outputFile1 = argv[3];
	//string outputFile2 = argv[4];
	//string outputFile3 = argv[5];
	//string outputFile4 = argv[6]; 

}




















