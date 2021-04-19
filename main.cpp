#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

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
    int i = 0;
    for (i; i < nodes.size();i++ )
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


class Edge {
    public:
    int weight;
    Node* source;
    Node* destination;
    Edge(Node* source, Node* destination,int weight);
    friend bool operator<(Edge const& leftHandSide, Edge const& rightHandSide);
	friend bool operator>(Edge const& leftHandSide, Edge const& rightHandSide);

};
bool operator<(Edge const& leftHandSide, Edge const& rightHandSide) {
    return leftHandSide.weight < rightHandSide.weight;
}
bool operator>(Edge const& leftHandSide, Edge const& rightHandSide) {
    return leftHandSide.weight > rightHandSide.weight;
}
Edge::Edge(Node* source, Node* destination, int weight)
{
    this->source = source;
    this->destination = destination;
    this->weight = weight;
}

void const printNodeVector(const vector<Node> &vect) 
{
    for (int i = 0; i < vect.size();i++)
    {
    }
}

class Graph{
    public:
    vector <Edge> edges;
    vector <Edge> MST;
};


bool checkGPandChurch(Edge *edge)
{
    string GP = "GP";
    string church = "Ch";

    size_t found1 = edge->source->name.find(GP);
    size_t found2 = edge->destination->name.find(church);

    if (found1 == std::string::npos || found2 == std::string::npos)  // check whether location is GP and Church or not
    {
        return false;
    }

    return true;
}
bool checkGPandHipp(Edge* edge)
{

    string GP = "GP";
    string Hipp = "Hipp";

    size_t found1 = edge->source->name.find(GP);
    size_t found2 = edge->destination->name.find(Hipp);

    if (found1 == std::string::npos || found2 == std::string::npos) // check whether location is GP and Hippodrome or not
    {

        return false;
    }
    return true;
}
int main(int argc, char** argv)
{

    nodes.reserve(100);
    string fname = argv[1];
    ifstream city_plan(fname);

    Graph g;

    vector<Edge> GPandCh;
    vector<Edge> GPandHipp;

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

        int index1 = containsName(nodes, source);

        if (index1 == nodes.size())
        {

            temp_source = new Node(source);
            nodes.push_back(*temp_source);
            _source = &nodes[index1];
            printNodeVector(nodes);

        }
        else
        {
            _source = &nodes[index1];

        }
        int index2 = containsName(nodes, destination);

        if (index2 == nodes.size())
        {
        

            temp_destination = new Node(destination);
            nodes.push_back(*temp_destination);
            printNodeVector(nodes);
            _destination = &nodes[index2];

        

        }
        else
        {
        
            _destination = &nodes[index2];

        }

        Edge *edge = new Edge(_source, _destination, weight);
        if (checkGPandChurch(edge))
        {

            GPandCh.push_back(*edge);
        }
        else if (checkGPandHipp(edge))
        {

            GPandHipp.push_back(*edge);
        }
        else
        {

            g.edges.push_back(*edge);
        }

    }
    sort(g.edges.begin(), g.edges.end());

    // except GP-Ch and GP-Hipp pairs, all edges are sorted,
    // since they have priorities, we will insert them front of the array

    for (int i = GPandHipp.size() - 1; i >= 0; i--) 
    {
        sort(GPandHipp.begin(), GPandHipp.end());
        g.edges.insert(g.edges.begin(), GPandHipp[i]);
    }

    for (int i = GPandCh.size() - 1; i >= 0; i--)
    {
        sort(GPandCh.begin(), GPandCh.end());
        g.edges.insert(g.edges.begin(), GPandCh[i]);
    }

    for (int i = 0; i < g.edges.size();i++)
    {
        cout << "Source Label: " << g.edges[i].source->label<<", " <<g.edges[i].source->name << ", " <<"Destination Label: " << g.edges[i].destination->label <<", " << g.edges[i].destination->name << ", " << g.edges[i].weight << endl;
    }

    return 0;
}