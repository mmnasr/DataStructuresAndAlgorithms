#include <iostream>
#include <map>
#include <set>
#include <deque>

using namespace std;

class Graph {
private:
	map<int, set<int> > adj;
	bool hasVertexPrivate(int v);
	void printDFSPrivate(int s, bool* visited);

public:
	void addEdge(int v, int w);
	void printEdges(int v);
	int countNodes(void);
	void printBFS(int s);
	void printDFS(int s);
};

void Graph::addEdge(int v, int w) {
	this->adj[v].insert(w);
	if (v != w)
		this->adj[w].insert(v);
}

bool Graph::hasVertexPrivate(int v) {
	if (this->adj.find(v) != this->adj.end())
		return true;
	return false;
}

void Graph::printEdges(int v) {
	if (!this->hasVertexPrivate(v)) {
		cout << "Vertex "<<v<<" doesn't exist in the graph." << endl;
		return;
	}
	set<int>::iterator it;
	for (it = this->adj[v].begin(); it != this->adj[v].end(); it++) {
		cout << "(" << v << "," << *it << ")  ";
	}
	cout << endl;
}

int Graph::countNodes(void) {
	return this->adj.size();
}

void Graph::printBFS(int s) {
	int nNodes = this->countNodes();
	bool* visited = new bool[nNodes];
	for (int i=0; i < nNodes; i++)
		visited[i] = false;

	deque<int> q;
	visited[s] = true;
	q.push_back(s);

	while (!q.empty()) {
		int n = q.front();
		cout << "BFS-Vertex: " << n << endl;
		q.pop_front();

		set<int>::iterator it;
		for (it=this->adj[n].begin(); it != this->adj[n].end(); it++) {
			int neighbor = *it;
			if (!visited[neighbor]) {
				visited[neighbor] = true;
				q.push_back(neighbor);
			}
		}
	}
	delete []visited;
}

void Graph::printDFS(int s) {
	int nNodes = this->countNodes();
	bool* visited = new bool[nNodes];

	for (int i=0; i < nNodes; i++) 
		visited[i] = false;

	printDFSPrivate(s, visited);
	delete []visited;
}

void Graph::printDFSPrivate(int s, bool* visited) {
	visited[s] = true;
	cout << "DFS-Vertex: " << s << endl;

	set<int>::iterator it;
	for (it=this->adj[s].begin(); it != this->adj[s].end(); it++) {
		if (!visited[*it])
			printDFSPrivate(*it, visited);
	}
}

int main(int argc, char* argv[]) {
	Graph g;
	g.addEdge(1,0);
	g.addEdge(1,2);
	g.addEdge(2,3);
	// g.addEdge(2,3);

	g.printEdges(1);
	cout << "Nodes: " << g.countNodes() << endl;
	g.printBFS(1);
	g.printDFS(1);

	return 0;
}