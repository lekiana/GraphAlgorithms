//
// Created by lenak on 22.05.2022.
//

#ifndef UNTITLED1_MST_H
#define UNTITLED1_MST_H

#endif //UNTITLED1_MST_H

#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <windows.h>
#include <iomanip>
#include <list>
#include <queue>
#include <cstdlib>
#include <cmath>

using namespace std;

struct listElem
{
    //neighbour; connection weight
    int n;
    int key;
};

struct node
{
    list<int> neighbours;
};

class MST
{
public:

    int ** matrix;
    listElem ** tab;

    int * parent;
    int * rank;

    list<tuple<int, int, int>> kruskal;

    node * nodes;

    int * CON;
    int * KEY;

    int node_count, edges_count;

    void PrimMatrix();
    void PrimList();
    void displayMatrix() const;
    void displayList() const;

    void loadFromFile(const string& FileName);
    void getCount(string s);
    void findNeighbours();

    void KruskalMatrix();
    void KruskalList();
    void MakeSet();
    int FindSet(int x);
    void Union(int x, int y);

    void generateRandom(int n, double density);
    void copyList(list<listElem>);
    int findKey(int i) const;

    void DisplayPrim(string s);
    void DisplayKruskal(string s);

    //void measure(int x);
};