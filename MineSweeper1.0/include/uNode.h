#ifndef UNODE_H_
#define UNODE_H_

#include <list>
#include <map>
#include <string>
#include <memory>


struct uVec
{
    double x;
    double y;
    double z;
    

    uVec(double _x, double _y, double _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
};

class uNode
{
    //member functions
    public:
        uNode(std::string _nodeId);
        ~uNode() = default;
        std::list<std::string> adjacencyList;
        const std::string nodeId;
        uVec transform;
        bool marked;

    //global functions
    public:
        //base manage nodes
        static const uNode& getNode(std::string _nodeId);
        static std::shared_ptr<uNode> getNodeShare(std::string _nodeId);
        static bool isNode(std::string _nodeId);
        static void removeNode(std::string _nodeId);
        static int nodeCount();

        //node adjaceny
        static void updateAdjacencyLists2d(double _distance);
        static double getDistanceBetweenNodes(uNode* node1, uNode* node2);

        //2d util
        static std::string coordsToId(int x, int y);
        static std::string coordsToId(int x, int y, int z);
        static const uNode& getNode(int x, int y, int z);
        static void createNodes2d(int sx, int sy);
        static const uNode& getNode2d(int x, int y);

        static std::list<std::string> getAllNodeIds();
        static void unmarkAllNodes();
        
    private:
        static std::map<std::string, std::shared_ptr<uNode>> nodes;
        

        
};

#endif // !UNODE_H_