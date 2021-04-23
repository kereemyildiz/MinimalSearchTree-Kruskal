#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits.h>

# define MAX_DISTANCE 5

using namespace std;

class Node {
    public:
        int label;
        string name;
        static int count;
        Node(string name);
};

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
int Node::count = 0;
vector<Node> nodes;
vector<int> forbidden;

bool checkEnemyZone(string name)
{
    string enemy = "E";
    size_t found = name.find(enemy);

    if (found != std::string::npos)
        return false;
    return true;
}
int nearestDistance(vector<int> distance, vector<bool> isTraversed)
{
    // Initialize min value
    int min = INT_MAX; // highest value at the beginning
    int index;

    for (unsigned int i = 0; i < nodes.size(); i++)
        if (isTraversed[i] == false && distance[i] <= min) // if it is not traversed and nearest, we will choose it.
        {
            index = i; 
            min = distance[i];
        }
    return index;
}

// Function to print shortest
// path from source to j
// using parent array
void printRecursive(vector <int> parent, int j)
{

    // Base Case : If j is source
    if (parent[j] == - 1)
        return;

    printRecursive(parent, parent[j]);

    cout << nodes[j].name << " ";
}
void printPath(vector<int> distance, int start_label,int end_label, vector<int>parent)
{
        int x = end_label;
        cout << nodes[start_label].name << " ";
        printRecursive(parent, x);
        cout << distance[end_label] << endl;
}

void ShortestPath(int **graph, int start, int end)
{

    int size = nodes.size();

    // Every node (place) has a label which equals to the its index number inside the 'nodes' vector

    // We are going to create distance vector which stores the distance information between the place with current index and starting point(Ma)
    // For example, Ma:0, S1:1 , S2:2, etc. and distance[] = {0,2,4} which means Ma-S1 path 2 has 2 weight and Ma-S2 has 4 weight
    // Also, we will store the parents of every place in order to avoiding cycles

    vector<int> distance(size); 
    vector<bool> isTraversed(size);
    vector<int> parent(size);

    parent[start] = -1; // root node's parent is -1

    for (int i = 0; i < size; i++) // All distances are infinite and not traversed at the beginning.
    {
        distance[i] = INT_MAX; 
        isTraversed[i] = false;
    }

    distance[start] = 0; // Distance of starting point from itself must be 0.

    // We are going to apply Dijkstra's algorithm
    // We will check every node, then decide which is the nearest to choose.
    for (int count = 0; count < size - 1; count++)
    {
        int source = nearestDistance(distance, isTraversed); // Chosen distance must be not traversed (otherwise, cycle exist)
                                                            // and we must choose nearest neighbour or starting point at the beginning

        isTraversed[source] = true; // We mark as true the node which we are traversing from.

        // Now, we need to traverse all places and find the ones which satisfies requirements (has a connection with source, not traversed etc.)
        for (int i = 0; i < size; i++)

            if (!isTraversed[i] && graph[source][i] && distance[source] + graph[source][i] < distance[i])
            {
                parent[i] = source; // we mark i'th element as child of source because there is a connection 
                distance[i] = distance[source] + graph[source][i]; // update the distance vector, we find shortest path.
            } 
    }
    // print the constructed
    // distance array
    printPath(distance, start ,end, parent);
}
void printNodes(vector<Node> &nodes) 
{
    for (unsigned int i = 0; i < nodes.size(); i++)
    {
        cout << nodes[i].name <<" "<<nodes[i].label<< endl;
    }
    
}
void detectForbiddenZone(int i, int max, int **graph,unsigned int start_label)
{
    for (unsigned int j = 0; j < nodes.size(); j++)
    {
        if (graph[i][j] < max && graph[i][j] != 0 && j != start_label )
        {
            forbidden.push_back(j);
        }
    }
    forbidden.push_back(i);
}
int main()
{
                        // We dont know node number in advance.So, we cannot create static array.
                        // Also, we didnt create dynamic array for nodes which cannot perform
                        // assign operation according to given input.(i.e : a[i][j] = 5 ). With given i and j
                        // it cannot perform. We can solve this situation by other methods which are time consuming.
                        // To perform this algorithm, I choose speed rather than memory allocation.
                        // Firstly, we are going to choose big number and then free the memory.


    int rowCount = 1000;                     
    int colCount = 1000;
    int** temp_array = new int*[rowCount];

    for(int i = 0; i < rowCount; ++i){ // All elements filled with 0
        temp_array[i] = new int[colCount];
        for (int j = 0; j < colCount; ++j)
        {
            temp_array[i][j] = 0;
        }
    }


    nodes.reserve(1000); // since we are not know the node size, initially, we reserve some memory
                        // After file read operation done, we are going to free the memory.
                        //it can help the vector avoid repeatedly allocating memory (and having to move the data to the new memory).
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
    int start_label;
    int end_label;

    while (city_plan.good())
    {
        getline(city_plan, source, ',');
        getline(city_plan, destination, ',');
        getline(city_plan, _weight, '\n');
        weight = stod(_weight);

        unsigned int index1 = containsName(nodes, source); // if node is already added to nodes vector. We use this function in order to evaluate a set. (Unique nodes)
        if (index1 == nodes.size()) // If it return its size, this means it cannot find a node with the given name. 
        {                           // Therefore it is going to add.
            temp_source = new Node(source);
            nodes.push_back(*temp_source);
            _source = &nodes[index1];
        }
        else
        {
            _source = &nodes[index1]; // If it is already added in nodes vector, we take its address and do some operation on it.
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

        if (source == "Ma") // evaluating start and end label
            start_label = index1;
        if (destination == "Mo")
            end_label = index2;

        temp_array[_source->label][_destination->label] = weight; // filling the array with given source, destination and weight inputs.
        temp_array[_destination->label][_source->label] = weight;
    }

    int size = nodes.size(); // we evaluate the size of nodes.
    int **graph = new int*[size]; // grpah initialized

    for(int k = 0; k < size; ++k){
        graph[k] = new int[size];
        for (int m = 0; m < size; ++m)
        {
            graph[k][m] = temp_array[k][m]; // copying values from temp_array to graph
        }
    }

     //Free the memory by deleting nodes vector and temporarily created dynamic 2d array. 
    // Free each sub-array
    for(int i = 0; i < size; ++i) {
        delete[] temp_array[i];   
    }
    //Free the array of pointers
    delete[] temp_array;


    vector <int> enemy; // we will store the enemy spot's labels in there.

    for (unsigned int k = 0; k < nodes.size(); ++k) // nodes vector contains every place and place's information( name, label)
                                                    // label is assigned to all places when creating phase. All of them have unique integer label value.
    {
        if (!checkEnemyZone(nodes[k].name)) // if place is enemy spot which means is it containing 'E' or not.
        {
            enemy.push_back(nodes[k].label); // if it is enemy spot, then add it to the enemy vector.
        }
    }

    // We found the enemy spots.
    // Now, we will going to find spots which has a distance smaller than 5 with enemy spots. 
    for (unsigned int i = 0; i < enemy.size(); ++i)
    {
        detectForbiddenZone(enemy[i],MAX_DISTANCE,graph,start_label); // we call this function for each enemy spot.
                                                                    // This function going to change the graph.
                                                                    // It will fill with zeros all row and column of forbidden spots.
    }

    for (unsigned int k = 0; k < forbidden.size();k++){ // Fill with zero of forbidden spots (enemy spots and close spots to the enemy spots)
        for (int j = 0; j < size; j++)
        {
        graph[forbidden[k]][j] = 0;
        graph[j][forbidden[k]] = 0;
        }
    }

    // Graph is evaluated properly
    ShortestPath(graph, start_label,end_label);
    return 0;
}
