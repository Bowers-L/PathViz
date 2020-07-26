#include "VertDistPair.h"

namespace graph
{
	VertDistPair::VertDistPair(Vertex vertex, double distance)
		: vertex(vertex), distance(distance)
	{

	}
	std::string VertDistPair::toString() const
	{
		return "Vertex: " + vertex.getLabel() + " Distance To: " + std::to_string(distance);
	}
}
