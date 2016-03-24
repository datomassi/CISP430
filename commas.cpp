#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct node{
	char data;
	node* next;
}node;

//#define size 

void printCharPtr(char* n) { 

	for(; *(n) !='\0';n++) {

		cout<<*n;


	}
	cout<<endl;

}//end printChar

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

char pop(node*& head) {

	char data = head->data;
	
	node* tmp = head;

	head = head->next;

	delete(tmp);

	return data;

}//end pop

int stringLength(char *a) {

    int counter = 0;
//MAKE APP. VALUE FOR i<
    for(int i = 0;i < 15; i++) {

        if(*(a+i) !='\0') {//looks for null terminator

            counter++;    

        } else break;        

    }//end loop
return counter;
}//end stringLength



char* longToChar(long long num,node*& stack) {

	char* lToC = (char*)malloc(sizeof(num));
	
	char* temp = lToC;

	int m = 10;
	int n = 1;

	while(n < num) {

		long long tmpNum = num;
	
		char tmp;

		tmpNum = tmpNum % m;

		tmpNum = tmpNum / n;

		tmp = tmpNum + '0';
//cout<<tmp<<endl;
		push(stack,tmp);

		m = m *10;
		n = n *10;

	}

	while(stack) {

		*temp = pop(stack);
//cout<<*temp<<endl;
		temp++; 

	}

	
	return lToC;

}//end longToChar


char* shiftAndPlace(char* list, int length, int shift) {

	for(int i = length; i >= 0; i--) {//counting down to shift values 

		*(list+i+shift) = *(list+i);    

	}//end loop

	return list;

}//end shiftAndPlace


long long highestPlace(long long num) {

	long long higher = 1;

	while(higher < num) {

		higher = higher * 10;
		

	}

	return higher;

}//end highestPlace

bool isZeroNext(char* num,int offset) {

	char* tmp = num;
	
	return *(tmp+offset) == '0';


}//end isZeroNext


/*
*
*/
char* putCommas(long long n) {

	char* withCommas = (char*)malloc(100);

	node* head = NULL;

	char* tmp = longToChar(n,head);

	bool isNextZero = isZeroNext(tmp,1);
cout<< "isNextZero: " << isNextZero<<endl;	
	int numOfZeros;

	if(isNextZero) {


		numOfZeros = 1;

		int index = 2;


		while(isZeroNext(tmp,index)) {
			index++;
			numOfZeros++;

		}

//cout<< "numofzeros: " << numOfZeros<<endl;

	}//end if


	if(n < 10) {

		*withCommas = (int)n  + '0';


		return withCommas;

	} else {
	
		withCommas = putCommas(n % (highestPlace(n)/10));
		 
		int length = stringLength(withCommas);
//printCharPtr(withCommas);


		if(isNextZero) { 

			for(int i = 0; i < numOfZeros; i++) {
			
				if( length == 3 || length == 7 || length == 11 ) {

					withCommas = shiftAndPlace(withCommas, length, 3);

					*(withCommas+2) = ',';//add comma
					*(withCommas+1) = '0';//add zero

				} else if(length+1 == 3 || length +1 == 7 || length +1 == 11) {

					withCommas = shiftAndPlace(withCommas, length, 3);

					*(withCommas+2) = '0';//add comma
					*(withCommas+1) = ',';//add zero
			

				} else {
		
					withCommas = shiftAndPlace(withCommas, length, 2);
	
					*(withCommas+1) = '0';//add zero

				}

			

				length = stringLength(withCommas);

			}//end for			

		} else {

			if( length == 3 || length == 7 || length == 11 ) {


				withCommas = shiftAndPlace(withCommas, length, 2);

				*(withCommas+1) = ',';//add comma
			} else {

				withCommas = shiftAndPlace(withCommas, length, 1);

			}			



		}


	*withCommas = (int)(n/(highestPlace(n)/10))  + '0';

	return withCommas;//add isolated place value

	}
	
	
	



}//end putCommas


void printChar(char* n) { 

	for(; *(n) !='\0';n++) {

		cout<<*n;


	}
	cout<<endl;

}//end printChar


int main() {

	node* stack = NULL;

 	long long userNum;

	
//cout<<sizeof(test);
	cout<< "Please enter number: ";

	cin>>userNum;
//cout<< sizeof(userNum)<<endl;

	//char* num = longToChar(userNum,stack);
//cout<<sizeof(num)<<endl;
	char* num = putCommas(userNum);	
//cout<<"length: "<<stringLength(num)<<endl;

	

	for(; *(num) !='\0';num++) {

		cout<<*num;


	}
	cout<<endl;
}//end main
