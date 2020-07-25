#pragma once

#include <string>

#include "Vec3.h"

namespace graph {

	class Vertex {
	private:
		std::string m_Label;
		vec3 m_Pos;

	public:
		Vertex();
		Vertex(const std::string& label, float x, float y);
		Vertex(const std::string& label, float x, float y, float z);

		~Vertex();

		const std::string& getLabel() const;
		vec3 getPos() const;

		bool operator==(const Vertex& other) const;
	};

}

//Implement hash function (needed to use set and map structures)
namespace std
{
	template<>
	struct hash<graph::Vertex>
	{
		size_t
			operator()(const graph::Vertex& obj) const
		{
			return hash<string>()(obj.getLabel());
		}
	};
}