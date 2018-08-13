#pragma once
#include <iostream>
#include <queue>
using namespace std;
template<class W>
struct HuffmanTreeNode
{

    HuffmanTreeNode<W>* _left;
    HuffmanTreeNode<W>* _right;
    HuffmanTreeNode<W>* _parent;
    W _w; //权值

    HuffmanTreeNode(const W& w)
        :_w(w)
         ,_left(NULL)
         ,_right(NULL)
    {}
};

template<class W>
class HuffmanTree
{
    typedef HuffmanTreeNode<W> Node;
public:
    struct NodeCompare
    {
        bool operator()(Node* l, Node* r)
        {
             return l->_w > r->_w;
        }
    };

    HuffmanTree(W* a, size_t n, const W& invalid)
        :_root(NULL)
    {
        priority_queue<Node*, vector<Node*>,NodeCompare> minheap;

        for(size_t i = 0; i < n; i++)
        {
            if(a[i] != invalid)
                minheap.push(new Node(a[i]));
        }

        while(minheap.size() > 1)
        {
            Node* left = minheap.top();
            minheap.pop();
            Node* right = minheap.top();
            minheap.pop();

            Node* parent = new Node(left->_w + right->_w);
            parent->_left = left;
            parent->_right = right;
            left->_parent = parent;
            right->_parent = parent;
            minheap.push(parent);
        }
    }
private:
    Node* _root;
};
