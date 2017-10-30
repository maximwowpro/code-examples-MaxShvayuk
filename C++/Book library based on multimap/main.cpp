#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>//for sort() function
#include <map>
#include <string>
#include <vector>
#include"laba4Tools.h"

using namespace std;

int main(void)
{
	multimap <string, string> lib = createLib();
	string author[13] = { { "Jules Werne" },{ "Jules Werne" },{ "Jules Werne" },{ "Jules Werne" },{ "Jules Werne" },{ "Jules Werne" }, {"Mark Twen"}, {"Taras Shevchenko"}, {"Roman Svechnikov"}, {"Howard Lovecraft"},{ "Mark Twen" },{ "Mark Twen" }, { "Mark Twen" } },
		   title [13] = { { "Around the World in 80 Days1" },{ "Around the World in 80 Days2" },{ "Around the World in 80 Days3" },{ "Around the World in 80 Days4" },{ "Around the World in 80 Days5" },{"Around the World in 80 Days6"}, {"The Adventures of Tom Sawyer"}, {"Kobzar"}, {"Roma Yedet"}, {"Cthulhu"}, {"Adventures of Huckleberry Finn"}, {"The Gilded Age: A Tale of Today"}, {"A Connecticut Yankee in King Arthur's Court"} };
	for (int i = 0; i < 13; i++)
		lib = addBook(lib, author[i], title[i]);//fill the lib
	printLib(lib);

	//if you want check import library from .csv file - choose next code:
	//ifstream csvFileImport;
	//csvFileImport.open("CSV library import.csv");
	//multimap <string, string> lib = createLib();
	//lib = importFromCSV(lib, csvFileImport);//import a library from .csv file
	//printLib(lib);

	cout << "\ndelete book:\n\n";
	lib = deleteBook(lib, "Jules Werne");//delete a book use a key
	printLib(lib);

	cout << endl << endl;

	string name = "Howard Lovecraft";
	int numBooks = numAuthorBooks(lib, name);//number of books by key
	
	name = "qwerty";//checking on error in function   numAuthorBooks()
	numBooks = numAuthorBooks(lib, name);


	string title1 = "Around the World in 80 Days2";//search a book by title
	pair<string, string> book =  searchBookTitle(lib, title1);

	title1 = "QWERTY";//checking on error in function   searchBookTitle()
	book = searchBookTitle(lib, title1);

	ofstream csvFileExport;
	csvFileExport.open("multimap library.csv");
	exportCSV(lib, csvFileExport);//export a library to .csv file

	system("pause");
	return 0;
}