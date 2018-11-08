#include <iostream>
#include <list>
#include <queue>


class Graph {
private:
	int V; // Number of vertices
	std::list<int> *adj;
	void DFSPrivate(int u, bool* visited);
	bool isCyclicPrivate(int u, bool* visited, int parent);

public:
	Graph(int V);
	void addEdge(int u, int v);
	void printGraph(void);
	void BFS(int u);
	void DFS(int u);
	bool isCyclic(void);
};

Graph::Graph(int V) {
	this->V = V;
	this->adj = new std::list<int>[V];
}

void Graph::addEdge(int u, int v) {
	if (u >= this->V || v >= this->V) {
		std::cout << "Graph overflow." << std::endl;
		return;
	}
	this->adj[u].push_back(v);
	if (u != v) {
		this->adj[v].push_back(u);
	}
}

void Graph::printGraph(void) {
	for (int i=0; i<this->V; i++) {
		if (this->adj[i].empty()) {
			continue;
		}
		int u = i;
		std::list<int>::iterator it;
		for (it=this->adj[i].begin(); it != this->adj[i].end(); it++) {
			int v = *it;
			std::cout << "(" << u << "," << v << ")" << " "; //std::end;
		}
		std::cout << std::endl;
	}
}

void Graph::BFS(int u) {
	if (u >= this->V || u < 0) {
		std::cout << "Invalid node to perform BFS: " << u << std::endl;
		return;
	}
	bool* visited = new bool[this->V];
	for (int i=0; i<this->V; i++)
		visited[i] = false;

	std::queue<int> nodesQueue;
	nodesQueue.push(u);
	visited[u] = 0;

	while (!nodesQueue.empty() ){
		int s = nodesQueue.front();
		nodesQueue.pop();
		std::cout << "BFS: Node: " << s << std::endl;
		std::list<int>::iterator it; 
		for (it= this->adj[s].begin(); it != this->adj[s].end(); it++) {
			if (!visited[*it]) {
				visited[*it] = true;
				nodesQueue.push(*it);
			}
		}
	}
}

void Graph::DFS(int u) {
	if (u > this->V || u < 0) {
		std::cout << "Invalid node to perform DFS: " << u << std::endl;
		return;
	}
	bool* visited = new bool[this->V];
	for (int i=0; i < this->V; i++) {
		visited[i] = false;
	}

	this->DFSPrivate(u, visited);
}

void Graph::DFSPrivate(int u, bool* visited) {
	visited[u] = true;
	std::cout << "DFS: " << u << std::endl;

	std::list<int>::iterator it;
	for (it=this->adj[u].begin(); it != this->adj[u].end(); it++) {
		if (!visited[*it])
			this->DFSPrivate(*it, visited);
	}
}

bool Graph::isCyclic(void) {
	bool* visited = new bool[this->V];

	for (int i=0; i < this->V; i++) 
		visited[i] = false;

	for (int i=0; i < this->V; i++) {
		if (this->adj[i].empty()) 
			continue;
		if (!visited[i] && this->isCyclicPrivate(i, visited, -10000) ) {
			delete []visited;
			return true;
		}
	}
	delete []visited;
	return false;
}

bool Graph::isCyclicPrivate(int u, bool* visited, int parent) {
	visited[u] = true;

	std::list<int>::iterator it;
	for (it=this->adj[u].begin(); it != this->adj[u].end(); it++) {
		if (!visited[*it]) {
			if (this->isCyclicPrivate(*it, visited, u))
				return true;
		} else {
			if (*it != parent)
				return true;
		}
	}
	return false;
}

int main(int argc, char* argv[]) {
	Graph g(4);
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(0,3);
	g.addEdge(3,2);
	g.printGraph();
	//g.BFS(0);
	//g.DFS(0);
	g.isCyclic() ? std::cout << "Cyclic graph.\n" : std::cout << "Non-cyclic graph.\n";

	return 0;
}