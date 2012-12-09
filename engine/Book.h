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

/*
Representation of the Movies when used has nodes for simplicity.
Book made more sense than using movie as the name class.
*/

class Book {
private:
    string Title; //movie Title
    int repetitions; //total ocurrences of X word in the movie.
    
public:
    //Default constructor
	Book(const string& title);
    //Constructor passing repetitions values
    Book(const string& title, const int& repetitions);
	
    //Method
    void increase();
    //getters
    int getRepetitions() const;
    string getTitle() const;
};

bool bookSort(const Book& book1, const Book& book2); //Helper function for comparisions of books

#endif /* defined(____Book__) */
