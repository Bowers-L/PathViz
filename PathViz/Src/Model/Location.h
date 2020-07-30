#pragma once

#include <string>

#include "Vec3.h"

namespace model {

	class Location {
	private:
		std::string m_Label;
		vec3 m_Pos;

	public:
		Location();
		Location(std::string label, float x, float y);
		Location(std::string label, float x, float y, float z);

		~Location();

		const std::string& getLabel() const;
		const vec3& getPos() const;

		std::string toString() const;

		bool operator==(const Location& other) const;
		bool operator!=(const Location& other) const;

		static double calcDistance(const Location& u, const Location& v);
	};

}

//Implement hash function (needed to use set and map structures)
namespace std
{
	template<>
	struct hash<model::Location>
	{
		size_t
			operator()(const model::Location& obj) const
		{
			return hash<string>()(obj.getLabel());
		}
	};
}