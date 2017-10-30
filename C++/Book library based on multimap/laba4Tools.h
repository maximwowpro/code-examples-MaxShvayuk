#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;


multimap <string, string> createLib();//create a library; key = author, value = title of book

multimap<string, string> addBook(multimap<string, string> lib, string author, string title);//add a book to library

multimap <string, string> deleteBook(multimap<string, string> lib, string author);//delete the book from library

int numAuthorBooks(multimap<string, string>, string author);//show a number of books, writen by selected author

pair<string, string> searchBookTitle(multimap<string, string> lib, string title);//search by a title of book

int printLib(multimap<string, string> lib);//print a library to a console

int exportCSV(multimap<string, string> lib, ofstream& file);//export library to .csv file

multimap<string, string> importFromCSV(multimap<string, string> lib, ifstream& file);//import a library from .csv file





