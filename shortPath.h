//
// Created by lenak on 16.06.2022.
//

#ifndef UNTITLED1_SHORTPATH_H
#define UNTITLED1_SHORTPATH_H

#endif //UNTITLED1_SHORTPATH_H


#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <list> //tylko moja??
#include <queue>
#include <cstdlib>

using namespace std;

struct listEl
{
    //neighbour; connection weight
    int n;
    int key;
};

struct n
{
    list<int> neighbours; //matrix neighbours
};

class shortPath
{
public:
    int node_count, edges_count;
    int ** matrix; //matrix representation
    listEl ** tab; //list representation
    n * nodes;

    void generate(int n, double density);

    void loadFromFile(const string& FileName);
    void findNeighbours();
    int getCount(string s);
    void DijkstraMatrix();
    void DijkstraList();

    void displayM() const;
    void displayL() const;

    void measure(int x);
    void DijkstraDisplay(int * d, int * p) const;
};
