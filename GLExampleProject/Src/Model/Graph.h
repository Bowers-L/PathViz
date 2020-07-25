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

		void addVertex(Vertex v, Vector<Vertex> neighbors);

		void removeVertex(Vertex v);

		Set<Edge> getMST(Vertex start);

	private:
		void constructAdjList();


	};

}