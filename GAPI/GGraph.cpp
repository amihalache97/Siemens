#include "GGraph.h"
#include <fstream>;

GGraph::GGraph(const std::string &iName)
{
	m_name = iName;
	ObjectCounter::numberOfObjects++;
}

GGraph::~GGraph(void)
{
	ObjectCounter::numberOfObjects--;
}


std::shared_ptr<GNode> GGraph::addNode(const std::string& iName)
{
	if (iName.empty())
	{
		return NULL;
	}
	else
	{

		for (auto iterator : m_nodes)
		{
			if (iterator->getName() == iName)
			{
				return NULL;
			}
		}

		auto node = std::make_shared<GNode>(iName);

		m_nodes.push_back(node);

		return node;
	}
}

std::shared_ptr<GNode> GGraph::getNode(const std::string& iName)
{
	if (iName.empty())
	{
		return NULL;
	}

	for (auto iterator : m_nodes)
	{
		if (iterator->getName() == iName)
		{
			return iterator;
		}
	}

    return NULL;
}

ReturnCode GGraph::removeNode(const std::string& iName)
{
	if (iName.empty())
	{
		return RC_ParameterError;
	}

	for (int i=0; i< m_nodes.size(); i++)
	{
		if (m_nodes[i]->getName() == iName)
		{
			m_nodes.erase(m_nodes.begin() + i);
			return RC_OK;
		}
	}

	return RC_ValueError;
}

ReturnCode GGraph::save(const std::string& iFileName)
{
	std::ofstream file(iFileName);

	if (file.is_open())
	{
		file << m_name << std::endl;

		for (auto iteratorNode : m_nodes)
		{
			file << iteratorNode->getName();

			int numberOfConnections = iteratorNode->getNumConnectedTo();

			for (int i = 0; i < numberOfConnections; i++)
			{
				std::shared_ptr<GNode> conection = iteratorNode->getNodeAtIndex(i);

				if (conection != NULL)
				{
					file << ' ' << conection->getName();
				}
			}

			file << std::endl;
		}

		file.close();
	}
	else
	{
		return RC_ParameterError;
	}

    return RC_OK;
}

ReturnCode GGraph::load(const std::string& iFileName)
{
	std::ifstream file(iFileName);

	if (file.is_open())
	{
		file >> m_name;

		std::string nodeName;

		while (file >> nodeName)
		{
			std::string conectionName;

			auto node = addNode(nodeName);

			while ((file.peek() != '\n') && (file.peek() != EOF))
			{
				file >> conectionName;
				
				node->connect(std::make_shared<GNode>(conectionName));
			}
		}
	}
	else
	{
		return RC_ParameterError;
	}

	return RC_OK;
}

int GGraph::getNumNodes()
{
    return m_nodes.size();
}
