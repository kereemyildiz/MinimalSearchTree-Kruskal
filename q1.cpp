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
vector<int> parents;
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
    parents.push_back(label);
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
    for (unsigned int i = 0; i < vect.size();i++)
    {
        cout << vect[i].name << ", " << vect[i].name << endl;

    }
}

class Graph{
    public:
        int weight_sum;
        vector<Edge> edges;
        vector<Edge> MST;
        void runKruskal();
        void printMST();
        Graph() : weight_sum(0){}

};

bool checkValidity(Node* source,Node* destination)
{
    string hp = "Hp";
    string basilica = "Bas";
    string hippodrome = "Hipp";

    size_t found1 = source->name.find(hp);
    size_t found2 = destination->name.find(hp);
    size_t found3 = source->name.find(basilica);
    size_t found4 = destination->name.find(hippodrome);
    size_t found5 = source->name.find(hippodrome);
    size_t found6 = destination->name.find(basilica);


    if (found1 != std::string::npos && found2 != std::string::npos)  // source and destiantion is Hp
    {
        return false;
    }
    else if (found3 != std::string::npos && found4 != std::string::npos) // source is basilica and destination is hippodrome
    {
        return false;
    }
    else if( found5 != std::string::npos && found6 != std::string::npos) // source is hippodrome and desitination is baislica
    {
        return false;
    }
    return true;
}
int FindSet(int vertice)
{
    int parent = parents[vertice];

    if (parent == vertice)
        return vertice;

    return FindSet(parent);
}

void Graph::runKruskal()
{
    int sourceParent, destinationParent;
    for (unsigned int i = 0; i < edges.size();i++)
    {
        sourceParent = FindSet(edges[i].source->label);
        destinationParent = FindSet(edges[i].destination->label);

        if (sourceParent != destinationParent && checkValidity(edges[i].source,edges[i].destination))
        {
            MST.push_back(edges[i]);
            edges[i].destination->label = edges[i].source->label;
            parents[destinationParent] = parents[sourceParent];
            weight_sum += edges[i].weight;
        }
    }
}
void Graph::printMST()
{
    sort(MST.begin(), MST.end());
    for (unsigned int i = 0; i < MST.size();i++)
    {
        cout << MST[i].source->name << " " << MST[i].destination->name << " " << MST[i].weight << endl;
    }
    cout << weight_sum << endl;
}

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
    nodes.reserve(100);
    string fname;
    cin >> fname;
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

        Edge *edge = new Edge(_source, _destination, weight);

        if (checkGPandChurch(edge))
        {
            if (GPandCh.size() == 0)
                GPandCh.push_back(*edge);
            else
            {
                if(GPandCh[0].weight < edge->weight){
                    g.edges.push_back(*edge);
                }
                else{
                    g.edges.push_back(GPandCh[0]);
                    GPandCh.erase(GPandCh.begin());
                    GPandCh.push_back(*edge);
                }
                
            }
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
    g.runKruskal();
    g.printMST();

    return 0;
}