#include <stdio.h>
#include "area_tools.h"
#include "sort_tools.h"

int main(void)
{ 
	FILE *jsonn = fopen("jsonn.json", "w+");//create a .JSON file
	kvadrat();//printf an image of square
			
	SquareArray *ANarray = create_square_array(15);
	Square ANsquare;	

	addSeveralSquaresToList(ANarray, &ANsquare);
	
	area_square(ANarray);//count an AREA for each Square	
	
	chooseTheKindOfSort(ANarray);
	
	writeSquareArrayInConsole(ANarray);//write an ARRAY of Squares in console
	json_write( jsonn, ANarray);// write ARRAY into .json file

	destroySquareArray(ANarray);
}


