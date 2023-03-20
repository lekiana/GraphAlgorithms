//
// Created by lenak on 16.06.2022.
//

#include "shortPath.h"
#include <cmath>
#include "list.h"

#define vertex pair <int, int>

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
        cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000.0; //milliseconds

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}

void shortPath::measure(int x)
{
    double data, avg;
    double sum = 0.0;

    srand(time(nullptr));

    for(int i = 0; i < 50; i++)
    {
        int randomNr = ((rand() % 1000) - 500);
        //int randomIndex = ((rand() % (size)) + 0);
        generate(x, 99);
        StartCounter();
        DijkstraList();
        data = GetCounter();
        sum = sum + data;
    }

    avg = sum/100;
    cout << avg << endl;
}

void shortPath::generate(int n, double density)
{
    delete tab;
    delete [] matrix;

    node_count = n;
    if (density == 99) density = 100;
    edges_count = (int) round(density / 100 * n * (n - 1) / 2);

    List considered{};
    considered.head = considered.tail = nullptr;
    considered.count = 0;

    tab = new listEl * [node_count];

    matrix = new int * [node_count];
    int i, j;
    for(i = 0; i < node_count; i++ )
        matrix [i] = new int [node_count];

    for(i = 0; i < node_count; i++)
        for(j = 0; j < node_count; j++)
            matrix [i][j] = 0;

    int randomNode;
    do randomNode = rand() % node_count;
    while (randomNode == 0);

    int randomWeight = rand() % 10;

    matrix[0][randomNode] = randomWeight;
    matrix[randomNode][0] = randomWeight;
    considered.addValueToList(0, 0);
    considered.addValueToList(1, randomNode);

    int count = 2;
    while (considered.count != node_count)
    {
        int consideredNode;
        do consideredNode = rand() % node_count;
        while (!considered.IsValueInList(consideredNode));

        do randomNode = rand() % node_count;
        while (considered.IsValueInList(randomNode));

        randomWeight = rand() % 10;
        matrix[consideredNode][randomNode] = matrix[randomNode][consideredNode] = randomWeight;
        considered.addValueToList(count, randomNode);
        count++;
    }

    int edgesCurr = node_count - 1;
    int n1, n2;
    while (edgesCurr != edges_count)
    {
        do
        {
            n1 = rand() % node_count;
            n2 = rand() % node_count;
        } while (n1 == n2 || matrix[n1][n2] != 0);

        randomWeight = rand() % 10;
        matrix[n1][n2] = matrix[n2][n1] = randomWeight;

        edgesCurr++;
    }

    if (density == 100)
    {
        int del = edges_count / 100;

        for (int i = 0; i < del; i++)
        {
            do
            {
                n1 = rand() % node_count;
                n2 = rand() % node_count;
            } while (n1 == n2 || matrix[n1][n2] != 0);

            matrix[n1][n2] = matrix[n2][n1] = 0;
        }
    }

    findNeighbours();
}

void shortPath::loadFromFile(const string& FileName)
{
    delete [] matrix;
    delete [] tab;

    fstream file;
    file.open(FileName, ios:: in);
    if(!file.good()) exit(0);

    string readSize, readLine;//,size

    getline(file, readSize);
    getCount(readSize);
    file.close();

    tab = new listEl * [node_count];

    matrix = new int * [node_count];
    int i, j;
    for(i = 0; i < node_count; i++ )
        matrix [i] = new int [node_count];

    for(i = 0; i < node_count; i++)
        for(j = 0; j < node_count; j++)
            matrix [i][j] = 0;

    file.open(FileName, ios:: in);
    if(!file.good()) exit(0);
    getline(file, readSize);

    for(i = 0; i < edges_count; i++){
        getline(file, readLine);
        char n1, n2, w;
        n1 = (int) readLine[0];
        n2 = (int) readLine[2];
        w = (int) readLine[4];

        int node1, node2, weight;
        node1 = n1 - 48;
        node2 = n2 - 48;
        weight = w - 48;

        matrix[node1][node2] = weight;
    }

    file.close();
    findNeighbours();
}

void shortPath::findNeighbours()
{
    //matrix
    nodes = new n [node_count];
    for(int i = 0; i < node_count; i++)
    {
        for(int j = 0; j < node_count; j++)
        {
            if(matrix[i][j] != 0)
            {
                nodes[i].neighbours.push_back(j);
            }
        }
    }

    //list
    for(int i1 = 0; i1 < node_count; i1++)
    {
        int size = nodes[i1].neighbours.size();
        tab [i1] = new listEl [size];

        int tab_i = 0;
        for (int i2: nodes[i1].neighbours)
        {
            listEl element{};
            element.n = i2;

            element.key = matrix[i1][i2];
            tab[i1][tab_i] = element;
            tab_i++;
        }
    }
}

int shortPath::getCount(string s)
{
    string temp;
    string e, n, b;
    int begin;

    for(int i = 0; i <= s.size()-1; i++){
        if(s[i] != ' '){
            temp += s[i];
            if(i == s.size()-1) b = temp;
        }
        else{
            if(i == s.size()-2) n = temp;
            else if(i == s.size()-4) e = temp;
            if(i == s.size()-1) b = temp;
            temp = "";
        }
    }

    begin = atoi(b.c_str());
    edges_count = atoi(e.c_str());
    node_count = atoi(n.c_str());

    return begin;
}

int findMinVertex(const int * distance,bool * visited,int n){
    int minVertex = -1;
    for (int i=0; i < n; i++){
        if (!visited[i] && (minVertex == -1 || distance[i] < distance[minVertex])){
            minVertex=i;
        }
    }
    return minVertex;
}

void shortPath::DijkstraMatrix(){

    int * p = new int[node_count];
    int * d = new int[node_count];
    bool * visited = new bool[node_count];

    for (int i = 0; i < node_count; ++i){
        d[i]= 100;  //infinity
        visited[i]=false;
        p[i] = 100; //null
    }
    d[0]=0;

    int minVertex,dist;
    for (int i = 0; i < node_count - 1; i++){

        minVertex = findMinVertex(d, visited, node_count);
        visited[minVertex] = true;

        for(int j=0; j < node_count; j++){

            if (matrix[minVertex][j] != 0 && !visited[j]){
                dist = d[minVertex] + matrix[minVertex][j];
                if(dist < d[j]){
                    d[j] = dist;
                    p[j] = minVertex;
                }
            }
        }
    }

    DijkstraDisplay(d, p);

    delete [] visited;
    delete [] d;
    delete [] p;
}

void shortPath::DijkstraDisplay(int * d, int * p) const
{
    cout << "Short path (Dijkstra)" << endl;
    for (int i = 0; i < node_count; ++i)
    {
           cout << "v: " << i << ", d: " << d[i] << ", p: " << p[i] << endl;
    }
}

void shortPath::DijkstraList(){

    int * p = new int[node_count];
    int * d = new int[node_count];
    bool * visited = new bool[node_count];

    for (int i = 0; i < node_count; ++i){
        d[i]= 100;  //infinity
        visited[i]=false;
        p[i] = 100; //null
    }

    d[0]=0;
    int minVertex,dist;

    for (int i1 = 0; i1 < node_count - 1; i1++){

        minVertex = findMinVertex(d, visited, node_count);
        visited[minVertex]=true;

        for (int j = 0; j < nodes[minVertex].neighbours.size(); j++) // for nodes directly connected to v1
        {
            int i2 = tab[minVertex][j].n;
            int key = tab[minVertex][j].key;

            if (!visited[i2])
            {
                dist = d[minVertex] + key;
                if(dist < d[i2]){
                    d[i2] = dist;
                    p[i2] = minVertex;
                }
            }
        }

        for(int j=0; j < node_count; j++){

            if (matrix[minVertex][j] != 0 && !visited[j]){
                dist = d[minVertex] + matrix[minVertex][j];
                if(dist < d[j]){
                    d[j] = dist;
                    p[j] = minVertex;
                }
            }
        }
    }

    DijkstraDisplay(d, p);

    delete [] visited;
    delete [] d;
    delete [] p;
}

void shortPath::displayM() const
{
    cout << endl;
    cout << "Matrix" << endl;
    cout << "   ";

    for(int i = 0; i < node_count; i++ )
        cout << setw(3) << i;

    cout << endl;
    for(int i = 0; i < node_count; i++ )
    {
        cout << setw(3) << i;
        for(int j = 0; j < node_count; j++ )
        {
            cout << setw(3);
            if(matrix [i][j] == 0) cout << 0;
            else cout << 1;
        }
        cout << endl;
    }
    cout << endl;
}

void shortPath::displayL() const
{
   cout << "Neighbour's list" << endl;
    for(int i = 0; i < node_count; i++)
    {
        cout << i << " -> ";
        int size = nodes[i].neighbours.size();
        for(int j = 0; j < size; j++)
        {
            cout << "(-" << tab[i][j].n << ", " << tab[i][j].key << ") ";
        }
        cout << endl;
    }
}
