#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <new>
#include <cstring>

using namespace std;
typedef struct {
    vector<string> word;
    int word_number;
    int line_number;
} line_node;
void PreProcess(vector<line_node> &word_analysier);
bool FindText(char *&str,const char *text1,line_node &lnode,string &text);
int main()
{
    vector <line_node> word_analysier;
    PreProcess(word_analysier);
    for(int i=0;i<word_analysier[10].word_number;i++)
        cout <<word_analysier[10].word[i]<<"\t"<<endl;

}
void PreProcess(vector <line_node> &word_analysier)
{
    char *str;
    string line;
    string text;
    ifstream input;
    line_node lnode;
    int line_number;
    input.open("input.txt");
    if(!input)
        cerr << "couldn't open: input.txt";
    while(getline(input,line))
    {
        line_number++;
        lnode.line_number=line_number;
        lnode.word_number=0;
        str=const_cast<char*>(line.c_str());

        while(*str!='\r')
        {
            if(*str == ' '&&!text.empty())
            {
                lnode.word.push_back(text);
                lnode.word_number++;
                text="";
            }
            else if(FindText(str,"(",lnode,text))
            {
            }
            else if(FindText(str,")",lnode,text))
            {
            }
            else if(FindText(str,"{",lnode,text))
            {
            }
            else if(FindText(str,"}",lnode,text))
            {

            }
            else if(FindText(str,"++",lnode,text))
            {

            }
            else if(FindText(str,"--",lnode,text))
            {

            }
            else if(FindText(str,"+",lnode,text))
            {

            }
            else if(FindText(str,"-",lnode,text))
            {

            }
            else if(FindText(str,"=",lnode,text))
            {

            }
            else if(FindText(str,";",lnode,text))
            {
            }
            else if(FindText(str,"\"",lnode,text))
             {
                while(!FindText(str,"\"",lnode,text))
                    str++;
            }else if(FindText(str,"\\\\",lnode,text))
            {
                lnode.word.pop_back();
                lnode.word_number--;
            }
            else if(FindText(str,"\\*",lnode,text))
            {
                lnode.word.pop_back();
                lnode.word_number--;
                 while(!FindText(str,"*\\",lnode,text))\
                 {
                     str++;
                     if(*str='\0')
                     {
                         word_analysier.push_back(lnode);
                         getline(input,line);
                         line_number++;
                         lnode.line_number=line_number;
                         lnode.word_number=0;
                         str=const_cast<char*>(line.c_str());

                     }
                 }
                 lnode.word.pop_back();
                 lnode.word_number--;
            }
            else{
                text=text+*str;
                str++;
            }
            if(*str=='\r')
            {
                if(!text.empty())
                {
                    lnode.word.push_back(text);
                    lnode.word_number++;
                }
                word_analysier.push_back(lnode);

            }


        }

    }

}
bool FindText(char *&str,const char *text1,line_node &lnode,string &text)
{
    int len =strlen(text1);

    char * read=str;
    while(*read==' ')
    {
        read++;
    }
    if(strncmp(read,text1,len)==0)
    {
        if(!text.empty())
        {
            lnode.word.push_back(text);
            lnode.word_number++;
        }
        text="";
        str=read+len;
        lnode.word.push_back(text1);
        lnode.word_number++;

        return true;
    }else{
        str=read;
        return false;
    }
}

void
