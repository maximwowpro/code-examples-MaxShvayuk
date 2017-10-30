#include "laba4Tools.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <map>
#include <string>
#include <cstring>
using namespace std;

multimap<string, string> createLib()//create a library; key = author, value = title of book
{
	multimap<string, string> lib;
	return lib;
}

multimap<string, string> addBook(multimap<string, string> lib, string author, string title) // add a book to library
{
	lib.emplace(author, title);
	return lib;
}

multimap <string, string> deleteBook(multimap<string, string> lib, string author)//delete the book from library
{
	multimap <string, string> ::iterator it = lib.find(author);

	if (it == lib.end())//check for a book in library; if this condition is true - there isn`t book writen by this author in library
	{
		cout << "\n there isn`t book with " << author << " author in the library!\n";
	}
	else
	{
		int numBooks = lib.count(author);//number of books writen by author in library
		if (numBooks == 1)//if there is just 1 book in the library - delete it
		{
			lib.erase(it);
		}
		else//if there are several books - choose which of them do you want to delete?
		{
			cout << "\nThere are " << numBooks << " books, writen by " << author << " in the library:\n\n";
			
			for (int i = 0; i < numBooks; i++, it++)//a listing of all books; you can see number of each book
			{
				cout << i << " for\t "  << it->second << endl;
			}

			cout << "\nWhich of them do you want to delete? ";//choosing which book the program will delete
			int choose = 0;  
			cin >> choose;

			it = lib.find(author);
			for (int i = 0; i < choose; i++)//move our iterator on that book, which we will delete
			{	it++;    }

			lib.erase(it);//delete the selected book
			return lib;
		}
	}
	return lib;
}

int numAuthorBooks(multimap<string, string> lib, string author)//show a number of books, writen by selected author
{
	int counter = 0;//counter for number of books
	int countLoop = 0;//counter for number of iterrations of while() loops
	multimap<string, string> ::iterator it;

		while (counter == 0)//if we find the book in the library - we end the loop
		{
			if (countLoop != 0)//starts scan the author`s name from 2 iterration (if user choose this way)
				getline(cin, author);

			if (author != "skip")//if you enter author`s name - try find it in the library
			{
				
				for (it = lib.begin(); it != lib.end(); it++)//scan all books in library; if it searchs the name - counter ++; num boo
				{
					it->first == author ? counter++ : counter;//if it searchs the book with search authro  -  counter++
				}

				try//exception
				{
					if (counter == 0)//if we didn`t find the author in the library  -  throw 1
					{
						throw 1;
					}
					cout << "\nnumber of " << author << "`s books = " << counter << endl << endl;//if all is right (counter != 0) - do this
				}
				catch (int input)
				{
					cout << "\n\nThere aren`t any books with ''" << author << "'' author in the library\nPlease select what do you want to do:\n''skip'' = skip this stage\nother author`s name for search one more time\n";
				}
				countLoop++;//this counter we use to don`t scan author at the first iterration

				if (counter != 0)//if all is right (counter != 0) - do this
					return counter;//ends a function
			}
			else//if you enter "skip" - stop the "while" loop
			{
				cout << "\nsearching by author canceled\n";
				counter = 1;//to stop the "while" loop
				return 0;
			}
		}
}

pair<string, string> searchBookTitle(multimap<string, string> lib, string title)//search by a title of book
{
	int check = 1;//variable for checking on errors  
	int counter = 0;//just counter 
	pair <string, string> search;
	multimap <string, string> ::iterator it;
	
	while (check != 0)//repeat until not find a book with ''title'' value
	{
		if (counter != 0)//start scan the title from 2 itteration of while() loop
			getline(cin, title);

		if (title != "skip")
		{
			for (it = lib.begin(); it != lib.end(); it++)//check every book in the library
			{
				if (it->second == title)//condition for positive result
				{
					search.first = it->first;//if all is good write finded key and value in pair<> which func will return
					search.second = (*it).second;
					check = 0;// ''0'' = no mistakes
					cout << "\nthe author of  ''" << title << "''  is " << search.first << endl << endl;
				}
			}

			try//exception
			{
				if (check != 0)//if we didn`t find the book with ''title'' value
					throw 1;// mistake "there is not book with such "title"
			}
			catch (int input)
			{
				cout << "\nThere aren`t any books with ''" << title << "'' title!!!\nPlease select what do you want to do:\n''skip'' = skip this stage\nother title for search one more time\n";
			}
			counter++;//this counter we use to don`t scan title at the first iterration
		}
		else
		{
			cout << "\nsearching by title canceled\n";
			check = 0;//to stop "while" loop
		}
	}
	return search;
}

int printLib(multimap<string, string> lib)//print a library to a console
{
	multimap<string, string> ::iterator it = lib.begin();
	
	cout << "\nWatch your library :\n\n";
	for (it; it != lib.end(); it++)
	cout << it->first << setw( 25 - ( it->first.length() ) )<< ":\t" << (*it).second << endl;

	cout << endl;
	return 0;
}

int exportCSV(multimap<string, string> lib, ofstream& file)//export library to .csv file
{
	if (file.is_open() == 1)//if FILE was succesfully open
	{
		file << "Library by Max Shvayuk\n\nAuthor,Title\n";

		multimap<string, string> ::iterator it = lib.begin();
		for (it; it != lib.end(); it++)//write every book to the file
		{
			file << it->first << "," << (*it).second << "\n";
		}
		file.close();
		return 0;
	}
	else//if file wasn`t open
	{
		cout << "\ncan`t open the .csv file for export\n";
		file.close();
		return 1;
	}
}

multimap<string, string> importFromCSV(multimap<string, string> lib, ifstream & file)//import a library from .csv file
{
	if (file.is_open() == 1)//if file was succesfully open
	{
		string first, second;//first == author; second == title

		int i = 0;
		while (i < 3)//in this loop we skip first three lines,  where isn`t any useful information
		{
			getline(file, first, '\n');
			i++;
		}

		int a = -1;// '-1' - work with lib->first;   '1' - work with lib->second

		while ( !file.eof() )//until ! EOF
		{
			if (a == -1)//scan author
			{
				if (getline(file, first, ','))
					a = a*-1;	
			}

			if (a == 1)//scan title
			{
				if (getline(file, second, '\n'))
					a = a*-1;
			}

			lib.emplace(first, second);
		}
	}
	else//if file wasn`t open
	{
		cout << "\ncan`t open the .csv file for import\n";
	}

	file.close();
	return lib;
}

