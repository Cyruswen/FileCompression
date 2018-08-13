#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "HaffmanTree.hpp"
using namespace std;

typedef long long LongType;

struct CharInfo
{
    char _ch;
    LongType _count;
    string _code;
    CharInfo operator+(const CharInfo& info)
    {
        CharInfo ret;
        ret._count = _count + info._count;
        return ret;
    }

    bool operator >(const CharInfo& info)
    {
        return _count > info._count; 
    }

    bool operator != (const CharInfo& info)
    {
        return _count != info._count;
    }
};

class FileCompress
{
public:
    typedef HuffmanTree<CharInfo*> Node;
    FileCompress()
    {
        for(size_t i = 0; i < 256; ++i)
        {
            _infos[i]._ch = i;
            _infos[i]._count = 0;
        }
    }

    void Compress(const char* file)
    {
        //统计文件中字符出现的次数
        ifstream ifs(file);
        char ch;
        while(ifs >> ch)
        {
            _infos[ch]._count++;
        }

        //构建哈夫曼树
        CharInfo invalid;
        invalid._count = 0;
        HuffmanTree<CharInfo> t(_infos, 256, invalid);

        //生成haffman_code
        GetHuffmanCode(t.GetRoot());
        //压缩
        string Compressfile = file;
        Compressfile += ".huffman";
        ofstream ofs(Compressfile.c_str());
        ifs.clear();
        ifs.seekg(0);
        while(ifs >> ch)
        {
            string& code = _infos[ch].code;
            for(size_t i = 0; i < code.size(); ++i)
            {
                if(code[i] == '1')
                {

                }
                else if(code[i] == '0')
                {

                }else
                {
                    assert(false);
                }
            }
        }
        
    }
    void GetHuffmanCode(Node* root)
    {
        if(root == NULL)
        {
            return;
        }
        if(root->_left == NULL && root->_right == NULL)
        {
            string& code =_infos[root->_w._ch].code;
            Node* cur = root;
            Node* parent = cur->parent;
            while(parent)
            {
                if(cur == parent->_left)
                    code += '0';
                else
                    code += '1';

                cur = parent;
                parent = parent->parent;
            }
            reverse(code.begin(), code.end());
            return;
        }
        GetHuffmanCode(root->_left);
    }
    void Uncompress(const char* file);
    
    Node* GetRoot()
    {
        return
    }
private:
    CharInfo _infos[256];
};
