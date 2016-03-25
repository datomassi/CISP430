/* 
* Assumptions:
* 1. All user input is:
*  a. valid
*  b. no greater in length than 10 digits
*  c. positive values
*  d. less than the maximum of a signed long(2,147,483,647)
*/

#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct node{
	char data;
	node* next;
}node;

/*
* Stack operation: push
*/
void push(node*& head,char item) {

	node* newNode = new node;
	newNode->data = item;
	

	if(head) {
		newNode->next = head;
		head = newNode;

	} else {

		head = newNode;
		head->next = NULL;

	}


}//end push

/*
* Stack operation: pop
*/
char pop(node*& head) {

	char data = head->data;
	
	node* tmp = head;

	head = head->next;

	delete(tmp);

	return data;

}//end pop

/*
* prints char* to console
*/
void printCharPtr(char* n) { 

	for(; *(n) !='\0';n++) {//goes through and prints each el.
				// stops at null terminator
		cout<<*n;


	}
	cout<<endl;

}//end printChar

/*
* returns length of char*
*/
int stringLength(char *a) {

    int counter = 0;

    for(int i = 0;i < 15; i++) {//goes through whole char*

        if(*(a+i) !='\0') {//looks for null terminator

            counter++;//increment counter if not null term.

        } else break;        

    }//end loop

	return counter;

}//end stringLength

/*
* converts a long to a char*
*/
char* longToChar(long num,node*& stack) {

	char* lToC = (char*)malloc(sizeof(num));//allocate mem
	
	char* temp = lToC; //hold address and used to manipulate

	int m = 10;//coeffiecents used to find isolate individual places
	int n = 1;

	while(n < num) {//parse each place and put onto stack

		long tmpNum = num;
	
		char tmp;

		tmpNum = tmpNum % m;

		tmpNum = tmpNum / n;

		tmp = tmpNum + '0';//convert to char

		push(stack,tmp);

		m = m *10;
		n = n *10;

	}

	while(stack) {//pop stack and return

		*temp = pop(stack);

		temp++; 

	}

	return lToC;

}//end longToChar

/*
* shifts char* by param. shift
*/
char* shift(char* list, int length, int shift) {

	for(int i = length; i >= 0; i--) {//counting down to shift values 

		*(list+i+shift) = *(list+i);    

	}//end loop

	return list;

}//end shift

/*
* returns the place higher than the number in param.
* ex num = 1234 -> return = 10000
*/

long highestPlace(long num) {

	long higher = 1;

	while(higher < num) {

		higher = higher * 10;
		
	}

	return higher;

}//end highestPlace

/*
* checks to see if el. with param. offset
* is '0'
*/
bool isZeroNext(char* num,int offset) {

	char* tmp = num;
	
	return *(tmp+offset) == '0';


}//end isZeroNext


/*
* puts commas in proper places for param. n
*/
char* putCommas(long n) {

	char* withCommas = (char*)malloc(100);//allocate memory

	node* head = NULL;//stack for checking if zeros are next and how many

	char* tmp = longToChar(n,head);//converts n to a char*

	bool isNextZero = isZeroNext(tmp,1);//checks to see if next place is a 0
	
	int numOfZeros = 0;

	if(isNextZero) {//counts how many zeros in a row

		numOfZeros = 1;

		int index = 2;

		while(isZeroNext(tmp,index)) {
			index++;
			numOfZeros++;

		}

	}//end if


	if(n < 10) {//base case

		if(n != 0) *withCommas = (int)n  + '0';//zeros will be handled in previous call

		return withCommas;

	} else {
	
		withCommas = putCommas(n % (highestPlace(n)/10));//chop off highest place
		 
		int length = stringLength(withCommas);//get length of returned withCommas

		if(isNextZero) { //accounts for zeros

			for(int i = 0; i < numOfZeros; i++) {
										//check lengths where commas are appropriate
				if( length == 3 || length == 7 || length == 11 ) {//checks to see if commas should go 1st

					withCommas = shift(withCommas, length, 2);

					*(withCommas+1) = ',';//add comma
					*(withCommas) = '0';//add zero

				} else if(length+1 == 3 || length +1 == 7 || length +1 == 11) {//checks to see if commas should go 2nd

					withCommas = shift(withCommas, length, 2);

					*(withCommas+1) = '0';//add zero
					*(withCommas) = ',';//add comma
			

				} else {
		
					withCommas = shift(withCommas, length, 1);
	
					*(withCommas) = '0';//add zero
					
				}

				length = stringLength(withCommas);//recalulate length to account for additions

			}//end for

			withCommas = shift(withCommas, length, 1);//shift by 1 to make room for #	

			if((int)(n/(highestPlace(n)/10)) == 10) *withCommas = 1 + '0';//correcting for error with 0's where it would be 10 instead of 1
			
			else *withCommas = (int)(n/(highestPlace(n)/10))  + '0';//add # to withCommas

		} else {

			if( length == 3 || length == 7 || length == 11 ) {//check lengths where commas are appropriate

				withCommas = shift(withCommas, length, 2);

				*(withCommas+1) = ',';//add comma
								
			} else {

				withCommas = shift(withCommas, length, 1);
				
			}			

			if((int)(n/(highestPlace(n)/10)) == 10) *withCommas = 1 + '0';//correcting for error with 0's where it would be 10 instead of 1
			
			else *withCommas = (int)(n/(highestPlace(n)/10))  + '0';//add # to withCommas

		}

	return withCommas;//add isolated place value

	}
	
}//end putCommas

int main() {

	long userNum;

	cout<< "Please enter number: ";//prompt for user input

	cin>>userNum;//catch user input

	printCharPtr(putCommas(userNum));//print results of putCommas

}//end main
