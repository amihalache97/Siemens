#include "TestObjectTracker.h"

#include "../GAPI/GNode.h"
#include "../GAPI/GGraph.h"

TestObjectTracker::TestObjectTracker(void)
{
}

TestObjectTracker::~TestObjectTracker(void)
{
    tearDown("");
}


void TestObjectTracker::run()
{
    RUN_TEST(testNode);
    RUN_TEST(testGraph);
    RUN_TEST(testNodeWithConnection);
    RUN_TEST(testGraphWithNodes);
}

int TestObjectTracker::setUp(const std::string& iTestName)
{
    return 0;
}

void TestObjectTracker::tearDown(const std::string& iTestName)
{
}

void TestObjectTracker::testNode()
{
	GNode::count = 0;
	ASSERT_EQUALS(GNode::count, 0);

	GNode *pNa = new GNode("na");
	ASSERT_EQUALS(GNode::count, 1);

	delete pNa;
	ASSERT_EQUALS(GNode::count, 0);
}

void TestObjectTracker::testGraph()
{
	GGraph::count = 0;
	ASSERT_EQUALS(GGraph::count, 0);

	GGraph *pNa = new GGraph("na");
	ASSERT_EQUALS(GGraph::count, 1);

	delete pNa;
	ASSERT_EQUALS(GGraph::count, 0);
}

void TestObjectTracker::testNodeWithConnection()
{
	GGraph::count = 0;
	ASSERT_EQUALS(GGraph::count, 0);

	GNode *pNa = new GNode("na");
	GNode *pNb = new GNode("nb");
	GNode *pNc = new GNode("nc");
	GNode *pNd = new GNode("nd");

	ASSERT_EQUALS(GNode::count, 4);

	pNa->connect(pNb);
	pNa->connect(pNc);
	pNa->connect(pNd);

	pNd->deletion();
	ASSERT_EQUALS(GNode::count, 4);

	pNa->disconnect(pNd);
	ASSERT_EQUALS(GNode::count, 3);

	pNb->deletion();
	ASSERT_EQUALS(GNode::count, 3);

	pNa->deletion();
	ASSERT_EQUALS(GNode::count, 1);

	pNc->deletion();
	ASSERT_EQUALS(GNode::count, 0);
}

void TestObjectTracker::testGraphWithNodes()
{
	GNode::count = 0;
	ASSERT_EQUALS(GNode::count, 0);

	GGraph::count = 0;
	ASSERT_EQUALS(GGraph::count, 0);

	GGraph *G = new GGraph("G");
	GNode *A = G->addNode("A");
	GNode *B = G->addNode("B");

	ASSERT_EQUALS(GGraph::count + GNode::count, 3);
	

	A->deletion();
	ASSERT_EQUALS(GGraph::count + GNode::count, 3);

	G->deletion();
	ASSERT_EQUALS(GGraph::count + GNode::count, 1);

	B->deletion();
	ASSERT_EQUALS(GGraph::count + GNode::count, 0);
}
