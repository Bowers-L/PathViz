#include "Vertex.h"

#include <cmath>

namespace graph {
	Vertex::Vertex()
		: m_Label("Unnamed Vertex"), m_Pos(0, 0, 0)
	{
	}

	Vertex::Vertex(const std::string& label, float x, float y)
		: m_Label(label), m_Pos(x, y, 0)
	{
	}

	Vertex::Vertex(const std::string& label, float x, float y, float z)
		: m_Label(label), m_Pos(x, y, z)
	{
	}

	Vertex::~Vertex()
	{
	}

	const std::string& Vertex::getLabel() const
	{
		return m_Label;
	}

	const vec3& Vertex::getPos() const
	{
		return m_Pos;
	}

	std::string Vertex::toString() const
	{
		return "(" + getLabel() + ", " + getPos().toString() + ")";
	}

	bool Vertex::operator==(const Vertex& other) const
	{
		return (getPos() == other.getPos());
	}
}