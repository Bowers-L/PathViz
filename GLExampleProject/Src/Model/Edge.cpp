#include "Edge.h"

namespace graph {
	Edge::Edge(Vertex u, Vertex v)
		:m_U(u), m_V(v)
	{
		m_Distance = vec3::calcDistance(u.getPos(), v.getPos());
	}

	const Vertex& Edge::getU() const
	{
		return m_U;
	}

	const Vertex& graph::Edge::getV() const
	{
		return m_V;
	}

	double Edge::getDistance() const
	{
		return m_Distance;
	}

	std::string Edge::toString() const
	{
		return "From " + getU().getLabel() + " To " + getV().getLabel() + " In " + std::to_string(getDistance());
	}

	bool Edge::operator==(const Edge& other) const
	{
		//Edges with the vertices reversed are considered the same edge
		return (((m_U == other.m_U) && (m_V == other.m_V)) 
			|| ((m_U == other.m_V) && (m_V == other.m_U)))
			&& (m_Distance == other.m_Distance);
	}
}



