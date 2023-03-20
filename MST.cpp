//
// Created by lenak on 22.05.2022.
//

#include "MST.h"
#include <vector>
#include "list.h"

#define vertex pair <int, int>

void MST::getCount(string s)
{
    string temp;
    string e,n;

    for(int i = 0; i <= s.size()-1; i++){
        if(s[i] != ' '){
            temp += s[i];
            if(i == s.size()-1) n = temp;
        }
        else{
            if(i == s.size()-2) e = temp;
            else n = temp;
            temp = "";
        }
    }

    edges_count = atoi(e.c_str());
    node_count = atoi(n.c_str());
}

void MST::loadFromFile(const string& FileName)
{
    delete [] matrix;
    delete tab;

    fstream file;
    file.open(FileName, ios:: in);
    if(!file.good()) exit(0);

    string readSize, readLine;

    getline(file, readSize);
    getCount(readSize);
    file.close();

    tab = new listElem * [node_count];

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
        matrix[node2][node1] = weight;
    }

    file.close();
    findNeighbours();
}

void MST::generateRandom(int n, double density)
{
    delete tab;
    delete [] matrix;

    node_count = n;
    if (density == 99) density = 100;
    edges_count = (int) round(density / 100 * n * (n - 1) / 2);

    List considered{};
    considered.head = considered.tail = nullptr;
    considered.count = 0;

    tab = new listElem * [node_count];

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

int MST::findKey(int i) const
{
    int minWeight = 0;
    for(int j = 0; j < node_count; j++)
    {
        if(matrix[i][j] != 0)
        {
            if(minWeight == 0 || minWeight > matrix[i][j])
                minWeight = matrix[i][j];
        }
    }
    return minWeight;
}

void MST::findNeighbours()
{
    //matrix
    nodes = new node [node_count];
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
        tab [i1] = new listElem [size];

        int tab_i = 0;
        for (int i2: nodes[i1].neighbours)
        {
            listElem element{};
            element.n = i2;

            element.key = matrix[i1][i2];
            tab[i1][tab_i] = element;
            tab_i++;
        }
    }
}

void MST::displayMatrix() const
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

void MST::displayList() const
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

void MST::PrimMatrix()
{
    CON = new int [node_count];
    KEY = new int [node_count];

    for(int i = 0; i < node_count; i++) //at firt all keys = infinity, connections = NULL here 100
    {
        KEY[i] = 100;
        CON[i] = 100;
    }

    KEY[0] = 0; //key of the starting node = 0

    priority_queue <vertex, vector<vertex>, greater<>> queue1; // queue.top() = n, n.fist = key[i], n.second = connection //n = <key, connection> connection = <n1, n2>

    //initialization vertex - nodes

    vertex ver; //first - key; second - nr

    //constructing list
    List unchecked{};
    unchecked.head = unchecked.tail = nullptr;
    unchecked.count = 0;

    ver = make_pair(0, 0);
    queue1.push(ver);
    unchecked.addValueToList(0, 0);

    for (int i = 1; i < node_count; i++)
    {
        ver = make_pair(100, i); //100 - infinity
        queue1.push(ver);
        unchecked.addValueToList(i, i);
    }

    while(!queue1.empty())
    {
        vertex v1 = queue1.top();
        queue1.pop();

        int i1 = v1.second;
        unchecked.deleteFromList(i1);

        for (int i2: nodes[i1].neighbours) // for nodes directly connected to v1
        {
            if (unchecked.IsValueInList(i2) && matrix[i1][i2] < KEY[i2])
            {
                KEY[i2] = matrix[i1][i2];
                CON[i2] = i1;

                //new queue
                for (int j = 0; j < queue1.size(); j++) queue1.pop();

                for (int k = 0; k < node_count; k++)
                {
                    if(unchecked.IsValueInList(k))
                    {
                        ver = make_pair(KEY[k], k);
                        queue1.push(ver);
                    }
                }
            }
        }
    }
    DisplayPrim("matrix");
}

void MST::DisplayPrim(string s)
{
    int sum = 0;
    cout << endl << "MST (Prim - " << s << ")" << endl;
    for (int i = 1; i < node_count; i++)
    {
        cout << i << " - " <<  CON[i] << ", " << KEY[i] << endl;
        sum = sum + KEY[i];
    }

    cout << "sum: " << sum << endl;
}

void MST::PrimList()
{
    CON = new int [node_count];
    KEY = new int [node_count];

    for(int i = 0; i < node_count; i++) //at firt all keys = infinity, connections = NULL here 100
    {
        KEY[i] = 100;
        CON[i] = 100;
    }

    KEY[0] = 0; //key starting node = 0

    priority_queue <vertex, vector<vertex>, greater<>> queue1; // queue.top() = n, n.fist = key[i], n.second = connection //n = <key, connection> connection = <n1, n2>

    //initialization vertex - nodes

    vertex ver; //first - key; second - nr

    //constructing list
    List unchecked{};
    unchecked.head = unchecked.tail = nullptr;
    unchecked.count = 0;

    ver = make_pair(0, 0);
    queue1.push(ver);
    unchecked.addValueToList(0, 0);

    for (int i = 1; i < node_count; i++)
    {
        ver = make_pair(100, i); //100 - infinity
        queue1.push(ver);
        unchecked.addValueToList(i, i);
    }

    while(!queue1.empty())
    {
        vertex v1 = queue1.top();
        queue1.pop();

        int i1 = v1.second;
        unchecked.deleteFromList(i1);

        for (int j = 0; j < nodes[i1].neighbours.size(); j++) // for nodes directly connected to v1
        {
            int i2 = tab[i1][j].n;
            int key = tab[i1][j].key;

            if (unchecked.IsValueInList(i2) && key < KEY[i2])
            {
                KEY[i2] = key;
                CON[i2] = i1;

                //new queue
                for (int i = 0; i < queue1.size(); i++) queue1.pop();

                for (int i = 0; i < node_count; i++)
                {
                    if(unchecked.IsValueInList(i))
                    {
                        ver = make_pair(KEY[i], i);
                        queue1.push(ver);
                    }
                }
            }
        }
    }
    DisplayPrim("list");
}

void MST::MakeSet()
{
    parent = new int [node_count];
    rank = new int [node_count];

    for (int i = 0; i < node_count; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}

int MST::FindSet(int a)
{
    if (a != parent[a]) parent[a] = FindSet(parent[a]);
    return parent[a];
}

void MST::Union(int x, int y)
{
    int a, b;
    a = FindSet(x);
    b = FindSet(y);

    if (rank[a] < rank[b]) parent[a] = b;
    else parent[b] = a;

    if (rank[a] == rank[b]) rank[a] = rank[a] + 1;
}

void MST::KruskalMatrix()
{
    MakeSet();
    priority_queue <tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> queue;

    List * c = new List [node_count]; //so the edges are unique

    for (int a = 0; a < node_count; a++)
    {
        List considered{};
        considered.head = considered.tail = nullptr;
        considered.count = 0;

        c[a] = considered;
    }

    for (int i = 0; i < node_count; i++)
    {
        for (int j: nodes[i].neighbours)
        {
            if (!c[i].IsValueInList(j))
            {
                tuple<int, int, int> edge;
                edge = make_tuple(matrix[i][j], i, j);
                queue.push(edge);

                c[j].addValueToList(c[j].count, i);
            }
        }
    }

    while (!queue.empty())
    {
        tuple<int, int, int> top = queue.top();
        queue.pop();

        int u = get<1>(top);
        int v = get<2>(top);

        if (FindSet(u) != FindSet(v))
        {
            kruskal.push_back(top);
            Union(u, v);
        }
    }
    DisplayKruskal("matrix");
}

void MST::DisplayKruskal(string s)
{
    cout << endl << "MST (Kruskal - " << s << ")" << endl;
    int y = 0;
    int sum = 0;
    while(!kruskal.empty())
    {
        tuple <int, int, int> front;
        front = kruskal.front();
        cout << get<1>(front) << " - " <<  get<2>(front) << ", " << get<0>(front) << endl;
        sum = sum + get<0>(front);
        kruskal.pop_front();
        y++;
    }

    cout << "sum: " << sum << endl;
}

void MST::KruskalList()
{
    MakeSet();
    priority_queue <tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> queue;

    for (int i = 0; i < node_count; i++)
    {
        for (int j = 0; j < nodes[i].neighbours.size(); j++)
        {
            tuple<int, int, int> edge;
            edge = make_tuple(tab[i][j].key, i, tab[i][j].n);
            queue.push(edge);
        }
    }

    while(!queue.empty())
    {
        tuple<int, int, int> top = queue.top();
        queue.pop();

        int u = get<1>(top);
        int v = get<2>(top);

        if (FindSet(u) != FindSet(v)) {
            kruskal.push_back(top);
            Union(u, v);
        }
    }
    DisplayKruskal("list");
}

