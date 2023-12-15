#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <utility>
#include <cstdlib>
#include <algorithm>
#include <ctime> 
const int CVk=10;
std::vector<std::string>data;

//row:0 for 'y', row: 1 for 'n'
int republicans[2][16];
int democrats[2][16];
int testSetSize,testSetStartIndex;
double republicansCount=0.0,democratsCount=0.0;
int leadingOpinionAboutAtrributeRepublican[2][16];
int leadingOpinionAboutAtrributeDemocrat[2][16];


void calcProbTable(const std::string& row, const int& adder)
{
    bool isRepublican = row[0] == 'r';
    isRepublican ? republicansCount+=adder : democratsCount+=adder;

    for (size_t i = 1; i < row.size(); i++)
    {
        if(row[i] == 'y')
        {
            isRepublican ? republicans[0][i-1]+=adder : democrats[0][i-1]+=adder;
            isRepublican ? leadingOpinionAboutAtrributeRepublican[0][i-1]+=adder : leadingOpinionAboutAtrributeDemocrat[0][i-1]+=adder;
        }
        else if(row[i]=='n')
        {
            isRepublican ? republicans[1][i-1]+=adder : democrats[1][i-1]+=adder;
            isRepublican ? leadingOpinionAboutAtrributeRepublican[1][i-1]+=adder : leadingOpinionAboutAtrributeDemocrat[1][i-1]+=adder;

        }
    }
}
int countPredictedCorrect(const int& testSetStartInd)
{
    int result=0;
    for (size_t i = testSetStartInd; i < testSetStartInd + testSetSize; i++)
    {
        bool isRepublican = data[i][0] == 'r';
        double probForRepublican=0.0;
        double probForDemocrat=0.0;

        //features probabilities' calculation
        for (size_t j = 1; j < data[i].size(); j++)
        {
            if(data[i][j] == 'y')
            {
                //laplace smoothing and log 
                probForRepublican += log((double)(republicans[0][j-1] + 1)/(republicansCount + 2 * 1) );
                probForDemocrat += log((double)(democrats[0][j-1] + 1)/(democratsCount + 2 * 1) );

            }
            else if(data[i][j]=='n')
            {
                //laplace smoothing and log 
                probForRepublican += log((double)(republicans[1][j-1] + 1)/(republicansCount + 2 * 1) );
                probForDemocrat += log((double)(democrats[1][j-1] + 1)/(democratsCount + 2 * 1) );

            }
           
        }
        
        //classes' probabilities
        probForRepublican += log((republicansCount + 1) / (republicansCount + democratsCount + 2 * 1));
        probForDemocrat += log((democratsCount + 1 )/ (republicansCount + democratsCount + 2*1));

        //is it corect predicted ?
        if(isRepublican)
        {
            if(probForRepublican > probForDemocrat)
            {
                ++result;
            }
        }
        else
        {
            if(probForDemocrat > probForRepublican)
            {
                ++result;
            }
        }

    }
    return result;

}
// random generator function:
int myrandom (int i) { return std::rand()%i;}

int main()
{
    std::srand ( unsigned ( std::time(0) ) );
    std::ifstream data_in("congressional+voting+records/house-votes-84.data",std::ios::in);
    std::string row;
    while (std::getline(data_in,row,'\n'))
    {
        std::string input;
        if(row[0]=='r')
        {
            input+='r';
            for (size_t i = 10; i < row.size(); i++)
            {
                if(row[i]==',')
                {
                    continue;
                }
                input+=row[i];
            }
        }
        else if (row[0]=='d')
        {
            input+='d';
            for (size_t i = 8; i < row.size(); i++)
            {
                if(row[i]==',')
                {
                    continue;
                }
                input+=row[i];
            }
        }
        calcProbTable(input,1);
        data.push_back(input);

    }
    data_in.close(); 

    for (size_t i = 0; i < data.size(); i++)
    {
        bool isRepublican = data[i][0] == 'r';
        for (size_t j = 1; j < data[i].size(); j++)
        {
            if(data[i][j]=='?')
            {
                if(isRepublican)
                {
                    //'y'
                    if(leadingOpinionAboutAtrributeRepublican[0][j-1] >= leadingOpinionAboutAtrributeDemocrat[1][j-1])
                    {
                        data[i][j] = 'y';
                        republicans[0][j-1]+=1;
                    }
                    //'n'
                    else 
                    {
                        data[i][j]= 'n';
                        republicans[1][j-1]+=1;
                    }
                }
                else
                {
                    //'y'
                    if(leadingOpinionAboutAtrributeDemocrat[0][j-1] >= leadingOpinionAboutAtrributeDemocrat[1][j-1])
                    {
                        data[i][j] = 'y';
                        democrats[0][j-1]+=1;
                    }
                    //'n'
                    else 
                    {
                        data[i][j]= 'n';
                        democrats[1][j-1]+=1;
                    }
                }
            }

        }
        
    }
    
    // for (size_t i = 0; i < data.size(); i++)
    // {
    //     std::cout<<data[i]<<std::endl;
    // }
    // std::cout<<std::endl<<std::endl<<std::endl;
    // for (size_t i = 0; i < 3; i++)
    // {
    //     for (size_t k = 0; k < 16; k++)
    //     {
    //         std::cout<<democrats[i][k]<<' ';
    //     }
    //     std::cout<<std::endl;
    // }
    

    testSetSize = data.size()/10;
    double sumAccuracy=0.0;
    double curAccuracy=0.0;
    
    std::random_shuffle ( data.begin(), data.end(), myrandom);

    for (size_t i = 0; i < CVk; i++)
    {
        testSetStartIndex=i*testSetSize;
        
        //this is the test set
        for (size_t j = testSetStartIndex; j < testSetStartIndex + testSetSize; j++)
        {
            if(testSetStartIndex != 0 )
            {
                calcProbTable(data[j-testSetSize],1);
            }
            calcProbTable(data[j],-1);
        }
        
        int correct= countPredictedCorrect(testSetStartIndex);
        curAccuracy = (double)(correct)/(double)(testSetSize);
        std::string out="10th-fold-cv iter [";
        out+=std::to_string(i+1);
        out+="] ";

        std::cout<<out<<"accuracy: "<<curAccuracy<<std::endl;
        sumAccuracy+=curAccuracy;
    }

    std::cout<<"\n===============================\n\n";
    std::cout<<"Avarage accuracy: "<<sumAccuracy/10.000000<<"\n\n";
    

    // for (size_t i = 0; i < count; i++)
    // {
    //     /* code */
    // }
   
}