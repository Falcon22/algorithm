#include "Huffman.h"
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <assert.h>

size_t countByte = sizeof(unsigned char);

class CBitSequence {
public:
    void WriteBit( bool bit );
    void WriteByte( unsigned char value );

    unsigned char ReadByte();
    bool IsEOS() const { return readIterator == data.size(); }
    int GetLastBitsCount() const { return lastBitsCount; }

private:
    std::vector<unsigned char> data;
    int lastBitsCount = 0;
    int readIterator = 0;
};

void CBitSequence::WriteBit( bool bit )
{
    if( lastBitsCount == 0 ) {
        data.push_back( 0 );
    }
    if( bit ) {
        data.back() |= 1 << lastBitsCount;
    }
    lastBitsCount = ( lastBitsCount + 1 ) % (countByte * 8);
}

void CBitSequence::WriteByte(unsigned char value )
{
    for( int i = 0; i < (countByte * 8); ++i ) {
        WriteBit( ( value & ( 1 << i ) ) != 0 );
    }
}

unsigned char CBitSequence::ReadByte()
{
    assert( readIterator < data.size() );
    return data[readIterator++];
}

class Node {
public:
    Node() : left(nullptr), right(nullptr), count(0), value(0) {};
    Node(unsigned char value) : left(nullptr), right(nullptr), count(1), value(value) {};
    Node(unsigned char value, size_t count) : left(nullptr), right(nullptr), count(count), value(value) {};
    Node(Node* left, Node* right) : left(left), right(right) {
        value = 0;
        count = left->count + right->count;
    }
    ~Node() {
        delete left;
        delete right;
    }

    Node* left;
    Node* right;
    size_t count;
    unsigned char value;

    class Compare {
    public:
        bool operator()(Node* a, Node* b) {
            return a->count > b->count;
        }
    };
};


void BuildTable(Node* node, std::vector<bool>& code, std::map<unsigned char, std::vector<bool>>& table) {
    if (node->left != nullptr) {
        code.push_back(0);
        BuildTable(node->left, code, table);
    }

    if (node->right != nullptr) {
        code.push_back(1);
        BuildTable(node->right, code, table);
    }

    if (node != nullptr && node->value) {
        table[node->value] = code;
    }
    if (code.size()) {
        code.pop_back();
    }
}


std::map<std::vector<bool>, unsigned char> tableCode;
size_t countBt = 0;
size_t lastBt = 0;

void Encode(IInputStream& original, IOutputStream& compressed)
{
    CBitSequence s;
    std::vector<unsigned char> in;
    std::map<unsigned char, size_t> symbols;
    std::vector<bool> code;
    byte value;

    while (original.Read(value)) {
        symbols[value]++;
        in.push_back(value);
    }
    std::priority_queue<Node*, std::vector<Node*>, Node::Compare> trees;

    for (auto i = symbols.begin(); i != symbols.end(); i++) {
        trees.push(new Node(i->first, i->second));
    }

    while (trees.size() != 1) {
        Node* left = trees.top();
        trees.pop();
        Node* right = trees.top();
        trees.pop();
        trees.push(new Node(left, right));
    }

    Node* root = trees.top();
    std::map<unsigned char, std::vector<bool>> table;
    BuildTable(root, code, table);

    for (auto i = table.begin(); i != table.end(); i++) {
        tableCode.insert(std::make_pair(i->second, i->first));
    }

    for (auto i : in) {
        for (int j = 0; j < table[i].size(); j++) {
            s.WriteBit(table[i][j]);
        }
    }

    lastBt = s.GetLastBitsCount();
    while (!s.IsEOS()) {
        compressed.Write(s.ReadByte());
        size_t prev = countBt;
        countBt++;
        if (prev > countBt) {
            std::cout << "perepoln";
        }
    }
}

void Decode(IInputStream& compressed, IOutputStream& original)
{
    std::vector<bool> t;
    CBitSequence s;
    byte value;
    size_t n = 0;
    while (compressed.Read(value)) {
        if (countBt == 1) {
            n = lastBt;
        } else {
            n = countByte * 8;
        }
        for (int j = 0; j < n; j++) {
            t.push_back((value & (1 << j)) != 0);
            if (tableCode.find(t) != tableCode.end()) {
                original.Write(tableCode[t]);
                t.clear();
            }
        }
        countBt--;
    }
}