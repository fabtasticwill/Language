#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

string remove_letter_easy( std::string str, char c )
{
    str.erase( std::remove( str.begin(), str.end(), c ), str.end() ) ;
    return str ;
}

string itos(int i) // convert int to string
{
    stringstream s;
    s << i;
    return s.str();
}

bool isStringDigit(string text)
{
    for(int a = 0; a < text.length();a++)
    {
        if(!isdigit(text[a]))
            return false;
    }
    return true;
}
void error(string message)
{
    cout<<"Error: "+message+"\n";
}
int main()
{
    std::map<string, string> var;
    string buffer[9999];
    int temp;
    int varSize;
    ifstream file("test.run");
    string unused;

    for(int c = 1;!file.eof();c++)
    {
        file>>buffer[c];
    }
    file.clear();
    file.seekg(0, ios::beg);
    for(int d = 0;d<9999;d++)
    {
        if(var[buffer[d]] != "" && buffer[d+1] == "=")
        {
            var[buffer[d]] = buffer[d+2];
        }

        if (buffer[d] == "int")
        {
            if(buffer[d+2] == "=")
            {
                if(!isStringDigit(buffer[d+3]))
                    error("Token: "+itos(d+3)+": "+buffer[d+1]+" is not an int.");
                else
                    var[buffer[d+1]] = buffer[d+3];
            }
            else var[buffer[d+1]] = "||";
        }

        if (buffer[d] == "string")
        {
            if(buffer[d+2] == "=")
            {
                if(buffer[d+3][0] != '\"' || buffer[d+3][buffer[d+3].length()-1] != '\"')
                    error("Token: "+itos(d+3)+": "+buffer[d+1]+": Expected \"");
                else
                    var[buffer[d+1]] = buffer[d+3];
            }
            else var[buffer[d+1]] = "||";
        }

        if(buffer[d] == "echo")
        {

                varSize = var[buffer[d+1]].length();
                if(buffer[d+1][0] == '"')
                {
                    if(buffer[d+1][0] != '\"' || buffer[d+1][buffer[d+1].length()-1] != '\"')
                        error("Token: "+itos(d+1)+": "+buffer[d+1]+": Expected \"");
                    else
                    {
                        buffer[d+1] = buffer[d+1];
                        for(int e = 0;e < buffer[d+1].length();e++)
                        {
                            if(buffer[d+1][e] == '\\' && buffer[d+1][e+1] == 'n')
                            {
                                cout<<'\n';
                                e++;
                            }
                            else
                                cout<<buffer[d+1][e];
                        }
                    }
                }
                else {
                    if(var[buffer[d+1]] == "")
                        error("Token: "+itos(d+1)+": "+buffer[d+1]+" has not been initialized.");
                    else
                    {
                        var[buffer[d+1]] = remove_letter_easy(var[buffer[d+1]], '"');
                        for(int e = 0;e < varSize;e++)
                        {
                            if(var[buffer[d+1]][e] == '\\' && var[buffer[d+1]][e+1] == 'n')
                            {
                                cout<<'\n';
                                e++;
                            }
                            else
                                cout<<var[buffer[d+1]][e];
                        }
                    }
                }

        }
        if(d != 0 && buffer[d] != "int" && buffer[d] != "string" && buffer[d] != "echo" && buffer[d] != "=" && buffer[d] != "+" && buffer[d] != "-" && buffer[d] != "*" && var[buffer[d]] == "" && isStringDigit(buffer[d]) == false && buffer[d][0] != '#' && buffer[d][0] != '"' && buffer[d][buffer[d].size()-1] != '"')
        {
            error("Token: "+itos(d)+": Unrecognised token: "+buffer[d]);
            break;
        }

    }
    getchar();
    return 0;
}
