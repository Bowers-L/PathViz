#pragma once

#include <string>

namespace model {

	struct vec3 {
		double x, y, z;

		vec3(double x, double y, double z);

		static double calcDistance(const vec3& u, const vec3& v);

		std::string toString() const;

		bool operator==(const vec3& other) const;
		bool operator!=(const vec3& other) const;
	};
}

//Implement hash function (needed to use set and map structures)
namespace std
{
	template<>
	struct hash<model::vec3>
	{
		size_t
			operator()(const model::vec3& obj) const
		{
			double prime = 11.0;
			return (size_t) (((obj.x*prime) + obj.y) * prime + obj.z);
		}
	};
}
