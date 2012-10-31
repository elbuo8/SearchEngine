//
//  Histogram.h
//  
//
//  Created by Yamil Asusta on 10/29/12.
//
//

#ifndef ____Histogram__
#define ____Histogram__

#include <iostream>
#include <string>
#include <tr1/unordered_map>

using namespace std;

class Histogram {
private:
    int totalRepetitions;
    tr1::unordered_map<string, int> reverseIndex;
    
public:
    Histogram();
    Histogram(const string& index);
    void add(const string& bookTitle);
    int getTotalRepetitions() const;
    
};

#endif /* defined(____Histogram__) */
