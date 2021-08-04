#include "GNode.h"

GNode::GNode(const std::string &iName)
{
	m_name = iName;
	ObjectCounter::numberOfObjects++;
}

GNode::~GNode()
{
	ObjectCounter::numberOfObjects--;
}

ReturnCode GNode::connect(std::shared_ptr<GNode> ipNode)
{
	if (ipNode == NULL)
	{
		return RC_ParameterError;
	}

	for (int i = 0; i < m_conectionsTo.size(); i++)
	{
		if (m_conectionsTo[i]->m_name == ipNode->m_name)
		{
			return RC_ValueError;
		}
	}
	
	m_conectionsTo.push_back(std::shared_ptr<GNode>(ipNode));
	
	return RC_OK;
}

ReturnCode GNode::disconnect(std::shared_ptr<GNode> ipNode)
{
	if (ipNode == NULL)
	{
		return RC_ParameterError;
	}

	for (int i = 0; i < m_conectionsTo.size(); i++)
	{
		if (m_conectionsTo[i]->m_name == ipNode->m_name)
		{
			m_conectionsTo[i].reset();
			m_conectionsTo.erase(m_conectionsTo.begin() + i);
			return RC_OK;
		}
	}

    return RC_ValueError;
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

std::shared_ptr<GNode> GNode::getNodeAtIndex(int index)
{
	if (index > m_conectionsTo.size() - 1 || m_conectionsTo.size() == 0)
	{
		return NULL;
	}

	return m_conectionsTo[index];
}