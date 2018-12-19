#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0 
#define maxHexLenght 8

int decimal = 0;
bool Error;
char hexNum[] = "ffffffff";

/****************************************************************************************************************
* This function gets a decimal value from a hex input. L.S 06-12-18.
*****************************************************************************************************************/
int getHexVal(char hexArray[])
	{

	int base = 1;
	int hexLength = 0;
	int i;
	decimal = 0;
	
	while (hexArray[i] != 0)
	{
		hexLength++;
		i++;
	}
		if (hexLength >= maxHexLenght)
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
int main(int argc, char const *argv[])
{

getHexVal(hexNum);
printf("The hex number is %s - decimal value is %d\n", hexNum, decimal );

return 0;
}

