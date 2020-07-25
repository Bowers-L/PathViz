#pragma once

#include "Vertex.h"

namespace graph {

	class Edge
	{
	private:
		const Vertex m_U, m_V;
		double m_Distance;

	public:

		Edge(Vertex u, Vertex v);

		Vertex getU() const;
		Vertex getV() const;
		double getDistance() const;

		bool operator==(const Edge& other) const;
	};
}

//Implement hash function (needed to use set and map structures)
namespace std
{
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


