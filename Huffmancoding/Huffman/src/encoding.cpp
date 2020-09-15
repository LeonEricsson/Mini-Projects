// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
#include "HuffmanNode.h"
#include <queue>
#include <bitset>

using namespace std;

map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;
    while (true) {
        int character = input.get();
        if(character == -1) break;
        else {
            // Bra sätt att lägga in i mapp?
            if(freqTable.count(character) == 0){
                freqTable.insert(pair<int, int>(character, 1));
            }
            else {
                freqTable.find(character)->second++;
            }
        }
    }
    freqTable.insert(pair<int, int>(PSEUDO_EOF, 1));
    return freqTable;

}


HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    // Vill man inte jobba med pekar och bara flytta runt pekarna för att spara minne?
    auto cmp = [](HuffmanNode* a, HuffmanNode* b) {return a->count > b->count; };
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, decltype (cmp)> queue(cmp);
    HuffmanNode* top;
    HuffmanNode* tempNode;
    HuffmanNode* tempNode2;
    for(auto it = freqTable.begin() ; it != freqTable.end() ; it++){
        HuffmanNode* tempNode1 = new HuffmanNode(it->first, it->second);
        queue.push(tempNode1);
        top = tempNode1;
    }
    size_t size = queue.size();
    while (size > 1) {
        tempNode = queue.top();
        queue.pop();
        tempNode2 = queue.top();
        queue.pop();
        HuffmanNode* newNode = new HuffmanNode(NOT_A_CHAR, tempNode->count + tempNode2->count, tempNode, tempNode2);
        queue.push(newNode);
        top = newNode;
        size--;

    }

    return top;
}

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;
    string binaryCode;
    preorder(encodingTree->zero, binaryCode + "0", encodingMap);
    preorder(encodingTree->one, binaryCode + "1", encodingMap);
    return encodingMap;
}

void preorder(HuffmanNode* node, string binaryCode, map<int, string>& encodingMap){
    if(node == nullptr) return;
    preorder(node->zero, binaryCode + "0", encodingMap);
    preorder(node->one, binaryCode + "1", encodingMap);
    if(node->isLeaf()) encodingMap.insert(pair<int, string>(node->character, binaryCode));

}


void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    string binaryCode;
    input.clear();
    input.seekg(0, ios::beg);
    while(true){
        int character = input.get();
        if(character == -1) break;
        binaryCode = encodingMap.at(character);
        //cout << binaryCode << endl;
        stringIterate(binaryCode, output);
    }
    binaryCode = encodingMap.at(PSEUDO_EOF);
    stringIterate(binaryCode, output);
}


void stringIterate(string binaryCode, obitstream& output){
    for(auto it = binaryCode.cbegin() ; it != binaryCode.cend() ; it++){
        switch (*it) {
            case '0':
                output.writeBit(0);
                break;
            case '1':
                output.writeBit(1);
                break;
        }
    }
}



void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    while(true){
        if(decodeTraversal(input, encodingTree, output)) break;
    }


}

bool decodeTraversal(ibitstream& input, HuffmanNode* node, ostream& output){
    if(node->isLeaf()){

        if(node->character == PSEUDO_EOF) return true;
        else{
            output.put(node->character);
            return false;
        }
    }
    int bit = input.readBit();

    if(bit == 0) return decodeTraversal(input,node->zero,output);
    else return decodeTraversal(input, node->one, output);
}

void compress(istream& input, obitstream& output) {
    map<int, int> freqTable = buildFrequencyTable(input);
    output << "{";
    for(auto it2 = freqTable.cbegin() ; it2 != freqTable.cend() ; it2++){
        if (it2 != freqTable.cbegin()) output << ", " << it2->first << ":" << it2->second;
        else{output << it2->first << ":" << it2->second;}

    }
    output << "}";

    HuffmanNode* encodingTree = buildEncodingTree(freqTable);
    map<int, string> encodingMap = buildEncodingMap(encodingTree);
    encodeData(input, encodingMap, output);
}



void decompress(ibitstream& input, ostream& output) {
    map<int, int> freqTable;
    input.get();
    string str;
    while(true){
        int character;
        char c;
        int freq;
        input >> character >> c >> freq;
        freqTable.insert(pair<int, int>(character, freq));
        c = input.get();
        if(c == '}') break;
        input.get();
    }
    HuffmanNode* encodingTree = buildEncodingTree(freqTable);
    decodeData(input, encodingTree, output);

}



void freeTree(HuffmanNode* node) {
    if(node == nullptr) return;
    freeTree(node->zero);
    freeTree(node->one);
    delete node;
}
