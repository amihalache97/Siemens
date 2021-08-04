#pragma once

#include "GAPI.h"
#include "GGraph.h"
#include "ObjectCounter.h"

#include <string>
#include <vector>
#include <algorithm>

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
    ReturnCode connect(std::shared_ptr<GNode> ipNode);
    
    //
    //Break the connection between this node and given ip node
    //if exists.
    //
    ReturnCode disconnect(std::shared_ptr<GNode> ipNode);
    
    //
    //Disconnect all connections of this node.
    //
    ReturnCode disconnectAll();

    //
    //Get number of nodes which this node connects to
    //
    int getNumConnectedTo();

	std::shared_ptr<GNode> getNodeAtIndex(int index);

private:
    std::string m_name;
	std::vector<std::shared_ptr<GNode>> m_conectionsTo;
};

