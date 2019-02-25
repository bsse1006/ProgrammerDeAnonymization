#include "signatureAnalyzer.h"

#include "code.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int braceCounter = 0;

string dataTypesArray [6] = {"int ", "double ", "float ", "string ", "bool ", "char "};

vector <string> dataTypes (dataTypesArray,dataTypesArray+sizeof(dataTypesArray)/sizeof(string));

bool isSignature (string line)
{
    if((line.find("for")!=string::npos||line.find("while")!=string::npos)&&line.find('(')!=string::npos)
        return true;

    if(braceCounter==0)
    {
        for(vector <string> :: iterator itr = dataTypes.begin(); itr!=dataTypes.end(); itr++)
        {
            if(line.find(*itr)!=string::npos&&line.find('(')!=string::npos)
               return true;
        }
    }
    return false;
}

double signatureAnalyzer (string fileName)
{
    vector <string> inputCode = readCode(fileName);
    vector <string> :: iterator codeItr;

    int numberOfSignature = 0;
    int numberOfSpaces = 0;

    for(codeItr=inputCode.begin();codeItr!=inputCode.end();codeItr++)
    {
        if(isSignature(*codeItr))
        {
            for(int startPoint = (*codeItr).find_first_not_of(' '); (*codeItr)[startPoint]!='\0'; startPoint++)
            {
                if((*codeItr)[startPoint]==' ')
                    numberOfSpaces++;
            }
            numberOfSignature++;
        }

        if((*codeItr).find('{')!=string::npos) braceCounter++;
        if((*codeItr).find('}')!=string::npos) braceCounter--;
    }

    return (double)numberOfSpaces/numberOfSignature;
}

