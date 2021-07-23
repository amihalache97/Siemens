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

    GNode *pNode_na = pGraph->addNode("na");
    ASSERT_NOT_EQUALS(pNode_na, NULL);
    ASSERT_EQUALS(pGraph->getNumNodes(), numNodes + 1);

	delete pNode_na;
    pNode_na = NULL;

    pNode_na = pGraph->addNode("na");
    ASSERT_EQUALS(pNode_na, NULL);
    ASSERT_EQUALS(pGraph->getNumNodes(), numNodes + 1);
    pGraph = NULL;

	delete pNode_na;
	delete pGraph;
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
    GNode *pNode = pGraph->addNode("na");
    ASSERT_EQUALS(pGraph->getNode("na"), pNode);
}

void TestGraph::testSaveLoad()
{
	GGraph *pGraph = new GGraph("ga");

	GNode *pNode_na = pGraph->addNode("na");
	GNode *pNode_nb = pGraph->addNode("nb");
	GNode *pNode_nc = pGraph->addNode("nc");

	pNode_na->connect(pNode_nb);
	pNode_na->connect(pNode_nc);
	pNode_nb->connect(pNode_nc);

	pGraph->save("file.txt");

	GGraph *pGraph2 = new GGraph("");
	pGraph2->load("file.txt");

	ASSERT_EQUALS(pGraph2->getName(), "ga");
	ASSERT_EQUALS(pGraph2->getNumNodes(), 3);

	GNode* aux = pGraph2->getNode("na");
	ASSERT_NOT_EQUALS(aux, NULL);
	int numberConectedTo = aux->getNumConnectedTo();
	ASSERT_EQUALS(numberConectedTo, 2);
	GNode* con = aux->getNodeAtIndex(0);
	ASSERT_NOT_EQUALS(con, NULL);
	ASSERT_EQUALS(con->getName(), "nb");
	con = aux->getNodeAtIndex(1);
	ASSERT_NOT_EQUALS(con, NULL);
	ASSERT_EQUALS(con->getName(), "nc");
	con = aux->getNodeAtIndex(2);
	ASSERT_EQUALS(con, NULL);

	aux = pGraph2->getNode("nb");
	ASSERT_NOT_EQUALS(aux, NULL);
	numberConectedTo = aux->getNumConnectedTo();
	ASSERT_EQUALS(numberConectedTo, 1);
	con = aux->getNodeAtIndex(0);
	ASSERT_NOT_EQUALS(con, NULL);
	ASSERT_EQUALS(con->getName(), "nc");
	con = aux->getNodeAtIndex(1);
	ASSERT_EQUALS(con, NULL);

	aux = pGraph2->getNode("nc");
	ASSERT_NOT_EQUALS(aux, NULL);
	numberConectedTo = aux->getNumConnectedTo();
	ASSERT_EQUALS(numberConectedTo, 0);
	con = aux->getNodeAtIndex(1);
	ASSERT_EQUALS(con, NULL);

}
