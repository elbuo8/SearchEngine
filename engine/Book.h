//
//  Book.h
//  
//
//  Created by Yamil Asusta on 10/29/12.
//
//

#ifndef ____Book__
#define ____Book__

#include <iostream>
#include <string>


using namespace std;

class Book {
private:
    string Title;
    int repetitions;
    
public:
	Book(const string& title);
    Book(const string& title, const int& repetitions);
	void increase();
    int getRepetitions() const;
    string getTitle() const;
};

bool bookSort(const Book& book1, const Book& book2);

#endif /* defined(____Book__) */
