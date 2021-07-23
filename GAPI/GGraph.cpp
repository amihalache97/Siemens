#include "GGraph.h"
#include <fstream>;

int GGraph::count = 0;

GGraph::GGraph(const std::string &iName)
{
	m_name = iName;
	GGraph::count++;
}

GGraph::~GGraph(void)
{
	GGraph::count--;
}


GNode* GGraph::addNode(const std::string& iName)
{
	GNode *node = NULL;

	if (iName.empty())
	{
		return NULL;
	}
	else
	{
		node = new GNode(iName);

		std::list<GNode*>::iterator findNode = std::find(m_nodes.begin(), m_nodes.end(), node);

		if (findNode != m_nodes.end())
		{
			delete(node);
			return NULL;
		}
		else
		{
			m_nodes.push_back(node);
			node->belongsToGraph = true;
		}
	}

	return node;
}

GNode* GGraph::getNode(const std::string& iName)
{
	if (iName.empty())
	{
		return NULL;
	}

	for (std::list<GNode*>::iterator iterator = m_nodes.begin(); iterator != m_nodes.end(); ++iterator)
	{
		if ((*iterator)->getName() == iName)
		{
			return *iterator;
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

	for (std::list<GNode*>::iterator iterator = m_nodes.begin(); iterator != m_nodes.end(); ++iterator)
	{
		if ((*iterator)->getName() == iName)
		{
			GNode *aux = *iterator;
			m_nodes.remove(*iterator);
			delete aux;
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

		for (std::list<GNode*>::iterator iteratorNode = m_nodes.begin(); iteratorNode != m_nodes.end(); ++iteratorNode)
		{
			file << (*iteratorNode)->getName();

			int numberOfConnections = (*iteratorNode)->getNumConnectedTo();

			for (int i = 0; i < numberOfConnections; i++)
			{
				GNode* conection = (*iteratorNode)->getNodeAtIndex(i);

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

			GNode* node = addNode(nodeName);

			while ((file.peek() != '\n') && (file.peek() != EOF))
			{
				file >> conectionName;
				GNode* connectionNode = new GNode(conectionName);
				node->connect(connectionNode);
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


void GGraph::deletion()
{
	if (m_nodes.size() == 0)
	{
		delete this;
	}
	else
	{
		for (std::list<GNode*>::iterator iterator = m_nodes.begin(); iterator != m_nodes.end(); ++iterator)
		{
			(*iterator)->deletion();
		}
		delete this;
	}
}
