#pragma once

#include "Path.h"

#include <forward_list>

#define SLL std::forward_list

namespace model {

	/*
	Container class for a SLL of paths
	*/
	class Route {
	private:
		const Location& m_Start;
		const Location& m_Dest;
		SLL<Path> *m_Paths;

	public:
		Route(const Location& start, const Location& dest, SLL<Path>* paths);

		const SLL<Path> *getPaths() const;

		const std::string& routeDesc() const;
	};





}
