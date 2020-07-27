#pragma once

#include "Vertex.h"

namespace graph {

	class Edge
	{
	private:
		Vertex m_U, m_V;
		double m_Distance;

	public:

		Edge(Vertex u, Vertex v);

		const Vertex& getU() const;
		const Vertex& getV() const;
		double getDistance() const;

		std::string toString() const;

		bool operator==(const Edge& other) const;
	};

	//priority_queue by default is a max heap that uses a less than comparator
	//So I am implementing a greater than comparator to make it a min heap
	struct minHeapEdgeComp : std::binary_function <Edge, Edge, bool> {

		bool operator() (const Edge& x, const Edge& y) const {
			return (x.getDistance() > y.getDistance());
		}
	};
}


namespace std
{
	using namespace graph;

	//Implementation of hash function (needed to use set and map structures)
	template<>
	struct hash<graph::Edge>
	{
		size_t
			operator()(const graph::Edge& obj) const
		{
			return hash<string>()(obj.getU().getLabel()) * 11 + hash<string>()(obj.getV().getLabel());
		}
	};
}


