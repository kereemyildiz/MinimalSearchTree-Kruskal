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
Node::Node(string name)
{
    this->label = count;
    count++;
    this->name = name;
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


class Graph{
    public:
    vector <Edge> edges;
    vector<Edge> MST;
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
int main()
{


    string fname = "city_plan_1.txt";
    ifstream city_plan(fname);

    Graph g;

    vector<Edge> GPandCh;
    vector<Edge> GPandHipp;

    string source;
    string destination;
    string _weight;
    int weight;
    while (city_plan.good())
    {
        getline(city_plan, source, ',');
        getline(city_plan, destination, ',');
        getline(city_plan, _weight, '\n');
        weight = stod(_weight);

        Node *_source = new Node(source);
        Node *_destination = new Node(destination);


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
        cout << g.edges[i].source->name << ", " << g.edges[i].destination->name << ", " << g.edges[i].weight << endl;
    }

        return 0;
}