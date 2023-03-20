#include "MST.h"
#include "list.h"
#include "shortPath.h"

void displayMenu(const string& info)
{
    cout << endl;
    cout << info << endl;
    cout << "1.Load from file" << endl;
    cout << "2.Generate random" << endl;
    cout << "3.Display" << endl;
    cout << "4.Test" << endl;
    cout << "0.Main menu" << endl;
    cout << "Type the nr: ";
}

void menu_MST()
{
    MST myMST{};
    myMST.node_count = myMST.edges_count = 0;
    myMST.nodes = new node [myMST.node_count];

    char opt;
    string fileName;
    int x, d;

    do{
        displayMenu("--- MST ---");
        opt = getche();
        cout << endl;
        switch (opt){
            case '1': //Load from file

                cout << "Enter file name: ";
                cin >> fileName;
                myMST.loadFromFile(fileName);

                myMST.displayMatrix();
                myMST.displayList();

                myMST.PrimMatrix();
                myMST.PrimList();

                myMST.KruskalMatrix();
                myMST.KruskalList();

                break;

            case '2': //Generate random

                cout << "Enter vertex count: ";
                cin >> x;
                cout << "Enter density: ";
                cin >> d;
                myMST.generateRandom(x, d);

                myMST.displayMatrix();
                myMST.displayList();

                myMST.PrimMatrix();
                myMST.PrimList();

                myMST.KruskalMatrix();
                myMST.KruskalList();

                break;

            case '3': //Display

                myMST.displayMatrix();
                myMST.displayList();

                break;

            case '4': //Test
                cout << "Enter vertex count: ";
                cin >> x;
                cout << "Enter density: ";
                cin >> d;
                myMST.generateRandom(x, d);
                break;
        }

    } while (opt != '0');
}

void menu_shortPath()
{

    shortPath shortPath{};
    shortPath.node_count = shortPath.edges_count = 0;
    //shortPath.nodes = new node [shortPath.node_count];

    char opt;
    string fileName;
    int n, d;

    do{
        displayMenu("--- Short Path ---");
        opt = getche();
        cout << endl;
        switch (opt){
            case '1': //Load from file

                cout << "Enter file name: ";
                cin >> fileName;
                shortPath.loadFromFile(fileName);

                shortPath.displayM();
                shortPath.displayL();

                shortPath.DijkstraMatrix();
                shortPath.DijkstraList();

                break;

            case '2': //Generate random

                cout << "Enter vertex count: ";
                cin >> n;
                cout << "Enter density: ";
                cin >> d;
                shortPath.generate(n, d);

                shortPath.displayM();
                shortPath.displayL();

                shortPath.DijkstraMatrix();
                shortPath.DijkstraList();

                break;

            case '3': //Display

                shortPath.displayM();
                shortPath.displayL();

                break;

            case '4': //Test

                break;
        }

    } while (opt != '0');
}

int main() {
    char option;
    do{
        cout << endl;
        cout << "==== MAIN MENU ====" << endl;
        cout << "1.MST" << endl;
        cout << "2.Short path" << endl;
        cout << "0.End" << endl;
        cout << "Choose the option: ";
        option = getche();
        cout << endl;

        switch (option){
            case '1':
                menu_MST();
                break;

            case '2':
                menu_shortPath();
                break;
        }

    } while (option != '0');

    return 0;
}
