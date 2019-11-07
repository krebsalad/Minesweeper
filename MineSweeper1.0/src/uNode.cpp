#include "./../include/uNode.h"
#include <iostream>
#include <math.h>

std::map<std::string, std::shared_ptr<uNode>> uNode::nodes;

uNode::uNode(std::string _nodeId)
    : nodeId(_nodeId), transform(0,0,0), marked(false)
{

}

//static
const uNode& uNode::getNode(std::string _nodeId)
{
    //if not existin create it
    if(!isNode(_nodeId))
    {
        nodes[_nodeId] = std::make_shared<uNode>(_nodeId);
        std::cout << "uNode: created node : " << _nodeId << std::endl;
    }

    //return the node    
    return *nodes[_nodeId];
}

std::shared_ptr<uNode> uNode::getNodeShare(std::string _nodeId)
{
    getNode(_nodeId);
    return nodes[_nodeId];
}

bool uNode::isNode(std::string _nodeId)
{
    //if not node 
    if(nodes.find(_nodeId) == nodes.end())
    {
        return false;
    }
 
    return true;
}

void uNode::removeNode(std::string _nodeId)
{
  
}

double uNode::getDistanceBetweenNodes(uNode* node1, uNode* node2)
{
    double dis_x = abs((double)(node1->transform.x) - (double)(node2->transform.x));
    double dis_y = abs((double)(node1->transform.y) - (double)(node2->transform.y));
    double dis_z = abs((double)(node1->transform.z) - (double)(node2->transform.z));
    double dis = sqrt(pow(dis_x, 2.0) + pow(dis_y, 2.0) + pow(dis_z, 2.0));
    return dis;
}

void uNode::updateAdjacencyLists2d(double _distance)
{
    for (std::map<std::string, std::shared_ptr<uNode>>::iterator node_itr_1 = nodes.begin(); node_itr_1 != nodes.end(); node_itr_1++)
    {
        std::shared_ptr<uNode> node1 = node_itr_1->second;
        node1->adjacencyList.clear();
        for (std::map<std::string, std::shared_ptr<uNode>>::iterator node_itr_2 = nodes.begin(); node_itr_2 != nodes.end(); node_itr_2++)
        {
            std::shared_ptr<uNode> node2 = node_itr_2->second;
            if(node1->nodeId == node2->nodeId)
            {
                continue;
            }
            
            double distance = uNode::getDistanceBetweenNodes(node1.get(), node2.get());
            if(distance <= _distance)
            {
                node1->adjacencyList.push_back(node2->nodeId);              
            }     
        }
    }

    std::cout << "uNode: updated adjaceny lists" << std::endl; 
}

std::list<std::string> uNode::getAllNodeIds()
{
    std::list<std::string> nodeIds;
    for(std::map<std::string, std::shared_ptr<uNode>>::iterator node_id_iter = nodes.begin(); node_id_iter != nodes.end(); node_id_iter++)
    {
        nodeIds.push_back(node_id_iter->first);
    }
    return nodeIds;
}

const uNode& uNode::getNode2d(int _x, int _y)
{
    return getNode(_x, _y, 0);   
}

const uNode& uNode::getNode(int _x, int _y, int _z)
{
    std::string _nodeId = uNode::coordsToId(_x, _y, _z);
    std::shared_ptr<uNode> node = uNode::getNodeShare(_nodeId);
    node->transform = uVec(_x, _y, _z);
    return *node;   
}

void uNode::createNodes2d(int sx, int sy)
{
    for (int _x =0; _x < sx; _x++)
    {
        for (int _y =0; _y < sy; _y++)
        {
            getNode2d(_x, _y);
        }
    }

    updateAdjacencyLists2d(1.5);
}

std::string uNode::coordsToId(int x, int y)
{
    return uNode::coordsToId(x, y, 0);
}

std::string uNode::coordsToId(int x, int y, int z)
{
    std::string txt = std::string("n") + std::to_string(x) + std::string(",") + std::to_string(y) + std::string(",") + std::to_string(z);
    return txt;
}

int uNode::nodeCount()
{
    return nodes.size();
}

void uNode::unmarkAllNodes()
{
    for(std::map<std::string, std::shared_ptr<uNode>>::iterator node_id_iter = nodes.begin(); node_id_iter != nodes.end(); node_id_iter++)
    {
        node_id_iter->second->marked = false;
    }
}

