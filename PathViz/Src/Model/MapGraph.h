#pragma once

#include "Location.h"
#include "Path.h"
#include "Route.h"
#include "LocDistPair.h"

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>
#include <forward_list>

#define Set std::unordered_set
#define Map std::unordered_map
#define Vector std::vector
#define PQ std::priority_queue
#define SLL std::forward_list


namespace model {

	/*
	A spacial map modeled as a graph structure.
	The map can be used as a 2D or 3D map depending on which 
	location constructor is used.
	*/
	class MapGraph {
	private:
		Set<Location> m_Locations;
		Set<Path> m_Paths;
		Map<Location, Vector<LocDistPair>> m_AdjList;
	public:
		MapGraph();
		MapGraph(Set<Location> locations, Set<Path> paths);

		~MapGraph();

		/*
		Adds Location v to the graph as well as Paths to all of its neighbors.
		If v is already in the graph, then it updates the neighbors.
		If 
		*/
		void addLocation(Location v, Vector<Location> neighbors);

		/*
		Adds a Path from u to v and properly updates adj list
		*/
		void addPath(Location u, Location v);

		/*
		Adds a Path from labelU to labelV, assuming that they exist.
		If the Locations do not already exist in the graph, this function does nothing.
		*/
		void addPath(std::string labelU, std::string labelV);

		/*
		Removes the Location and all Paths associated with it.
		*/
		void removeLocation(Location v);

		/*
		Finds the shortest path from start to dest using the A* algorithm.
		*/
		Route findShortestPathFromTo(const Location& start, const Location& dest);
		Route findShortestPathFromTo(const std::string& start, const std::string& dest);

		/*
		Basic getters for member fields
		*/
		const Set<Location>& getLocations() const;
		const Set<Path>& getPaths() const;

		/*
			Returns the minimum spanning tree of this graph
		*/
		Set<Path> getMST(Location start) const;

		std::string getMSTDesc(const Set<Path>& mst) const;

		std::string toString() const;

		/*
		Gets the total distance (sum of weights) of a set of Paths.
		*/
		static double totalDistance(const Set<Path>& paths);

	private:
		const Location* findLocation(const std::string& label);
		void constructAdjList();
		void addPathToAdjList(Path p);
	};

}