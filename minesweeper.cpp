/*
* Assumptions:
* 1. User will enter a valid indice
*/

#include <iostream>
#include <stdlib.h>

using namespace std;

#define ROWSIZE 5
#define COLSIZE 5

int arr[ROWSIZE][COLSIZE] = { {0,0,0,0,0},//define array
		      {0,1,1,1,0},
		      {0,1,1,1,0},
		      {0,0,1,0,1},
		      {0,0,1,0,0} };

/*
* Takes a user index and checks to see if 1.
* If 1 changes to 0 and checks indices to 
* the right,left,above,and below for 1's -- repeat.
*/
void mine(int row1, int col1) {

	//base case arr[row1][col1] == 0

	if(arr[row1][col1] == 1) {//check to see if 1
		
		arr[row1][col1] = 0; //set to zero

		if(row1 + 1  < ROWSIZE) mine(row1+1,col1);//check to see if there will be bound errors
					 	          //check position below 
		if(row1 - 1  >= 0) mine(row1-1,col1); //checks position above	 

		if(col1 + 1  < COLSIZE) mine(row1,col1+1); //check position to the right	
		
		if(col1 - 1  >= 0) mine(row1,col1-1); //check position to the left 

	} 

}//end mine

/*
*prints array arr to console
*/
void printArray() {

	for(int i = 0; i < ROWSIZE; i++) {//cycle rows

		for( int j = 0; j < COLSIZE; j++) {//cycle cols.

			cout<< arr[i][j]<<' ';

		}

		cout<<endl;

	}

}//end printArray



int main() {

int userR,userC;

cout<<"Please enter a row indice: ";//get user's row and col.
cin>>userR;
cout<<"Please enter a column indice: ";
cin>>userC;
cout<<endl;


cout<<"Before: "<<endl;

printArray();

cout<<"After: "<<endl;

mine(userR,userC);//tests mine function

printArray();


}//end main
