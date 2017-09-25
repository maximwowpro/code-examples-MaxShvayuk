/*A quadrilateral consisting of 4 points. Each point is given two-dimensional
coordinates.
Realize the function to calculate the area.
Provide a function that creates a structure by input and adds it to an array of relevant structures.
Realize a function? which create a .json file and write array of squares there.
*/

#include <stdio.h>
#include "area_tools.h"

int main(void)
{ 
	kvadrat();//printf an image of Square
	FILE *jsonn = fopen("jsonn.json", "w+");//create a .JSON file
	
	SquareArray *ANarray = create_square_array(10);
	Square ANsquare;
		
	addSquareToList(ANarray, &ANsquare);
	addSquareToList(ANarray, &ANsquare);
	
	int i=0;
	for(i;i<2;i++)
	{
		int j=0;//counter for loop
		for(j;j<4;j++)
		{			
			printf("\nkvadrat:%i ; point[%i].x = % .1f", (i), j, (ANarray->array[i].points[j].x));
			printf("\nkvadrat:%i ; point[%i].y = % .1f", i, j, (ANarray->array[i].points[j].y));

		}
		
		
	}
	area_square(ANarray);//count an AREA for each Square
	printf("\n\n\n");
	json_write( jsonn, ANarray);	
}


