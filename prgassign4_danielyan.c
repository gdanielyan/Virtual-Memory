/*
Student : Georgiy Danielyan
Professor : George Lazik
Programming Assingment 4 : Virutal Address Mapping
Due : Monday November 30th 2015 @ 11PM
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*********************
Function Prototypes
*********************/
void displayMenu();
void setParameters();
void mapVirtualAddress();

/*********************
Variable Declarations
*********************/
char ESC = 27;       //Used for bold printing of messages
int mainMemorySize;  //Size of main memory size
int pageSize;        //Size of page/frame size
int replacementType; //Type of replacement algorithm

/*********************
Main Method
*********************/
int main(){
	int choice;
	do{
      //reset the choice before getting new input.
		choice = 0;
		displayMenu();
		scanf("%d", &choice);
		switch(choice){
			case 1:
            setParameters();
				break;
			case 2:
            mapVirtualAddress();
				break;
			case 3: 
            //Free any allocated memory

				exit(0);
				break;
			default:
				printf("Invalid selection\n\n");
				//Clear the input stream in case of extraneous inputs.
				while ((choice = getchar()) != '\n' && choice != EOF);
				break;
		}

	}while(choice != 3);
	return 0;
}

/*********************
Function Declarations
*********************/

/*
@return none
display the menu to the user
*/
void displayMenu(){
	printf("\nGeorgiy Danielyan\n");
	printf("Virtual Address Mapping\n");
	printf("-----------------------\n");
	printf("1) Set Parameters\n");
	printf("2) Map Virtual Address\n");
	printf("3) Quit Program\n");
	printf("Enter Selection\n");
}

/*
@return none
get the parameters from the user
*/
void setParameters(){
   printf("Enter main memory size (words): ");
   scanf("%d", &mainMemorySize);
   printf("Enter page size (words/page): ");
   scanf("%d", &pageSize);
   printf("Enter replacement policy (0=LRU, 1=FIFO): ");
   scanf("%d", &replacementType);

   /*- turn on bold */
   printf("%c[1m",ESC);

   /* turn off bold */
   printf("%c[0m",ESC);

}

/*
@return none
display the physical address
*/
void mapVirtualAddress(){
   /*- turn on bold */
   printf("%c[1m",ESC);

   /* turn off bold */
   printf("%c[0m",ESC);

}