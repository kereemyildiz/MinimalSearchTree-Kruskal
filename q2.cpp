#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Node {
    public:
        int label;
        string name;
        static int count;
        Node(string name);
};

int Node::count = 0;
vector<Node> nodes;

int containsName(vector<Node> nodes, string name)
{
    unsigned int i = 0;
    for (; i < nodes.size();i++ )
    {
        if (name == nodes[i].name)
        {
            return i;
        }
    }
    return i;
}

Node::Node(string name)
{
    this->name = name;
    this->label = count;
    count++;
}



int main()
{

    nodes.reserve(100);

    int rowCount = 20;
    int colCount = 20;
    int** a = new int*[rowCount];
    for(int i = 0; i < rowCount; ++i){
        a[i] = new int[colCount];
        for (int j = 0; j < colCount; ++j)
        {
            a[i][j] = 0;
        }
    }
    string fname = "path_info_1.txt";
    ifstream city_plan(fname);

    string source;
    string destination;
    string _weight;
    int weight;
    Node *_source;
    Node *temp_source;
    Node *_destination;
    Node *temp_destination;


    while (city_plan.good())
    {
        getline(city_plan, source, ',');
        getline(city_plan, destination, ',');
        getline(city_plan, _weight, '\n');
        weight = stod(_weight);

        cout << source << ", " << destination << ", " << weight << endl;

        unsigned int index1 = containsName(nodes, source);
        if (index1 == nodes.size())
        {
            temp_source = new Node(source);
            nodes.push_back(*temp_source);
            _source = &nodes[index1];

        }
        else
        {
            _source = &nodes[index1];
        }
        
        unsigned int index2 = containsName(nodes, destination);

        if (index2 == nodes.size())
        {
    
            temp_destination = new Node(destination);
            nodes.push_back(*temp_destination);
            _destination = &nodes[index2];

        }
        else
        {
            _destination = &nodes[index2];
        }
        // cout << "2" << endl;
        // cout << _source->label << ", " << _destination->label << ", " << weight << endl;
        a[_source->label][_destination->label] = weight;
    }

    for (int k = 0; k < nodes.size();k++)
    {
        cout << nodes[k].label << ", " << nodes[k].name << endl;
    }
    int size = nodes.size();
    cout << "size : "<<size << endl;
    int **graph = new int*[size];

    for(int k = 0; k < size; ++k){
        graph[k] = new int[size];
        for (int m = 0; m < size; ++m)
        {
            graph[k][m] = a[k][m];
            cout << graph[k][m] << " ";
        }
        cout << endl;
    }



    return 0;
}
