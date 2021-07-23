#include "GNode.h"

int GNode::count = 0;

GNode::GNode(const std::string &iName)
{
	m_name = iName;
	belongsToGraph = false;
	GNode::count++;
}

GNode::~GNode(void)
{
	for (std::list<GNode*>::iterator it = m_conectionsTo.begin(); it != m_conectionsTo.end(); ++it)
	{
		(*it)->deletion();
	}
	GNode::count--;
}

ReturnCode GNode::connect(GNode *ipNode)
{
	if (ipNode == NULL)
	{
		return RC_ParameterError;
	}

	std::list<GNode*>::iterator findNodeConnection = std::find(m_conectionsTo.begin(), m_conectionsTo.end(), ipNode);
	
	if (findNodeConnection == m_conectionsTo.end())
	{
		m_conectionsTo.push_back(ipNode);
		ipNode->m_IsConectedTo.push_back(this);
	}
	else
	{
		return RC_ValueError;
	}

	return RC_OK;
}

ReturnCode GNode::disconnect(GNode *ipNode)
{
	if (ipNode == NULL)
	{
		return RC_ParameterError;
	}

	std::list<GNode*>::iterator findNodeConnection = std::find(m_conectionsTo.begin(), m_conectionsTo.end(), ipNode);

	if (findNodeConnection != m_conectionsTo.end())
	{	
		m_conectionsTo.remove(ipNode);
		ipNode->deletion();
	}
	else
	{
		return RC_ValueError;
	}

    return RC_OK;
}

ReturnCode GNode::disconnectAll()
{
	m_conectionsTo.clear();

    return RC_OK;
}

int GNode::getNumConnectedTo()
{
    return m_conectionsTo.size();
}

GNode * GNode::getNodeAtIndex(int index)
{
	if (index > m_conectionsTo.size() - 1)
	{
		return NULL;
	}

	std::list<GNode*>::iterator it = m_conectionsTo.begin();

	for (int i = 0; i < index;i++)
	{
		if (it != m_conectionsTo.end())
		{
			++it;
		}
		else
		{
			return NULL;
		}
	}

	return *it;
}

void GNode::deletion()
{
	if (m_IsConectedTo.size() == 0 && belongsToGraph == false)
	{
		delete this;
	}
	else
	{
		belongsToGraph = false;
		m_IsConectedTo.clear();
	}
}