#pragma once

#include "Vertex.h"
#include "Edge.h"
#include "VertDistPair.h"

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>

#define Set std::unordered_set
#define Map std::unordered_map
#define Vector std::vector
#define PQ std::priority_queue


namespace graph {

	class Graph {
	private:
		Set<Vertex> m_Vertices;
		Set<Edge> m_Edges;
		Map<Vertex, Vector<VertDistPair>> m_AdjList;
	public:
		Graph();
		Graph(Set<Vertex> vertices, Set<Edge> edges);

		~Graph();

		/*
		Adds vertex v to the graph as well as edges to all of its neighbors.
		If v is already in the graph, then it updates the neighbors.
		If 
		*/
		void addVertex(Vertex v, Vector<Vertex> neighbors);

		/*
		Adds an edge from u to v and properly updates adj list
		*/
		void addEdge(Vertex u, Vertex v);

		/*
		Adds an edge from labelU to labelV, assuming that they exist.
		If the vertices do not already exist in the graph, this function does nothing.
		*/
		void addEdge(std::string labelU, std::string labelV);

		/*
		Removes the vertex and all edges associated with it.
		*/
		void removeVertex(Vertex v);

		/*
		Getters for member fields
		*/
		const Set<Vertex>& getVertices() const;
		const Set<Edge>& getEdges() const;

		/*
		Finds the vertex in the graph with the given label and returns it
		*/
		const Vertex& getLabeledVertex(std::string label) const;

		/*
			Returns the minimum spanning tree of this graph
		*/
		Set<Edge> getMST(Vertex start) const;

		std::string getMSTDesc(Vertex start) const;

		std::string toString() const;

		/*
		Gets the total distance (sum of weights) of a set of edges.
		*/
		static double totalDistance(const Set<Edge>& edges);

	private:
		void constructAdjList();
		void addEdgeToAdjList(const Edge& e);
	};

}