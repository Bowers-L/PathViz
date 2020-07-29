#include "Location.h"

#include <cmath>

namespace model {
	Location::Location()
		: m_Label("Unnamed"), m_Pos(0, 0, 0)
	{
	}

	Location::Location(const std::string& label, float x, float y)
		: m_Label(label), m_Pos(x, y, 0)
	{
	}

	Location::Location(const std::string& label, float x, float y, float z)
		: m_Label(label), m_Pos(x, y, z)
	{
	}

	Location::~Location()
	{
	}

	const std::string& Location::getLabel() const
	{
		return m_Label;
	}

	const vec3& Location::getPos() const
	{
		return m_Pos;
	}

	std::string Location::toString() const
	{
		return "(" + getLabel() + ", " + getPos().toString() + ")";
	}

	bool Location::operator==(const Location& other) const
	{
		return (getLabel().compare(other.getLabel()) == 0);
	}

	bool Location::operator!=(const Location& other) const 
	{
		return !(*this == other);
	}

	double Location::calcDistance(const Location& u, const Location& v)
	{
		return vec3::calcDistance(u.getPos(), v.getPos());
	}
}