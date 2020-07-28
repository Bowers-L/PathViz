#include "LocDistPair.h"

namespace model
{
	LocDistPair::LocDistPair(Location location, double distance)
		: loc(location), dist(distance)
	{

	}
	std::string LocDistPair::toString() const
	{
		return "Vertex: " + loc.getLabel() + " Distance To: " + std::to_string(dist);
	}
}
