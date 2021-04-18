#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;



class Edge {
    public:
    int weight;
    string source;
    string destination;
    Edge(string source, string destination,int weight);
    friend bool operator<(Edge const& leftHandSide, Edge const& rightHandSide);
	friend bool operator>(Edge const& leftHandSide, Edge const& rightHandSide);

};
bool operator<(Edge const& leftHandSide, Edge const& rightHandSide) {
    return leftHandSide.weight < rightHandSide.weight;
}
bool operator>(Edge const& leftHandSide, Edge const& rightHandSide) {
    return leftHandSide.weight > rightHandSide.weight;
}
Edge::Edge(string source, string destination, int weight) : source(source), destination(destination), weight(weight) {}

bool checkGPandChurch(Edge *vertice)
{
    string GP = "GP";
    string church = "Ch";

    size_t found1 = vertice->source.find(GP);
    size_t found2 = vertice->destination.find(church);

    if (found1 == std::string::npos || found2 == std::string::npos)
    {
        return false;
    }
    return true;
}
bool checkGPandHipp(Edge* vertice)
{
    string GP = "GP";
    string Hipp = "Hipp";

    size_t found1 = vertice->source.find(GP);
    size_t found2 = vertice->destination.find(Hipp);

    if (found1 == std::string::npos || found2 == std::string::npos)
    {
        return false;
    }
    return true;
}
int main()
{

    vector<Edge> vertices;
    vector<Edge> GPandCh;
    vector<Edge> GPandHipp;
    string fname = "city_plan_1.txt";
    ifstream city_plan(fname);
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
        Edge *vertice = new Edge(source, destination, weight);
        // cout << source << " "<< destination<< " " << _weight <<  endl;
        if (checkGPandChurch(vertice))
        {
            GPandCh.push_back(*vertice);
        }
        else if (checkGPandHipp(vertice))
        {
            GPandHipp.push_back(*vertice);
        }
        else
        {
            vertices.push_back(*vertice);
        }
    }
    sort(vertices.begin(), vertices.end());

    for (int i = GPandHipp.size() - 1; i >= 0; i--)
    {
        sort(GPandHipp.begin(), GPandHipp.end());
        vertices.insert(vertices.begin(), GPandHipp[i]);
    }

    for (int i = GPandCh.size() - 1; i >= 0; i--)
    {
        sort(GPandCh.begin(), GPandCh.end());
        vertices.insert(vertices.begin(), GPandCh[i]);
    }

    for (int i = 0; i < vertices.size();i++)
    {
        cout << vertices[i].source << ", " << vertices[i].destination << ", " << vertices[i].weight << endl;
    }

        return 0;
}