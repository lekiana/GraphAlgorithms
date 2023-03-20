//
// Created by lenak on 02.06.2022.
//

#include "list.h"

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

int List::loadListFromFile(const string& FileName)
{
    ListElement *e = head;

    while (count != 0)
    {
        count--;
        head = e -> next;
        if(e -> next) e -> next -> prev = e -> prev;
        else tail = e -> prev;
        delete e;
        e = head;
    }

    fstream file;

    file.open(FileName.c_str());

    string readSize, readLine;
    getline(file, readSize);
    count = atoi(readSize.c_str());


    for (int i = 0; i < count; i++ )
    {
        ListElement *p;

        p = new ListElement;
        getline(file, readLine);
        p -> data = atoi(readLine.c_str());
        p -> next  = nullptr;
        p -> prev = tail;
        tail = p;

        if (p -> prev) p -> prev -> next = p;
        else head = p;
    }

    return 0;
}

bool List::IsValueInList(int value)
{
    ListElement *p = head;

    while (p)
    {
        if (p -> data == value) return true;
        p = p -> next;
    }

    return false;
}

void List::addValueToList(int index, int value)
{
    ListElement *p;

    if (index == 0)
    {

        p = new ListElement;
        p -> data = value;
        p -> prev = nullptr;
        p -> next = head;
        head = p;

        if (p -> next) p -> next -> prev = p;
        else tail = p;

    } else if (index == count)
    {

        p = new ListElement;
        p -> data = value;
        p -> next = nullptr;
        p -> prev = tail;
        tail = p;

        if(p -> prev) p -> prev -> next = p;
        else head = p;

    } else if (index > 0 && index < count)
    {

        p = new ListElement;
        p -> data = value;

        ListElement *e = head;

        for (int i = 0; i < index; i++)
        {
            e = e -> next;
        }

        p -> next = e;
        p -> prev = e -> prev;

        e -> prev -> next = p;
        e -> prev = p;

    } else cout << "\nThe list is not long enough to add element with index " << index << "\n";

    count++;
}

void List::deleteFromList(int value)
{
    if (IsValueInList(value))
    {

        count--;

        ListElement *e = head;

        while (e)
        {
            if (e -> data == value) break;
            e = e -> next;
        }

        if (e -> prev) e -> prev -> next = e -> next;
        else head = e -> next;

        if (e -> next) e -> next -> prev = e -> prev;
        else tail = e -> prev;

        delete e;

    }
}

void List::deleteFirst()
{
    count--;
    ListElement * e = head;
    if(e -> prev) e -> prev -> next = e -> next;
    else head = e -> next;

    if( e -> next ) e -> next -> prev = e -> prev;
    else tail = e -> prev;
    delete e;
}

void List::deleteLast()
{
    count--;
    ListElement * e = tail;
    if(e -> prev) e -> prev -> next = e -> next;
    else head = e -> next;

    if( e -> next ) e -> next -> prev = e -> prev;
    else tail = e -> prev;
    delete e;
}

void List::displayList()
{
    ListElement *p1 = head;

    while (p1)
    {
        cout << p1 -> data << "  ";
        p1 = p1 -> next;
    }

    cout << endl;
    ListElement *p2 = tail;

    while (p2)
    {
        cout << p2 -> data << "  ";
        p2 = p2 -> prev;
    }
}

void List::generateRandomList(int size)
{
    ListElement *e = head;

    while (count != 0)
    {
        count--;
        head = e -> next;
        if(e -> next) e -> next -> prev = e -> prev;
        else tail = e -> prev;
        delete e;
        e = head;
    }

    count = size;
    srand(time(nullptr));

    for (int i = 0; i < size; i++ )
    {
        ListElement *p;

        p = new ListElement;

        int randomNr = ((rand() % 10000) - 5000);

        p -> data = randomNr;
        p -> next  = nullptr;
        p -> prev = tail;
        tail = p;

        if (p -> prev) p -> prev -> next = p;
        else head = p;
    }
}
