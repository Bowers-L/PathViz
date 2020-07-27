#include "Graph.h"

#include <sstream>

namespace graph {

	
	Graph::Graph() 
		: m_Vertices(Set<Vertex>()), m_Edges(Set<Edge>()), m_AdjList(Map<Vertex, Vector<VertDistPair>>())
	{

	}

	Graph::Graph(Set<Vertex> vertices, Set<Edge> edges)
		: m_Vertices(vertices), m_Edges(edges), m_AdjList(Map<Vertex, Vector<VertDistPair>>())
	{
		constructAdjList();
	}

	Graph::~Graph()
	{
	}

	
	void Graph::addVertex(Vertex v, Vector<Vertex> neighbors)
	{
		//Add v to the Vertex set
		if (m_Vertices.find(v) == m_Vertices.end()) {
			m_Vertices.insert(v);
			m_AdjList[v] = Vector<VertDistPair>();
		}

		//Construct new edges based on the neighbors
		for (Vertex neighbor : neighbors) {
			m_Vertices.insert(neighbor);
			m_AdjList[neighbor] = Vector<VertDistPair>();

			Edge e = Edge(v, neighbor);

			m_Edges.insert(e);

			addEdgeToAdjList(e);
		}
	}

	void Graph::addEdge(Vertex u, Vertex v)
	{
		Edge e = { u, v };
		m_Edges.insert(e);

		addEdgeToAdjList(e);
	}

	void Graph::addEdge(std::string labelU, std::string labelV)
	{
		Vertex u;
		Vertex v;

		bool foundU = false;
		bool foundV = false;
		
		for (Vertex vert : m_Vertices) {
			if (labelU.compare(vert.getLabel()) == 0) {
				u = vert;
				foundU = true;
			}

			if (labelV.compare(vert.getLabel()) == 0) {
				v = vert;
				foundV = true;
			}

			if (foundU && foundV) {
				break;
			}
		}

		if (foundU && foundV) {
			addEdge(u, v);
		}
	}

	void Graph::removeVertex(Vertex v)
	{
		//Erase the vertex
		m_Vertices.erase(v);

		//Erase all edges associated with the vertex
		for (Edge e : m_Edges) {
			if (e.getU() == v || e.getV() == v) {
				m_Edges.erase(e);
			}
		}

		//Erase all map entries that contain the vertex
		/*
		For example, deleting D from the following map
		would require removing the key D from the map
		and removing all VertDist pairs with D

		A -> (B, 5), (C, 6), (D, 4)
		B -> (A, 5), (C, 2), (D, 1)
		C -> (A, 6), (B, 2), (D, 3)
		D -> (A, 4), (B, 1), (C, 3)

		A -> (B, 5), (C, 6)
		B -> (A, 5), (C, 2)
		C -> (A, 6), (B, 2)
		*/


		for (VertDistPair vd : m_AdjList[v]) {
			Vector<VertDistPair>& neighborList = m_AdjList[vd.vertex];
			for (Vector<VertDistPair>::iterator it = neighborList.begin(); it != neighborList.end(); it++) {
				if (it->vertex == v) {
					neighborList.erase(it);
				}
			}
		}

		m_AdjList.erase(v);
	}

	const Set<Vertex>& Graph::getVertices() const
	{
		return m_Vertices;
	}

	const Set<Edge>& Graph::getEdges() const
	{
		return m_Edges;
	}

	const Vertex& Graph::getLabeledVertex(std::string label) const
	{
		for (Vertex v : m_Vertices) {
			if (label.compare(v.getLabel()) == 0) {
				return v;
			}
		}
	}

	Set<Edge> Graph::getMST(Vertex start) const
	{
		//Returns a minimum spanning tree of this graph
		//using Prim's algorithm (requires a starting vertex)

		//Keep track of vertices that have been visited 
		Set<Vertex> visited = Set<Vertex>();

		//Output set
		Set<Edge> mst = Set<Edge>();

		//Min. priority queue of all the considered edges
		auto queue = PQ<Edge, Vector<Edge>, minHeapEdgeComp>();

		//Add all edges from the start to the queue
		//Need this messy const_cast syntax because the [] operator isn't allowed on const maps
		//even though the map is not being modified
		for (VertDistPair vd : (*const_cast<Map<Vertex, Vector<VertDistPair>>*>(&m_AdjList))[start]) {
			queue.push(Edge(start, vd.vertex));
		}
		visited.insert(start);

		//Still items in the queue and have not visited all of the vertices yet
		while (queue.size() > 0 && visited.size() != m_Vertices.size()) {

			Edge currEdge = queue.top();	//Get reference to the edge
			queue.pop();	//Remove the edge from the queue
			Vertex currVert = currEdge.getV();


			if (visited.find(currVert) == visited.end()) {

				//Add the edge to the mst if the destination vertex hasn't been visited yet
				visited.insert(currVert);
				mst.insert(Edge(currEdge));

				//Push all edges from currVert to vertices that haven't been visited yet
				for (VertDistPair vd : (*const_cast<Map<Vertex, Vector<VertDistPair>>*>(&m_AdjList))[currVert]) {
					if (visited.find(vd.vertex) == visited.end()) {
						queue.push(Edge(currVert, vd.vertex));
					}

				}
			}
		}

		return mst;
	}

	std::string Graph::getMSTDesc(Vertex start) const
	{
		Set<Edge> mst = getMST(start);
		std::string retVal = "";

		for (Edge e : mst) {
			retVal += e.toString() + "\n";
		}

		return retVal;
	}

	std::string Graph::toString() const
	{
		std::string retVal = "";

		retVal += "Vertices: \n";
		for (Vertex v : m_Vertices) {
			retVal += v.toString();
			retVal += "\n";
		}

		retVal += "\nEdges: \n";
		for (Edge e : m_Edges) {
			retVal += e.toString();
			retVal += "\n";
		}

		retVal += "\nAdjacency List: \n";
		for (auto pair : m_AdjList) {
			retVal += pair.first.toString();
			retVal += "\n";

			for (VertDistPair vd : pair.second) {
				retVal += "\t" + vd.toString() + "\n";
			}
			retVal += "\n";
		}

		return retVal;
	}
	
	double Graph::totalDistance(const Set<Edge>& edges)
	{
		double total = 0;
		for (Edge e : edges) {
			total += e.getDistance();
		}

		return total;
	}

	void Graph::constructAdjList()
	{
		for (Vertex v : m_Vertices)
		{
			//Add vertices to the map with empty lists
			m_AdjList[v] = Vector<VertDistPair>();
		}

		for (Edge e : m_Edges) {	
			//Populate the adj list based on the graph's edges.
			if (m_AdjList.find(e.getU()) != m_AdjList.end()) {
				m_AdjList[e.getU()].push_back(VertDistPair(e.getV(), e.getDistance()));
			}
		}
	}

	//Need to call this every time an edge is added to the graph
	void Graph::addEdgeToAdjList(const Edge& e)
	{
		//Adds an entry into the adj list for both vertices in the edge
		m_AdjList[e.getU()].push_back(VertDistPair(e.getV(), e.getDistance()));
		m_AdjList[e.getV()].push_back(VertDistPair(e.getU(), e.getDistance()));
	}
	
}