/*
	Name: Sobel Edge Detection
	Author: Joseph Russo
	Date: 28/03/17 21:43
*/

#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<stdlib.h>
using namespace std;

class Edge{
public:	
	int maskVertical[3][3];
	int maskHorizontal[3][3];
	int maskRightDiag[3][3];
	int maskLeftDiag[3][3];
	int** SobelVertical;
	int** SobelHorizontal;
	int** SobelRightDiag;
	int** SobelLeftDiag;
	int** GradiantEdge;
	int Row;
	int Col;
	int Min=100;
	int Max=0;
  
public :
	Edge(){
		maskVertical[0][0] = 1;
		maskVertical[0][1] = 2;
		maskVertical[0][2] = 1;
		maskVertical[1][0] = 0;
		maskVertical[1][1] = 0;
		maskVertical[1][2] = 0;
		maskVertical[2][0] = -1;
		maskVertical[2][1] = -2;
		maskVertical[2][2] = -1;
		
		maskHorizontal[0][0] = 1;
		maskHorizontal[0][1] = 0;
		maskHorizontal[0][2] = -1;
		maskHorizontal[1][0] = 2;
		maskHorizontal[1][1] = 0;
		maskHorizontal[1][2] = -2;
		maskHorizontal[2][0] = 1;
		maskHorizontal[2][1] = 0;
		maskHorizontal[2][2] = -1;
		
		maskRightDiag[0][0] = 0;
		maskRightDiag[0][1] = 1;
		maskRightDiag[0][2] = 2;
		maskRightDiag[1][0] = -1;
		maskRightDiag[1][1] = 0;
		maskRightDiag[1][2] = 1;
		maskRightDiag[2][0] = -2;
		maskRightDiag[2][1] = -1;
		maskRightDiag[2][2] = 0;
		
		maskLeftDiag[0][0] = 2;
		maskLeftDiag[0][1] = 1;
		maskLeftDiag[0][2] = 0;
		maskLeftDiag[1][0] = 1;
		maskLeftDiag[1][1] = 0;
		maskLeftDiag[1][2] = -1;
		maskLeftDiag[2][0] = 0;
		maskLeftDiag[2][1] = -1;
		maskLeftDiag[2][2] = -2;	
	}//end contructor
	
	Initialize(int Rows, int Cols){
		Row=Rows;
		Col=Cols;
		SobelVertical = new int*[Rows];
		SobelHorizontal = new int*[Rows];
		SobelRightDiag = new int*[Rows];
		SobelLeftDiag = new int*[Rows];
		GradiantEdge = new int*[Rows];

		for(int i = 0; i <= Rows; ++i) {
			SobelVertical[i] = new int[Cols]();
			SobelHorizontal[i] = new int[Cols]();
			SobelRightDiag[i] = new int[Cols]();
			SobelLeftDiag[i] = new int[Cols]();
			GradiantEdge[i] = new int[Cols]();
		}//end for
	}//end initialize 
	
	int	convolute(int i, int j, int mask[3][3],int** zFramedAry){
		int Total=0;
		Total= zFramedAry[i-1][j-1] * mask[0][0] + zFramedAry[i-1][j] * mask[0][1] + zFramedAry[i-1][j+1] * mask[0][2]
			 + zFramedAry[i][j-1]   * mask[1][0] + zFramedAry[i][j]   * mask[1][1] + zFramedAry[i][j+1]   * mask[1][2]
			 + zFramedAry[i+1][j-1] * mask[2][0] + zFramedAry[i+1][j] * mask[2][1] + zFramedAry[i+1][j+1] * mask[2][2] ;
		return	Total;
	}//end convolute
	
	int	computeGradiant(int i, int j,int** zFramedAry){
		int G=sqrt( pow((zFramedAry[i][j] * zFramedAry[i+1][j]), 2)  + pow((zFramedAry[i][j] * zFramedAry[i][j+1]), 2) );	
		return 	G;
	} //end GRADIANT
	
	print(ofstream& V,ofstream& H, ofstream& R, ofstream& L,ofstream& G){
		
		FindMinMax(SobelVertical);
		V<<Row<<" "<<Col<<" "<<Min<<" "<<Max<<endl;
		FindMinMax(SobelHorizontal);
		H<<Row<<" "<<Col<<" "<<Min<<" "<<Max<<endl;
		FindMinMax(SobelRightDiag);
		R<<Row<<" "<<Col<<" "<<Min<<" "<<Max<<endl;
		FindMinMax(SobelLeftDiag);
		L<<Row<<" "<<Col<<" "<<Min<<" "<<Max<<endl;
		FindMinMax(GradiantEdge);
		G<<Row<<" "<<Col<<" "<<Min<<" "<<Max<<endl;
		
		for(int i=1; i <=Row; i++){
	 		for(int j=1; j<=Col; j++){
	 			V<<SobelVertical[i][j]<<" ";
	 			H<<SobelHorizontal[i][j]<<" ";
	 			R<<SobelRightDiag[i][j]<<" ";
	 			L<<SobelLeftDiag[i][j]<<" ";
	 			G<<GradiantEdge[i][j]<<" ";
	 		}//end j
	 			V<<endl;
	 			H<<endl;
	 			R<<endl;
	 			L<<endl;
	 			G<<endl;
	 	}//end i
	}//end print
	
	FindMinMax(int** Arry){
		for(int i=1; i<=Row; i++){
	 		for(int j=1; j<=Col; j++){
	 			if(Arry[i][j]>Max)
	 				Max=Arry[i][j];
	 			if(Arry[i][j]<Min)
	 				Min=Arry[i][j];
			}//i
		}//j
	}//End Find
};


class Image{
	int NumRow;
	int NumCol;
	int MinVal;
	int MaxVal;
	int** zeroFramedAry;
	
	ifstream data;
	ofstream output;//arg 2;
	ofstream output2;//arg 3;
	ofstream output3;//arg 4;
	ofstream output4;//arg 5;
	ofstream output5;//arg 6;
	
	Edge E;

	public: Image(string in, string out, string out2, string out3, string out4, string out5){
		data.open(in);// opens the imput file 
		output.open(out);
		output2.open(out2);
		output3.open(out3);
		output4.open(out4);
		output5.open(out5);

		data>>NumRow;//sets NumRows from input
		data>>NumCol;//sets NumCol from input
		data>>MinVal;//sets MinVal from input
		data>>MaxVal;//sets MaxVal from input
		E.Initialize(NumRow,NumCol);
		zeroFramedAry=new int*[NumRow+2];
		for(int i = 0; i <=NumRow+2; ++i) {
    		zeroFramedAry[i] = new int[NumCol+2];
		}//end for 
		zeroFrame();
		LoadImage();
		Scan();
	}//end chain code
	
	zeroFrame(){
	 	for(int i=0; i <=NumRow+1; i++){
	 		zeroFramedAry[i][0]=0;
			zeroFramedAry[i][NumCol+1]=0;
		}
	 	
		for(int j=0; j <=NumCol+1; j++){// framing top and bottom
		 	zeroFramedAry[0][j]=0;
			zeroFramedAry[NumRow+1][j]=0;
		}
	}//end frame
	 
	LoadImage(){
	 	for(int i=1; i <=NumRow; i++){
	 		for(int j=1; j<=NumCol; j++){
	 			data>>zeroFramedAry[i][j];
			 }//end j
	 	}//end i
	 	data.close();
	}//end load

	Scan(){
		for(int i=1; i <=NumRow; i++){
	 		for(int j=1; j<=NumCol; j++){
	 				E.SobelVertical[i][j] =   abs( E.convolute(i,j,E.maskVertical,zeroFramedAry));
					E.SobelHorizontal[i][j] = abs( E.convolute(i,j,E.maskHorizontal,zeroFramedAry));
					E.SobelRightDiag[i][j] =  abs( E.convolute(i,j,E.maskRightDiag,zeroFramedAry));
					E.SobelLeftDiag[i][j] =   abs( E.convolute(i,j,E.maskLeftDiag,zeroFramedAry));
		     		E.GradiantEdge[i][j] = E.computeGradiant(i,j,zeroFramedAry);
	 		}//end for j
	 	}//end for i 
	 	E.print(output,output2,output3,output4,output5);
	 	output.close();
	 	output2.close();
	 	output3.close();
	 	output4.close();
	 	output5.close();
	 }//end scan
	 				
};
int main(int argc, char** argv){
	if(argc<6){
		cout<<"Error must have 1 input file and 5 output files";
	}
	Image I(argv[1],argv[2],argv[3],argv[4],argv[5],argv[6]);
	return(0);
}
