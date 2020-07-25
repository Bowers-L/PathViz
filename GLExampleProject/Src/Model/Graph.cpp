#include "Graph.h"

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

			Edge e = Edge(v, neighbor);

			m_Edges.insert(e);

			m_AdjList[v].push_back(VertDistPair(neighbor, e.getDistance()));
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

	Set<Edge> Graph::getMST(Vertex start)
	{
		//Returns a minimum spanning tree of this graph
		//using Prim's algorithm

		//Keep track of vertices that have been visited 
		Set<Vertex> visited = Set<Vertex>();

		Set<Edge> mst = Set<Edge>();

		PQ<Edge> queue = PQ<Edge>();

		for (VertDistPair vd : m_AdjList[start]) {
			queue.push(Edge(start, vd.vertex));
		}
		visited.insert(start);

		//Still items in the queue and have not visited all of the vertices yet
		while (queue.size() > 0 && visited.size() != m_Vertices.size) {

			Edge currEdge = queue.top();
			queue.pop();
			Vertex currVert = currEdge.getV();

			if (visited.find(currVert) == visited.end()) {
				visited.insert(currVert);
				mst.insert(currEdge);

				for (VertDistPair vd : m_AdjList[currVert]) {
					if (visited.find(currVert) == visited.end()) {
						queue.push(Edge(currVert, vd.vertex));
					}

				}
			}


		}

		return mst;
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
	
}