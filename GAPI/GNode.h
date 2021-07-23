#pragma once

#include "GAPI.h"
#include "GGraph.h"

#include <string>
#include <list>

/**
 * GNode class represents a node in a given graph. Each node is 
 * identified by a unique name.
 **/
class GAPI_API GNode
{
public:
    GNode(const std::string &iName);
    ~GNode(void);
    
    const std::string& getName() {return m_name;}
    
    //
    //Connect this node to given ipNode
    //
    ReturnCode connect(GNode *ipNode);
    
    //
    //Break the connection between this node and given ip node
    //if exists.
    //
    ReturnCode disconnect(GNode *ipNode);
    
    //
    //Disconnect all connections of this node.
    //
    ReturnCode disconnectAll();

    //
    //Get number of nodes which this node connects to
    //
    int getNumConnectedTo();

	GNode* getNodeAtIndex(int index);

	void deletion();

private:
    std::string m_name;
	std::list<GNode*> m_conectionsTo;
	std::list<GNode*> m_IsConectedTo;
	
public:
	static int count;
	bool belongsToGraph;
};

