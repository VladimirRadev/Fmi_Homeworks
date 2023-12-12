#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <ctime>


const int MIN_SAMPLE_SIZE = 50;
std::vector<std::vector<std::string>> dataRecords;
std::vector<std::unordered_set<std::string>> valuesForEachAttr;

struct Node
{
    bool isReccuranceEvent;
    bool isLeaf = false;

    int incorrectsCount = 0;

    int attribute;
    std::string value;

    Node* parent = nullptr;
	std::vector<Node*> children;
    std::unordered_set<int> prevAttributes;
};

struct DataRecordsSet
{
    std::vector<std::vector<std::string>> rows;
    std::vector<std::unordered_set<std::string>> attrValues;

    // index 0 is for no-reccurance events
    // index 1  is for reccurance events
    std::unordered_map<std::string, int> mappingTable[2][10];

    int dataSize;
    int noRecSize = 0;
    int recSize = 0;

    DataRecordsSet(std::vector<std::vector<std::string>> rows)
    {
        this->rows = rows;
        getAttrValues();
        fromRowsToMappingTable();
    }

    void getAttrValues()
    {
        attrValues.resize(10);

        for (int i = 0; i<rows.size(); i++)
        {
            //rows[i][0] is the class , so we can skip it
            for (int j = 1; j < rows[i].size(); j++) 
            {
                attrValues[j].insert(rows[i][j]);
            }
        }
    }

    void fromRowsToMappingTable()
    {
        bool isReccuranceEvent;

        for(int i = 0; i<rows.size(); i++)
        {
            for (int j = 0; j<rows[i].size(); j++)
            {
                if (j == 0)
                {
                    isReccuranceEvent = rows[i][j][0] == 'r';
                    isReccuranceEvent ? recSize++ : noRecSize++;
                }
                else
                {
                    mappingTable[isReccuranceEvent][j][rows[i][j]]++;
                }
            }
        }

        dataSize = recSize + noRecSize;
    }

    double entropy(double a, double b)
    {
        if (a == 0 || b == 0)
        {
            return 0;
        }

        double pa = a/(a+b);
        double pb = b/(a+b);

        return -(pa)*log2(pa) - (pb)*log2(pb);
    }

    double entropyAttr(int attrIndex)
    {
        std::string key;

        double entropy_ = 0;
        double noReccuranceCount, reccuranceCount;

        for ( auto it = mappingTable[0][attrIndex].begin(); it != mappingTable[0][attrIndex].end(); ++it )
        {
            key = it->first;
            noReccuranceCount = it->second;
            reccuranceCount = mappingTable[1][attrIndex][key];
            entropy_ += ((noReccuranceCount+reccuranceCount)/dataSize) * entropy (noReccuranceCount, reccuranceCount);
        }

        return entropy_;
    }

    double informationGain(int attrIndex)
    {
        return entropy(noRecSize, recSize) - entropyAttr(attrIndex);
    }

    int findBestAttribute(std::unordered_set<int> prevAttributes)
    {
        double maxInfoGain = -1;
        double curInfoGain;
        int bestAttr = 1;

        for (int curAttr = 1; curAttr < 10 ; curAttr++)
        {
            //if curAttr is not traversed yet , then we can check it
            if (prevAttributes.find(curAttr) == prevAttributes.end())
            {
                curInfoGain = informationGain(curAttr);
                if (curInfoGain > maxInfoGain)
                {
                    maxInfoGain = curInfoGain;
                    bestAttr = curAttr;
                }
            }
        }

        return bestAttr;
    }

    DataRecordsSet* filter(int attr, std::string value)
    {
        std::vector<std::vector<std::string>> newRows;

        for (int i = 0; i < rows.size(); i++)
        {
            if(value == rows[i][attr])
            {
                newRows.push_back(rows[i]);
            }
        }

        DataRecordsSet* newDataset = new DataRecordsSet(newRows);

        return newDataset;
    }

    bool isRecMoreCommon(Node* node)
    {
        if (recSize == noRecSize)
        {
            return node->parent->isReccuranceEvent;
        }
        return recSize > noRecSize;
    }

};

struct ID3
{
    Node* root;

    void buildAttributeNode(DataRecordsSet* dataset, Node* parentNode)
    {
        Node* childNode;

        if (parentNode == nullptr)
        {
            root = new Node();
            childNode = root;
        }
        else
        {
            childNode = new Node();
            childNode->prevAttributes = parentNode->prevAttributes;
            parentNode->children.push_back(childNode);
        }

        int bestAttr = dataset->findBestAttribute(childNode->prevAttributes);

        childNode->attribute = bestAttr;
        childNode->prevAttributes.insert(bestAttr);
        childNode->parent = parentNode;
        childNode->isReccuranceEvent = dataset->isRecMoreCommon(childNode);

        std::unordered_set<std::string> attrValues = valuesForEachAttr[bestAttr];

        for (std::string value: attrValues)
        {
            buildValueNode(bestAttr, value, childNode, dataset);
        }
        return;
    }

    virtual void buildValueNode(int attr, std::string value, Node* parentNode, DataRecordsSet* dataset) = 0;

    bool classify(std::vector<std::string> row)
    {
        int attr;
        std::string value;
        Node* node = root;

        while(true)
        {
            attr = node->attribute;
            value = row[attr];

            for (int i = 0; i < node->children.size(); i++)
            {
                if(value == node->children[i]->value)
                {
                    if (node->children[i]->isLeaf)
                    {
                        return (node->children[i]->isReccuranceEvent) ?
                        row[0] == "recurrence-events" :
                        row[0] == "no-recurrence-events";
                    }

                    node = node->children[i]->children[0];
                    break;
                }
            }
        }
    }

    bool isEntropyZero(DataRecordsSet* dataset) {
        return dataset->entropy(dataset->recSize, dataset->noRecSize) == 0;
    }
};

struct ID3PrePruning : public ID3
{

    ID3PrePruning(DataRecordsSet* dataset)
    {
        buildAttributeNode(dataset, nullptr);
    }

    void buildValueNode(int attr, std::string value, Node* parentNode, DataRecordsSet* dataset)
    {
        if (isEntropyZero(dataset) || parentNode->prevAttributes.size() == 9 || dataset->rows.size() < MIN_SAMPLE_SIZE)
        {
            Node* leaf = new Node();
            leaf->value = value;
            leaf->isLeaf = true;
            leaf->parent = parentNode;
            leaf->isReccuranceEvent = dataset->isRecMoreCommon(leaf);
            parentNode->children.push_back(leaf);
            return;
        }

        Node* childNode = new Node();
        childNode->attribute = attr;
        childNode->value = value;
        childNode->prevAttributes = parentNode->prevAttributes;
        childNode->parent = parentNode;
        childNode->isReccuranceEvent = dataset->isRecMoreCommon(childNode);
        parentNode->children.push_back(childNode);
        DataRecordsSet* subset = dataset->filter(attr, value);
        buildAttributeNode(subset, childNode);

        delete subset;
    }
};

struct ID3PostPruning : public ID3
{
    std::vector<std::vector<std::string>> validationSet;

     ID3PostPruning(DataRecordsSet* dataRecordsSet)
    {
        buildAttributeNode(splitDataRecordsSet(dataRecordsSet), nullptr);
        validate();
    }

    DataRecordsSet* splitDataRecordsSet(DataRecordsSet* dataset)
    {
        std::vector<std::vector<std::string>> trainingSet;

        for (int i = 0; i < dataset->rows.size(); i++)
        {
            if (i < dataset->rows.size()*50/100)
            {
                trainingSet.push_back(dataset->rows[i]);
            }
            else
            {
                validationSet.push_back(dataset->rows[i]);
            }
        }

        return new DataRecordsSet(trainingSet);
    }

     void buildValueNode(int attr, std::string value, Node* parentNode, DataRecordsSet* dataset)
    {
        if (isEntropyZero(dataset) || parentNode->prevAttributes.size() == 9)
        {
            Node* leaf = new Node();
            leaf->value = value;
            leaf->isLeaf = true;
            leaf->parent = parentNode;
            leaf->isReccuranceEvent = dataset->isRecMoreCommon(leaf);
            parentNode->children.push_back(leaf);
            return;
        }

        Node* childNode = new Node();
        childNode->attribute = attr;
        childNode->value = value;
        childNode->parent = parentNode;
        childNode->prevAttributes = parentNode->prevAttributes;
        parentNode->children.push_back(childNode);
        DataRecordsSet* subset = dataset->filter(attr, value);
        buildAttributeNode(subset, childNode);

        delete subset;
    }

    void validate()
    {
        for (int i = 0 ; i < validationSet.size() ; i++)
        {
            evalIncorrects(validationSet[i]);
        }
        postPrune(root);
    }

    void evalIncorrects(std::vector<std::string> row)
    {
        int attr;
        std::string value;
        Node* node = root;

        while(true)
        {
            attr = node->attribute;
            value = row[attr];

            for (int i = 0; i < node->children.size(); i++)
            {
                if(value == node->children[i]->value)
                {
                    //incorrect classification at a step of the traversed tree
                    if ((row[0] == "recurrence-events" && !node->children[i]->isReccuranceEvent) ||
                        (row[0] == "no-recurrence-events" && node->children[i]->isReccuranceEvent))
                    {
                        node->children[i]->incorrectsCount++;
                    }

                    if (node->children[i]->isLeaf)
                    {
                        return;
                    }

                    node = node->children[i]->children[0];
                    break;
                }
            }
        }
    }

    void postPrune(Node* node)
    {
        if (node->isLeaf)
        {
            if (node->incorrectsCount > node->parent->parent->incorrectsCount)
            {
                //prune
                node->parent->parent->isLeaf = true;
                delete node;
            }
            return;
        }

        for (int i = 0; i<node->children.size(); i++)
        {
            postPrune(node->children[i]);
        }
    }
};

int myRandom (int i) { return std::rand()%i;}

 void readFileIN()
{
    std::string curLine, attribute;



    std::ifstream fileIN("breast+cancer/breast-cancer.data", std::ios::in);

    valuesForEachAttr.resize(10);
    int i = 0;

    while(getline(fileIN, curLine)){

        std::stringstream ss(curLine);
        std::vector<std::string> attributes;


        while(getline(ss, attribute, ',')){
            attributes.push_back(attribute);
            valuesForEachAttr[i].insert(attribute);
            i++;
        }

        dataRecords.push_back(attributes);
        i = 0;
    }

    std::srand ( unsigned ( std::time(0) ) );
    random_shuffle(dataRecords.begin(), dataRecords.end(), myRandom);

    fileIN.close();
}

double calcCurAccForPrePrun(std::vector<std::vector<std::string>>trainSet, std::vector<std::vector<std::string>>testSet)
{
    DataRecordsSet* dataset = new DataRecordsSet(trainSet);

    ID3PrePruning tree(dataset);

    double sum = 0;

    for (int i = 0 ; i<testSet.size(); i++)
    {
        sum += tree.classify(testSet[i]);
    }

    delete dataset;

    return (sum)/testSet.size();
}

double calcCurAccForPostPrun(std::vector<std::vector<std::string>>trainSet, std::vector<std::vector<std::string>>testSet)
{
    DataRecordsSet* dataset = new DataRecordsSet(trainSet);

    ID3PostPruning tree(dataset);

    double sum = 0;

    for (int i = 0 ; i < testSet.size(); i++)
    {
        sum += tree.classify(testSet[i]);
    }

    delete dataset;

    return (sum)/testSet.size();
}

void tenfoldCV()
{



    std::vector<std::vector<std::string>>trainSet;
    std::vector<std::vector<std::string>>testSet;

    std::cout << std::setw(23) <<"Pre-prun / Post-prun" << std::endl;
    std::cout << "=======================" << std::endl;

    int testSetSize = dataRecords.size()/10;
    int offset;


    double totalSumForPrePruning = 0;
    double totalSumForPostPruning = 0;


    double curAccForPrePrun;
    double curAccForPostPrun;

    for (int j = 0; j < 10; j++)
    {
        offset = j * testSetSize;

        for (int i = 0 ; i<dataRecords.size(); i++)
        {
            if (offset <= i && i< offset + testSetSize)
            {
                testSet.push_back(dataRecords[i]);
            }
            else
            {
                trainSet.push_back(dataRecords[i]);
            }
        }

        curAccForPrePrun = calcCurAccForPrePrun(trainSet, testSet);
        curAccForPostPrun = calcCurAccForPostPrun(trainSet, testSet);

        std::cout << std::setw(10) << curAccForPrePrun << " / " << std::setw(10) << curAccForPostPrun << std::endl;
        totalSumForPrePruning += curAccForPrePrun;
        totalSumForPostPruning += curAccForPostPrun;

        trainSet.clear();
        testSet.clear();
    }

    std::cout << "=======================" << std::endl ;
    std::cout << std::setw(10) << totalSumForPrePruning/10  << " / " << std::setw(10) << totalSumForPostPruning/10 << std::endl ;
}

int main()
{
    readFileIN();
    tenfoldCV();
}
