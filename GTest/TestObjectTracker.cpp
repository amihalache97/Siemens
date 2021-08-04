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
	ObjectCounter::numberOfObjects = 0;
	ASSERT_EQUALS(ObjectCounter::numberOfObjects, 0);

    return 0;
}

void TestObjectTracker::tearDown(const std::string& iTestName)
{
	ObjectCounter::numberOfObjects = 0;
	ASSERT_EQUALS(ObjectCounter::numberOfObjects, 0);

}

void TestObjectTracker::testNode()
{
	GNode *pNa = new GNode("na");
	ASSERT_EQUALS(ObjectCounter::numberOfObjects, 1);

	delete pNa;
	ASSERT_EQUALS(ObjectCounter::numberOfObjects, 0);
}

void TestObjectTracker::testGraph()
{
	GGraph *pNa = new GGraph("na");
	ASSERT_EQUALS(ObjectCounter::numberOfObjects, 1);

	delete pNa;
	ASSERT_EQUALS(ObjectCounter::numberOfObjects, 0);
}

void TestObjectTracker::testNodeWithConnection()
{
	auto pNa = std::make_shared<GNode>("na");
	auto pNb = std::make_shared<GNode>("nb");
	auto pNc = std::make_shared<GNode>("nc");
	auto pNd = std::make_shared<GNode>("nd");
	auto pNdd = std::shared_ptr<GNode>(pNd);

	ASSERT_EQUALS(ObjectCounter::numberOfObjects, 4);

	pNa->connect(pNb);
	pNa->connect(pNc);
	pNa->connect(pNd);

	pNd.reset();
	ASSERT_EQUALS(ObjectCounter::numberOfObjects, 4);

	pNa->disconnect(pNdd);
	pNdd.reset();
	ASSERT_EQUALS(ObjectCounter::numberOfObjects, 3);

	pNb.reset();
	ASSERT_EQUALS(ObjectCounter::numberOfObjects, 3);

	pNa.reset();
	ASSERT_EQUALS(ObjectCounter::numberOfObjects, 1);

	pNc.reset();
	ASSERT_EQUALS(ObjectCounter::numberOfObjects, 0);
}

void TestObjectTracker::testGraphWithNodes()
{
	GGraph *G = new GGraph("G");
	auto A = G->addNode("A");
	auto B = G->addNode("B");

	ASSERT_EQUALS(ObjectCounter::numberOfObjects, 3);

	A.reset();
	ASSERT_EQUALS(ObjectCounter::numberOfObjects, 3);

	delete G;
	ASSERT_EQUALS(ObjectCounter::numberOfObjects, 1);

	B.reset();
	ASSERT_EQUALS(ObjectCounter::numberOfObjects, 0);
}
