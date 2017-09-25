#include "area_tools.h"
#include <math.h>
#include "sort_tools.h"


SquareArray *create_square_array(int Asize)//create an ARRAY of Squares
{
	SquareArray *masiv = malloc(sizeof(SquareArray)*Asize);
	
	if(NULL != masiv)
	{
		masiv->array = (Square*)malloc(sizeof(Square)*Asize);
				
		masiv->size = Asize;
		masiv->current_size =  0;
	}
	
	return masiv;
}

void destroySquareArray(SquareArray *aList)//destroy an ARRAY of Squares
{
	if(NULL != aList)
	{
		if (NULL != aList->array)
		{
			int i = 0;
			for(i; i<aList->current_size; i++)
			{
				Square theSquare = aList->array[i];
				if(NULL != theSquare.points)
				{
					free(theSquare.points);
				}
			}
		}
		free(aList);
	}
}


int addSquareToList(SquareArray *aList, Square *aSquare, int MaxValueOfCoordinates)// add a Square to ARRAY
{
	int the_return = 0;
	
	if(aList!= NULL && aSquare!=NULL)
	{
		if(aList->current_size < aList->size)
		{
			Square *figure = &(aList->array[aList->current_size]);

			int i=0;
			for(i;i<4;i++)
			{
				figure->points[i].x =rand()%MaxValueOfCoordinates;
				
				figure->points[i].y =rand()%MaxValueOfCoordinates; 

			}

			aList->current_size++;
		}
		else
		{
			the_return = -2;
		}
	}
	else
	{
		the_return = -1;
	}
	return the_return;	
}

void addSeveralSquaresToList(SquareArray *aList, Square *aSquare)// add several Squares into ARRAY using funk addSquareToList
{
	printf("\n how many SQUARES are there in array (min = 1, max = 15)? = ");
	int quantity = scan(1, 15);
	
	printf("\ngive me the MAX value of coordinate [-1000; 1000] = ");
	int MaxValueOfCoordinates = scan(-1000, 1000);
	
	int i = 0;
	for(i;i<quantity; i++)
	{
		addSquareToList(aList, &aSquare, MaxValueOfCoordinates);

	}
}


float area_square(SquareArray *ANarray)//calculate an area of Square
{
	int rozmir = ANarray->size;
	int i=0;//counter for loop
	for(i;i<rozmir;i++)
	{
		float A_x = ANarray->array[i].points[0].x;// it is more comfortable to make a calculations
		float A_y = ANarray->array[i].points[0].y;
		float B_x = ANarray->array[i].points[1].x;
		float B_y = ANarray->array[i].points[1].y;
		float C_x = ANarray->array[i].points[2].x;
		float C_y = ANarray->array[i].points[2].y;
		float D_x = ANarray->array[i].points[3].x;
		float D_y = ANarray->array[i].points[3].y;
		
		float AC, BD;//variables for lenght of diagonals 
		
		AC = sqrt((C_x - A_x)*(C_x - A_x) + (C_y - A_y)*(C_y - A_y));
		
		BD = sqrt((D_x - B_x)*(D_x - B_x) + (D_y - B_y)*(D_y - B_y));
		
		struct dot vektor_ac;//create VEKTORS     ac     and    bd
		struct dot vektor_bd;
		
		vektor_ac.x = (C_x - A_x);//first coordinate of vektor ac
		vektor_ac.y = (C_y - A_y);//second coordinate of vektor ac
	 
	 	vektor_bd.x = (D_x - B_x);//first coordinate of vektor bd
		vektor_bd.y = (D_y - B_y);//second coordinate of vektor bd
	 	
	 	
		float ac_bd;//count the scalar derivative (dobutok) of vektors 		ac 		and 		bd
		ac_bd = ( (vektor_ac.x * vektor_bd.x) + (	vektor_ac.y * 	vektor_bd.y) );
		
		float cos_a;//cosinus  of wanted angle (ugol)
		cos_a = ac_bd/(AC*BD);
		
		float S;//variable for area
		S = (AC * BD) / (2 * cos_a);
		
		ANarray->array[i].area = S;
		
	}
}

void json_write( FILE *file, SquareArray *aList)
{
	int aSize = aList->size;
	int curr_size = aList->current_size;
	
	fprintf(file, "{\n\t\"size\" : %i,\n\t\"current_size\" : %i,\n\t\"array\" : [", aSize,curr_size);
	
	int i = 0;
	for(i;i<curr_size;i++)
	{
		fprintf(file, "\n\t\t{\n\t\t\"points\" : [");
		//A
		fprintf(file, "\n\t\t\t{\n\t\t\t\t\"X\" : % .2f,\n\t\t\t\t\"Y\" : % .2f\n\t\t\t},",(aList->array[i].points[0].x) , (aList->array[i].points[0].y) );
		//B
		fprintf(file, "\n\t\t\t\t{\n\t\t\t\t\"X\" : % .2f,\n\t\t\t\t\"Y\" : % .2f\n\t\t\t},",(aList->array[i].points[1].x) , (aList->array[i].points[1].y) );
		//C
		fprintf(file, "\n\t\t\t\t{\n\t\t\t\t\"X\" : % .2f,\n\t\t\t\t\"Y\" : % .2f\n\t\t\t},",(aList->array[i].points[2].x) , (aList->array[i].points[2].y) );
		//D
		fprintf(file, "\n\t\t\t\t{\n\t\t\t\t\"X\" : % .2f,\n\t\t\t\t\"Y\" : % .2f\n\t\t\t},",(aList->array[i].points[3].x) , (aList->array[i].points[3].y) );
		
		fprintf(file, "\n\t\t]\n\t\t\t\t\"area\" : % .2f\n\t\t},", (aList->array[i].area));
	}
	
	fflush(file);
	fclose(file);
}	

void writeSquareArrayInConsole(SquareArray *aList)//write an ARRAY of Squares in console
{
	int aSize = aList->size;
	int curr_size = aList->current_size;
	
	printf("{\n\n\t\"size\" : %i,\n\t\"current_size\" : %i,\n\t\"array\" : [", aSize,curr_size);
	
	int i = 0;
	for(i;i<curr_size;i++)
	{
		printf( "\n\t\t{\n\t\t\"points\" : [");
		//A
		printf( "\n\t\t\t{\n\t\t\t\t\"X\" : % .2f,\n\t\t\t\t\"Y\" : % .2f\n\t\t\t},",(aList->array[i].points[0].x) , (aList->array[i].points[0].y) );
		//B
		printf( "\n\t\t\t\t{\n\t\t\t\t\"X\" : % .2f,\n\t\t\t\t\"Y\" : % .2f\n\t\t\t},",(aList->array[i].points[1].x) , (aList->array[i].points[1].y) );
		//C
		printf( "\n\t\t\t\t{\n\t\t\t\t\"X\" : % .2f,\n\t\t\t\t\"Y\" : % .2f\n\t\t\t},",(aList->array[i].points[2].x) , (aList->array[i].points[2].y) );
		//D
		printf( "\n\t\t\t\t{\n\t\t\t\t\"X\" : % .2f,\n\t\t\t\t\"Y\" : % .2f\n\t\t\t},",(aList->array[i].points[3].x) , (aList->array[i].points[3].y) );
		
		printf( "\n\t\t]\n\t\t\t\t\"area\" : % .2f\n\t\t},", (aList->array[i].area));
	}
	
}

	
float scan(int min, int max)// just scanf with checking on idiot
{
	
	float buffer;// variable for saving that what we scanned
	int q;// variable for checking on idiot
	do
	{
	q = scanf("%f", &buffer);
	
	fflush(stdin);// without this it willn't work correctly
	
	if((buffer<min || buffer>max) || q!=1)
	{
		printf("\ngive me the correct number pls!\n");	
	}		
	
	}
	
	while ((buffer<min || buffer>max) || q!=1);
	
	return buffer;	

}

int printTextFromFile (FILE *aFile)//print text from file into a console and return lenght of file
	{
		char letter ;
		int lenght = 0;// lenght of text
		while (letter != EOF)
		{
			letter= fgetc(aFile);
			printf("%c", letter);
			lenght++;			
		}
		return lenght;
	}
 
 void kvadrat()
 {
	//print an image of square
	
	printf("this is how your square look like: \n\n");
	printf("B___________________C\n");
	int i;
	for(i = 0; i<7; i++)
	{
		printf("|                   |\n");
	}
	printf("A___________________D\n\n");
 
 
}
 

