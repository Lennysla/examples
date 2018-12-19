/* 
Program: replyComparator.c
Developer : Leonard Slattery
Date: 12/12/18

Functionality: 
The purpose of this program is to take in a reply and scan a text to query if a know string is in there. 
There are some specifiers in here to help with this -

$ - Search the entire string for a reply. This takes a char array input and sees if this is located anywhere contiguolsly in the string.
* - Search the string for a spcific contiguos string until a specific character is found. 
? - Search for a known hex digit in a string.
@ - Search for an unknown hex digit in a frame at a specific point in the array. Return the found hex digit.    
> - jump - Jump N places into the string and compare the returned string to the string at that position. 

compareReply takes 6 arguements the specifier, the full string, the test string, the jump number, the frame number, stop character.
  
****************************************************************************************************************
Date:
Developer:
Issue:
Fix: 
****************************************************** < > ***************************************************** 
*/ 

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef int bool;
#define true 1
#define false 0 
#define maxHexLength 8 		

bool match = false;
bool hexMatch = false;
bool Error;

unsigned char *p;   		// Declare p as a pointer variable of type char. p is our reply string.
unsigned char *q;			// Declare q as a pointer variable of type char. q is our test string.
unsigned char *t;			// Declare t as a pointer variable of type char. t is a replica of q.
unsigned char *r;			// Declare r as a pointer variable of type char. t is a replica of p.
unsigned char L;
char *specifier;			// Our specifier to what case we want to invoke. 
int jump;					// An integer so we can jump into the string by this amount. 
int count;
int i = 0;					// An increment integer. 
int decimal = 0;			// Return value for getHexVal.
int x = 0;
int y = 0;
char hexNum[maxHexLength];	// Initialise the hexNum. 
char builtHexNum[maxHexLength];

/****************************************************************************************************************
* This function gets a decimal value from a hex input. A maximum of 8 chard in the hex array. L.S 06-12-18.
*****************************************************************************************************************/
int getHexVal(char hexArray[])
	{
	int base = 1;
	int hexLength = 0;
	int i = 0;
	decimal = 0;
	while (hexArray[i])                	// While the element of hexArray is not equal to NULL 
	{
		hexLength++;					// Increment through the array
		i++;							// Count up the steps.
	}
		if (hexLength > maxHexLength)	// Check to see if the hex number is too long
		{
			printf("That Hex number is too long %s\n", hexNum );
			exit(0);
		}
		for (i = hexLength-1; i >= 0; i--)
		{
			if (hexArray[i] >= '0' && hexArray[i] <= '9')
			{
				decimal+= (hexArray[i] - 48) * base;
				base = base * 16;
			}
			else if (hexArray[i] >= 'A' && hexArray[i] <= 'F')
			{
				decimal+= (hexArray[i] - 55) * base;
				base = base * 16;
			}
			else if (hexArray[i] >= 'a' && hexArray[i] <= 'f')
			{
				decimal+= (hexArray[i] - 87) * base;
				base = base * 16;
			}
			else
			{
				Error = true;
			 	printf("%s is not a valid hex number\n", hexNum);
			 	exit(0); 	
			}
		}
	return(decimal);
	}
/****************************************************************************************************************
* This function gets contiguos string of characters in a long string. L.S 06-12-18.
*****************************************************************************************************************/
unsigned char *compareReply(char *specifier, unsigned char *p, unsigned char *q, int jump, int count, unsigned char L)
{
	t = q; 
	r = p;
	i = 0;                                 	 //assign address of q to address of t as if not a match we can point back
	while(*p){
		switch(*specifier)
			{ 
			case '$':                        // Search string for test string in enitre string.						  							
				while (*p){      
				//*** DEBUG *** printf("String element %c \n", *p );
					if (*p == *q && *q)		  // If the value of p == q and the value of q is not NULL execute this bit.
						{ 
						p++;				  // Increment the tested pointer 
						q++;				  // Increment the testing pointer
						i = 0;
						}

					else if(*p != *q && *q)	  // If the value of p == q and the value of q is not NULL execute this bit.
						{ 
						q = t;				  // Reset pointer to start of test string. 	
						if(*q == *p)continue; // Skips the increment if first test letter is a match to the reset pointer.
						p++; 				  // Increment the tested pointer 
						}

					if (!*q)				  // If we have reached the end of the testing pointer we have a match. We can return.
						{
						printf("$ Match found WOHOO   :-)\n");
						match = true;
						return(0);
							}
					}

				printf("\n");
				printf("No match found :-(\n");
				break;


			case '*' :                        // Search string for test string until @ character is found.
				while (*p != L){      	 	  // Break out of the loop if a specific character is found.
					if (*p == *q && *q)		  // If the value of p == q and the value of q is not NULL execute this bit.
						{ 
						p++;				  // Increment the tested pointer 
						q++;				  // Increment the testing pointer
						i = 0;
						}

					else if(*p != *q && *q)	  // If the value of p == q and the value of q is not NULL execute this bit.
						{ 
						q = t;				  // Reset pointer to start of test string. 	
						if(*q == *p)continue; // Skips the increment if first test letter is a match to the reset pointer.
						p++; 				  // Increment the tested pointer 
						}

					if (!*q)				  // If we have reached the end of the testing pointer we have a match. We can return.
						{
						printf("* Match found WOHOO   :-)\n");
						match = true;
						return(0);
							}
					}

				printf("\n");
				printf("No match found before %c :-(\n", L);
				break;


			case '?' :                  	// Search for hexNum case. 
			p += jump;	
			i = 0;					  		// Set the address of p to p plus the jump number. 

				while 		 (('0' <= *p && *p <= '9')|| // Test the value of p to see if its between 0 - 9.
					  		  ('a' <= *p && *p <= 'f')|| // Test the value of p to see if its between a - f.
							  ('A' <= *p && *p <= 'F')){ // Test the value of p to see if its between A - F.

					if (*p == *q && *q)       // If the value of p == q and the value of q is not NULL.
						{ 
						p++;
						q++;
						}

					else if(*p != *q && *q)
						{ 
						q = t;				  // Reset pointer to start of test string. 	
						if(*q == *p)continue; // Skips the increment if first test letter is a match to the reset pointer.
						p++;
						}

					if (!*q)				  // If we have reached the end of the testing pointer we have a match. We can return.
						{
						printf("? Match found WOHOO   :-)\n");
						hexMatch = true;
						return(builtHexNum);
							}
						}
					printf("\n");
					printf("No match found :-(\n");
				break;


			case '>' : //Jump case 
				p += jump;
				t = q;
				x = 0;
				while (*p && x < count){      	 // While the value of p is not null & x is less than count . 
					if (*p == *q && *q)			 // If the value of p == q and the value of q is not NULL execute this bit.
						{ 
						p++;
						q++;
						x++;
						}

					else if(*p != *q && *q)
						{ 
						q = t;				      // Reset pointer to start of test string. 	
						if(*q == *p)continue;     // Skips the increment if first test letter is a match to the reset pointer.
						p++;
						x++;
						}

					if (!*q)		
						{
						printf("> Match found WOHOO   :-)\n");
						match = true;
						return(0);
							}
					}

				printf("\n");
				printf("No match found :-(\n");
				break;


			case '@' :   // Search for unknown hex string at a specific point in a specific frame. 	
				p += jump;	
				i = 0; 					  // Set the address of p to p plus the jump number. 

				while  (('0' <= *p && *p <= '9')|| // Test the value of p to see if its between 0 - 9.
			    		('a' <= *p && *p <= 'f')|| // Test the value of p to see if its between a - f.
			            ('A' <= *p && *p <= 'F')){ // Test the value of p to see if its between A - F.

					if (i >= count){
						hexMatch = true;
						printf("@ Hex digit found!!   :-)\n");
						break;
					}

					builtHexNum[i] = *p;      	// Index i of builtHexNum is = to the value of what is at address p. 
					i++;						// Increment index variable.
					p++;						// Increment along the testing array. 
				}
			
				return (builtHexNum);	
				break;

			default :
			printf("That is not a recognoised command\n");
			break;

		}
		q = t; 
	    p = r;

		return(0);
	}	
}


// ***********************************************  MAIN  ***************************************************  

int main(int argc, char const *argv[])
{

unsigned char *reply = "trge£$%%^&*()_+=<>?~:}{leo0x56;7 8e553faa99cddd ul 789'ee#{le*LEOnArD7}[]oh nar@l9xjfhbg!de";
unsigned char *reply1 = "hhhhhhhef!""£$%^&*()_-+=f99fyyyyygftddhdfdwhfjhlk";
char hexNum [] = "3faa99c";
unsigned char *test = "LEOnArD";

compareReply("$", reply, test,     0,0,0);  // Search the entire string for a known contiguos sub string.
compareReply("?", reply, hexNum,  37,0,0);  // Search for HEX chars only at a specific point.
compareReply("*", reply, test,   0,0,'!');  // Search for a comparison until a specific char is found. 
compareReply(">", reply, test,    63,8,0);  // Jump to a specific point 60 chars in and test, if no FULL 'match before 8 increments return no match found.
compareReply("@", reply, 0,       37,8,0);  // Search for HEX chars only at a specific point.

printf("\n");

if(hexMatch) {
	getHexVal(builtHexNum);
	printf("Hex number found is %s - The decimal value is %d\n", builtHexNum, decimal );
}

printf("\n");

return 0;
}

