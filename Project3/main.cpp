class ConnectEightCC {

private: 
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int newMin;
	int newMax;
	int newLabel;
	int neighborMin;
	int neighborMax;
	int** zeroFramedAry;
	int* neighborAry;
	int* EqAry;
	struct Property {
		int label;
		int numPixels;
		int minRow;
		int minCol;
		int maxRow;
		int maxCol;
	};
	Property* properties;

public:
	ConnectEightCC(ifstream&);
	~ConnectEightCC();
	void zeroFramedAry();
	void loadNeighbors(int, int, int);
	void connectEightCC_Pass1(ofstream&);
	void connectEightCC_Pass2(ofstream&);
	void connectEightCC_Pass3(ofstream&);
	void updateEqAry();
	void manageEqAry(ofstream&);
	void prettyPrint(ofstream&, int);

};