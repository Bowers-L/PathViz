#include "pch.h"
#include "CppUnitTest.h"

#include <Src/Model/Graph.h>



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace graph;

namespace UnitTests
{
	TEST_CLASS(GraphTests)
	{
	public:
		
		TEST_METHOD(TestInitializeGraph)
		{
			Set<Vertex> vertices = { {"A", 0, 0, 0}, {"B", 1, 1, 1} };
			Set<Edge> edges = { {{"A", 0, 0, 0}, {"B", 1, 1, 1}} };
		}
	};
}
