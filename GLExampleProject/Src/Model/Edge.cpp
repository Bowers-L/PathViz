#include "Edge.h"

namespace graph {
	Edge::Edge(Vertex u, Vertex v)
		:m_U(u), m_V(v)
	{
		m_Distance = vec3::calcDistance(u.getPos(), v.getPos());
	}

	Vertex Edge::getU() const
	{
		return Vertex();
	}

	Vertex graph::Edge::getV() const
	{
		return Vertex();
	}

	double Edge::getDistance() const
	{
		return m_Distance;
	}

	bool Edge::operator==(const Edge& other) const
	{
		return (m_U == other.m_U) && (m_V == other.m_V) && (m_Distance == other.m_Distance);
	}
}



