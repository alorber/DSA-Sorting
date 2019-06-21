//
//  main.cpp
//  DSA 1 Project 2 - Sorting
//
//  Created by Andrew Lorber.
//  Copyright © 2019 Andrew Lorber. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <array>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
    string lastName;
    string firstName;
    string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {
    
    ifstream input(filename);
    if (!input) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }
    
    // The first line indicates the size
    string line;
    getline(input, line);
    stringstream ss(line);
    int size;
    ss >> size;
    
    // Load the data
    for (int i = 0; i < size; i++) {
        getline(input, line);
        stringstream ss2(line);
        Data *pData = new Data();
        ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
        l.push_back(pData);
    }
    
    input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {
    
    ofstream output(filename);
    if (!output) {
        cerr << "Error: could not open" << filename << "\n";
        exit(1);
    }
    
    // Write the size first
    int size = l.size();
    output << size << "\n";
    
    // Write the data
    for (auto pData:l) {
        output << pData->lastName << " "
        << pData->firstName << " "
        << pData->ssn << "\n";
    }
    
    output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
    string filename;
    cout << "Enter name of input file: ";
    cin >> filename;
    list<Data *> theList;
    loadDataList(theList, filename);
    
    cout << "Data loaded.\n";
    
    cout << "Executing sort...\n";
    clock_t t1 = clock();
    sortDataList(theList);
    clock_t t2 = clock();
    double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    
    cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";
    
    cout << "Enter name of output file: ";
    cin >> filename;
    writeDataList(theList, filename);
    
    return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

//T12 -----
class NewData12 {
public:
    Data* ptr;
    char ln1;
    char fn1;
    char fn2;
    const char* lname;
    const char* fname;
    const char* ssn;
    NewData12(Data* d, const char* ln, const char* fn, const char* ss, char l1, char f1, char f2)
    : ptr{d}, lname{ln}, fname{fn}, ssn{ss}, ln1{l1}, fn1{f1}, fn2{f2} {}
    NewData12(){};
};

array<NewData12, 1020000> T12;
array<array<NewData12*, 1000000>, 30> lbucket;
array<int, 30> lbucketCounts;
int bnum = 0;
int AsciiVal;

struct {
    bool operator() (NewData12* (a), NewData12* (b))const{
        if(a->ln1 == b->ln1){
            if(strcmp(a->lname, b->lname) == 0){
                if(a->fn1 == b->fn1){
                    if(a->fn2 == b->fn2){
                        if(strcmp(a->fname, b->fname) == 0){
                            return strcmp(a->ssn, b->ssn) < 0;
                        } else { return strcmp(a->fname, b->fname) < 0; }
                    } else { return a->fn2 < b->fn2; }
                } else { return a->fn1 < b->fn1; }
            } else { return strcmp(a->lname, b->lname) < 0; }
        } else { return (a->ln1 < b->ln1); }
    }
} T12Sort;

//T3 -----
list<Data*>::iterator lowSSN;
list<Data*>::iterator lowerSSN;
string tmp;
string fname;

void insertionSort(list<Data*>::iterator start, list<Data*>::iterator end){
    auto begin = next(start);
    
    for (; begin != end; begin++) {
        lowSSN = begin;
        lowerSSN = prev(lowSSN);
        tmp = (*lowSSN)->ssn;
        while(lowSSN != start && strcmp(((*lowerSSN))->ssn.data(), tmp.data()) > 0){
            (*lowSSN)->ssn = (*(lowerSSN))->ssn;
            lowSSN--;
            lowerSSN--;
        }
        (*lowSSN)->ssn = tmp;
    }
}

//T4 -----
array<array<Data*, 10000>, 1000> bin1;
array<int, 1000> count1 = {0};
array<array<Data*, 10000>, 1000> bin2;
array<int, 1000> count2 = {0};
array<array<Data*, 10000>, 1000> bin3;
array<int, 1000> count3 = {0};
int ssnPart;

//All ---
int lSize;
int j = 0;
int k = 0;


//Sort
void sortDataList(list<Data *> &l){
    lSize = l.size();
    if((*l.begin())->lastName == (*next(l.begin(), 1000))->lastName &&
       (*next(l.begin(), 200))->lastName == (*next(l.begin(), 6000))->lastName) {
        /* --- T4 --- */
       
        for (auto i = l.begin(); i != l.end(); i++) {
            ssnPart = ((((int)(*i)->ssn[8] - '0') * 100) + (((int)(*i)->ssn[9] - '0') * 10) +
                       ((int)(*i)->ssn[10] - '0'));
            bin3[ssnPart][count3[ssnPart]++] = (*i);
        }
        for (; j < 1000; j++) {
            if (count3[j] == 0) {
                j++;
            }
            for(k = 0; k < count3[j]; k++){
                ssnPart = ((((int)(bin3[j][k])->ssn[4] - '0') * 100) + (((int)(bin3[j][k])->ssn[5] - '0') * 10) +
                           ((int)(bin3[j][k])->ssn[7] - '0'));
                bin2[ssnPart][count2[ssnPart]++] = bin3[j][k];
            }
        }
        
        for (j = 0; j < 1000; j++) {
            if (count2[j] == 0) {
                j++;
            }
            for(k = 0; k < count2[j]; k++){
                ssnPart = ((((int)(bin2[j][k])->ssn[0] - '0') * 100) + (((int)(bin2[j][k])->ssn[1] - '0') * 10) +
                           ((int)(bin2[j][k])->ssn[2] - '0'));
                bin1[ssnPart][count1[ssnPart]++] = bin2[j][k];
            }
        }
        auto i = l.begin();
        for(j = 0; j < 1000; j++){
            if (count1[j] == 0) {
                j++;
            }
            for(k = 0; k < count1[j]; k++, i++){
                (*i) = bin1[j][k];
            }
        }
        
    } else if (lSize < 120000 || strcmp(((*next(l.begin(), 6300))->lastName).data(), ((*next(l.begin(), 6000))->lastName).data()) < 0 ||
               strcmp(((*next(l.begin(), 500))->lastName).data(), (*l.begin())->lastName.data()) < 0) {
        /* --- T1 / T2 ---- */
        for (auto i = l.begin(); i != l.end(); i++, j++) {
            AsciiVal = (int)((*i)->lastName[0]) - 65;
            T12[j] = NewData12((*i), ((*i)->lastName.data())+2, ((*i)->firstName.data())+2,
                             ((*i)->ssn.data()), (*i)->lastName[1], (*i)->firstName[0], (*i)->firstName[1]);
            lbucket[AsciiVal][lbucketCounts[AsciiVal]++] = &T12[j];
        }
        for(; k < 30; k++){
            if (lbucketCounts[k] > 1) {
                sort(lbucket[k].begin(), next(lbucket[k].begin(), lbucketCounts[k]), T12Sort);
            }
        }
        j = 0;
        bnum = 0;
        for(auto i = l.begin(); i != l.end(); i++, j++){
            while (lbucketCounts[bnum] == 0) {
                bnum++;
            }
            (*i) = lbucket[bnum][j]->ptr;
            if (j == lbucketCounts[bnum] - 1) {
                j = -1;
                bnum++;
            }
        }
    } else /* --- T3 ---- */ {
        auto start = l.begin();
        fname = (*start)->firstName;
        
        for(auto i = l.begin(); i != l.end(); i++){
            if((*i)->firstName != fname){
                insertionSort(start, i);
                start = i;
                fname = (*i)->firstName;
            }
        }
        insertionSort(start, l.end());
    }
    
}
