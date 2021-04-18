#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


class Edge {
    public:
    int weight;
    string source;
    string destination;
    Edge(string source, string destination,int weight);


};

Edge::Edge(string source, string destination, int weight) : source(source), destination(destination), weight(weight) {}

int main()
{

    vector<Edge> vertices;
    string fname = "city_plan_1.txt";
    ifstream city_plan(fname);
    string source;
    string destination;
    string dummy;
    string _weight;
    int weight;
    while (city_plan.good())
    {
        getline(city_plan, source, ',');
        getline(city_plan, destination, ',');
        getline(city_plan, _weight, '\n');
        weight = stod(_weight);
        // cout << source << " "<< destination<< " " << _weight <<  endl;
        vertices.push_back(Edge(source, destination, weight));
    }
    for (int i = 0; i < vertices.size();i++)
    {
        cout << vertices[i].source << ", " << vertices[i].destination << ", " << vertices[i].weight << endl;
    }

    return 0;
}