#include "TestGraph.h"
#include "../GAPI/GGraph.h"
#include "../GAPI/GNode.h"


TestGraph::TestGraph(void)
{
}

TestGraph::~TestGraph(void)
{
}


void TestGraph::run()
{
    RUN_TEST(testConstruct);
    RUN_TEST(testAddNode);
    RUN_TEST(testRemoveNode);
    RUN_TEST(testNodeAccess);
    RUN_TEST(testSaveLoad);
}

//
//
//
int TestGraph::setUp(const std::string& iTestName)
{
    return 0;
}

//
//
//
void TestGraph::tearDown(const std::string& iTestName)
{
}

//
//
//
void TestGraph::testConstruct()
{
    GGraph *pGraph = new GGraph("ga");
    ASSERT_NOT_EQUALS(pGraph, NULL);
    ASSERT_EQUALS(pGraph->getNumNodes(), 0);
	ASSERT_EQUALS(pGraph->getName(), "ga");
}

//
//
//
void TestGraph::testAddNode()
{
    GGraph *pGraph = new GGraph("ga");
    ASSERT_NOT_EQUALS(pGraph, NULL);
    int numNodes = pGraph->getNumNodes();
    
    ASSERT_EQUALS(pGraph->addNode(""), NULL);

	std::shared_ptr<GNode> pNode_na = pGraph->addNode("na");
    ASSERT_NOT_EQUALS(pNode_na, NULL);
    ASSERT_EQUALS(pGraph->getNumNodes(), numNodes + 1);

    pNode_na = NULL;

    pNode_na = pGraph->addNode("na");
    ASSERT_EQUALS(pNode_na, NULL);
    ASSERT_EQUALS(pGraph->getNumNodes(), numNodes + 1);
    pGraph = NULL;

}

//
//
//
void TestGraph::testRemoveNode()
{
    GGraph *pGraph = new GGraph("ga");
    ASSERT_EQUALS(pGraph->removeNode(""), RC_ParameterError);
    ASSERT_EQUALS(pGraph->removeNode("na"), RC_ValueError);
    
    pGraph->addNode("na");
    int numNodes = pGraph->getNumNodes();
    
    ASSERT_EQUALS(pGraph->removeNode("na"), RC_OK);
    ASSERT_EQUALS(pGraph->getNumNodes(), numNodes - 1);
    
    ASSERT_EQUALS(pGraph->removeNode("na"), RC_ValueError);
}


void TestGraph::testNodeAccess()
{
    GGraph *pGraph = new GGraph("ga");
    ASSERT_EQUALS(pGraph->getNode("na"), NULL);
	std::shared_ptr<GNode> pNode = pGraph->addNode("na");
    ASSERT_EQUALS(pGraph->getNode("na"), pNode);
}

void TestGraph::testSaveLoad()
{
	GGraph *pGraph = new GGraph("ga");

	auto pNode_na = pGraph->addNode("na");
	auto pNode_nb = pGraph->addNode("nb");
	auto pNode_nc = pGraph->addNode("nc");

	pNode_na->connect(pNode_nb);
	pNode_na->connect(pNode_nc);
	pNode_nb->connect(pNode_nc);

	pGraph->save("file.txt");

	GGraph *pGraph2 = new GGraph("");
	pGraph2->load("file.txt");

	ASSERT_EQUALS(pGraph2->getName(), "ga");
	ASSERT_EQUALS(pGraph2->getNumNodes(), 3);

	std::shared_ptr<GNode> intermediarNode = pGraph2->getNode("na");
	ASSERT_NOT_EQUALS(intermediarNode, NULL);
	int numberConectedTo = intermediarNode->getNumConnectedTo();
	ASSERT_EQUALS(numberConectedTo, 2);
	std::shared_ptr<GNode> conectionNode = intermediarNode->getNodeAtIndex(0);
	ASSERT_NOT_EQUALS(conectionNode, NULL);
	ASSERT_EQUALS(conectionNode->getName(), "nb");
	conectionNode = intermediarNode->getNodeAtIndex(1);
	ASSERT_NOT_EQUALS(conectionNode, NULL);
	ASSERT_EQUALS(conectionNode->getName(), "nc");
	conectionNode = intermediarNode->getNodeAtIndex(2);
	ASSERT_EQUALS(conectionNode, NULL);

	intermediarNode = pGraph2->getNode("nb");
	ASSERT_NOT_EQUALS(intermediarNode, NULL);
	numberConectedTo = intermediarNode->getNumConnectedTo();
	ASSERT_EQUALS(numberConectedTo, 1);
	conectionNode = intermediarNode->getNodeAtIndex(0);
	ASSERT_NOT_EQUALS(conectionNode, NULL);
	ASSERT_EQUALS(conectionNode->getName(), "nc");
	conectionNode = intermediarNode->getNodeAtIndex(1);
	ASSERT_EQUALS(conectionNode, NULL);

	intermediarNode = pGraph2->getNode("nc");
	ASSERT_NOT_EQUALS(intermediarNode, NULL);
	numberConectedTo = intermediarNode->getNumConnectedTo();
	ASSERT_EQUALS(numberConectedTo, 0);
	conectionNode = intermediarNode->getNodeAtIndex(1);
	ASSERT_EQUALS(conectionNode, NULL);
}
