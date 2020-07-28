#include "Path.h"

namespace model {
	Path::Path(Location u, Location v)
		:m_U(u), m_V(v)
	{
		m_Distance = vec3::calcDistance(u.getPos(), v.getPos());
	}

	const Location& Path::getU() const
	{
		return m_U;
	}

	const Location& model::Path::getV() const
	{
		return m_V;
	}

	double Path::getDistance() const
	{
		return m_Distance;
	}

	std::string Path::toString() const
	{
		return "From " + getU().getLabel() + " To " + getV().getLabel() + " In " + std::to_string(getDistance());
	}

	bool Path::operator==(const Path& other) const
	{
		//Paths with the vertices reversed are considered the same Path
		return (((m_U == other.m_U) && (m_V == other.m_V)) 
			|| ((m_U == other.m_V) && (m_V == other.m_U)))
			&& (m_Distance == other.m_Distance);
	}
}



