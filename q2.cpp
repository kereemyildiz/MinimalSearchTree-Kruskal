#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits.h>


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
vector<int> forbidden;

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

bool checkEnemyZone(string name)
{
    string enemy = "E";
    size_t found = name.find(enemy);

    if (found != std::string::npos)
        return false;
    return true;
}
int minDistance(vector<int> dist, 
                vector<bool> sptSet)
{

    // Initialize min value
    int min = INT_MAX, min_index;

    for (unsigned int v = 0; v < nodes.size(); v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Function to print shortest
// path from source to j
// using parent array
void printPath(vector <int> parent, int j)
{

    // Base Case : If j is source
    if (parent[j] == - 1)
        return;

    printPath(parent, parent[j]);

    cout << nodes[j].name << " ";
}
void printSolution(vector<int> dist, int start_label,int end_label, vector<int>parent)
{
        int x = end_label;
        cout << nodes[start_label].name << " ";
        printPath(parent, x);
        cout << dist[end_label] << endl;
}

void dijkstra(int **graph, int src, int end)
{

    int size = nodes.size();

    vector<int> dist(size);
    vector<bool> sptSet(size);
    vector<int> parent(size);

    // Initialize all distances as 
    // INFINITE and stpSet[] as false
    for (int i = 0; i < size; i++)
    {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance of source vertex 
    // from itself is always 0
    dist[src] = 0;

    // Find shortest path
    // for all vertices
    for (int count = 0; count < size - 1; count++)
    {
        // Pick the minimum distance
        // vertex from the set of
        // vertices not yet processed. 
        // u is always equal to src
        // in first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex 
        // as processed
        sptSet[u] = true;

        // Update dist value of the 
        // adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < size; v++)

            // Update dist[v] only if is
            // not in sptSet, there is
            // an edge from u to v, and 
            // total weight of path from
            // src to v through u is smaller
            // than current value of
            // dist[v]
            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            } 
    }

    // print the constructed
    // distance array
    printSolution(dist, src,end, parent);
}
void printNodes(vector<Node> &nodes) 
{
    for (int i = 0; i < nodes.size(); i++)
    {
        cout << nodes[i].name <<" "<<nodes[i].label<< endl;
    }
    
}
void detectForbiddenZone(int i, int max, int **graph)
{
    for (int j = 0; j < nodes.size(); j++)
    {
        if (graph[i][j] < max && graph[i][j] != 0)
        {
            forbidden.push_back(j);
        }
    }
    forbidden.push_back(i);
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
    string fname = "path_info_2.txt";
    ifstream city_plan(fname);

    string source;
    string destination;
    string _weight;
    int weight;
    Node *_source;
    Node *temp_source;
    Node *_destination;
    Node *temp_destination;
    int start_label;
    int end_label;

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

        if (source == "Ma")
            start_label = index1;
        if (destination == "Mo")
            end_label = index2;


        a[_source->label][_destination->label] = weight;
        a[_destination->label][_source->label] = weight;

    }


    int size = nodes.size();
    int **graph = new int*[size];

    for(int k = 0; k < size; ++k){
        graph[k] = new int[size];
        for (int m = 0; m < size; ++m)
        {
            graph[k][m] = a[k][m];
        }
    }

     //Free the memory by deleting nodes vector and temporarily created dynamic 2d array. 
 //       Free each sub-array
    for(int i = 0; i < 5; ++i) {
        delete[] a[i];   
    }
    //Free the array of pointers
    delete[] a;
    vector <int> enemy;
    printNodes(nodes);
    cout << "MATRIS:" << endl;
    for(int k = 0; k < size; ++k){
        for (int m = 0; m < size; ++m)
        {
            printf("%3d",graph[k][m]);
        }
        cout << endl;
    }
    for (int k = 0; k < nodes.size(); ++k)
    {
        if (!checkEnemyZone(nodes[k].name))
        {
            enemy.push_back(nodes[k].label);
        }
    }
    cout << " ENEMY:" << endl;
    for (int k = 0; k < enemy.size(); ++k)
    {
        cout << enemy[k]<< " ";
    }
    cout << endl;
    cout << "enemy size: " << enemy.size() << endl;
    cout << "Node size : "<< nodes.size() << endl;

    int enemy_size = enemy.size();
    cout << "************" << endl;

    for (int i = 0; i < enemy_size; ++i)
    {
        detectForbiddenZone(enemy[i],4,graph);
    }
    int forbidden_size1 = forbidden.size();
    cout << "forbidden size:" << forbidden_size1 << endl;
    for (int i = 0; i < forbidden_size1; ++i)
    {
        cout << "forbiddens : " << forbidden[i] << " " << endl;
    }

    cout << "************" << endl;


    for (int k = 0; k < forbidden.size();k++){
        for (int j = 0; j < 9; j++)
        {
        graph[forbidden[k]][j] = 0;
        graph[j][forbidden[k]] = 0;
        }
    }

    for(int k = 0; k < size; ++k){
        for (int m = 0; m < size; ++m)
        {
            printf("%3d",graph[k][m]);
        }
        cout << endl;
    }
    dijkstra(graph, start_label,end_label);
    return 0;
}
