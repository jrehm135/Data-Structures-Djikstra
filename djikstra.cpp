// implement the propagate application here
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

#include "heap_priority_queue.h"

struct NumWeight
{
	int number;
	int weight;
	friend bool operator<(NumWeight& left, NumWeight& right)
	{
		return left.weight < right.weight;
	}
	friend bool operator>(NumWeight& left, NumWeight& right)
	{
		return left.weight > right.weight;
	}
	friend bool operator<=(NumWeight& left, NumWeight& right)
	{
		return left.weight <= right.weight;
	}
	friend bool operator>=(NumWeight& left, NumWeight& right)
	{
		return left.weight >= right.weight;
	}
	friend bool operator==(NumWeight& left, NumWeight& right)
	{
		return left.weight == right.weight;
	}

};

typedef std::pair<int, int> numWeight;

class Graph
{
	int V; //number of vertices

	//vertex pairs for edges
	std::vector<std::pair<int, int>> *adj;

public:
	Graph(int V);  // Constructor

	void addEdge(int u, int v, int w);

	void shortestPath(int s);
};

// Allocates memory for adjacency list
Graph::Graph(int V)
{
	this->V = V;
	adj = new std::vector<numWeight>[V];
}

void Graph::addEdge(int u, int v, int w)
{
	adj[u].push_back(std::make_pair(v, w));
}

void Graph::shortestPath(int src)
{
	// Priority Queue for numbers and weights
	HeapPriorityQueue<NumWeight> pq;
	NumWeight nw;

	// Create a vector for distances and initialize all
	// distances as a large number
	std::vector<int> dist(V, 1000000);

	// Insert source itself in priority queue and initialize
	// its distance as 0.
	nw.number = src;
	nw.weight = 0;
	pq.add(nw);
	dist[src] = 0;

	// Looping till priority queue becomes empty
	while (!pq.isEmpty())
	{
		//number and weight of the minimum distance vertex
		int u = pq.peek().number;
		int w = pq.peek().weight;
		pq.remove();
		if (w < dist[u])
			dist[u] = w;


		// 'i' is used to get all adjacent vertices of a vertex
		std::vector< std::pair<int, int> >::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); ++i)
		{
			// Get vertex label and weight of current adjacent
			// of u.
			int v = (*i).first;
			int weight = (*i).second;

			//  If there is shorted path to v through u.
			if (dist[v] > dist[u] + weight)
			{
				// Updating distance of v
				dist[v] = dist[u] + weight;
				nw.number = v;
				nw.weight = dist[v];
				pq.add(nw);
			}
		}
	}
	//opens an ofstream to write the shortest path
	std::ofstream weightFile("weight.csv");
	for (int i = 0; i < V; ++i)
	{
		weightFile << dist[i];
		if (i != V - 1)
			weightFile << ",";
	}

}

int main(int argc, char *argv[])
{
	std::ifstream graphFile("graph.csv");
	if (!graphFile.good())
	{
		std::cerr << "No input file";
		return EXIT_FAILURE;
		//if the input file doesn't exist, exits the program
	}
	std::string num;
	std::string weight;
	int locU = 0;
	int numLines = 0;
	std::string unused;
	while (std::getline(graphFile, unused))
		++numLines;
	//reads in the number of vertices in the graph

	graphFile.close();
	graphFile.open("graph.csv");
	//resets the buffer for the file
	Graph g(numLines);
	
	while (std::getline(graphFile, num,','))
	{
		//reads in the number and checks to see if the file has ended
		if (num == "\n")
			break;
		std::getline(graphFile, weight, ',');
		//gets the corresponding weight to the number
		int fin = weight.find('\n');
		int intNum = std::stoi(num);
		int intWeight = std::stoi(weight);
		g.addEdge(locU, intNum, intWeight);
		//adds an edge for the current number and weight
		if (fin != -1)
		{
			graphFile.seekg(-2, graphFile.cur);
			locU++;
			//sets the buffer 2 places back, allowing for another getline, then increments the current vertex
		}
	}
	g.shortestPath(0);
}

