#pragma once

#include "GAPI.h"

#include <string>
#include <vector>
#include "GNode.h"
#include "ObjectCounter.h"

class GNode;

/**
 * GGraph class represents a graph object which is used to group a number of nodes.
 */
class GAPI_API GGraph
{
public:
    GGraph(const std::string &iName);
    ~GGraph(void);

	const std::string& getName() { return m_name; }

    //
    //Create a new node object and store it in graph for future access
    //Created object is returned to the caller as well
    //
	std::shared_ptr<GNode> addNode(const std::string &iName);

    //
    //Remove the node given by its name.
    //
    ReturnCode removeNode(const std::string &iName);
    
    //
    //Return the node object identified by iName
    //
	std::shared_ptr<GNode> getNode(const std::string& iName);
    
    //
    //Return number of nodes attached to this graph
    //
    int getNumNodes();

    //
    //Dump the current state of the graph to given file
    //
    ReturnCode save(const std::string& iFileName);
    
    //
    //Update the current state of the graph from given file
    //
    ReturnCode load(const std::string& iFileName);

private:
	std::string m_name;
	std::vector<std::shared_ptr<GNode>> m_nodes;
};
