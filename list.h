#ifndef UNTITLED_LIST_H
#define UNTITLED_LIST_H

#endif //UNTITLED_LIST_H

#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

using namespace std;

struct ListElement
{
    int data;
    ListElement *next, *prev;
};

class List
{

public:

    ListElement *head, *tail;
    int count;

    int loadListFromFile(const string& FileName);

    bool IsValueInList(int value);

    void addValueToList(int index, int value);

    void deleteFromList(int value);

    void deleteFirst();

    void deleteLast();

    void displayList();

    void generateRandomList(int size);

    //void measure(int size);
};