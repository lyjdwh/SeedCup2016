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
bool FindText(char *&str,const char *text1,line_node &lnode,string &text,vector <line_node> &word_analysier);
int main()
{
    vector <line_node> word_analysier;
    PreProcess(word_analysier);
    count <<word_analysier[0].word[1]<<endl;


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
        while(*str!='\0')
        {
            if(*str==' '&&!text.empty())
            {
                lnode.word.push_back(text);
                lnode.word_number++;
                text="";
            }
            else if(FindText(str,"(",lnode,text,word_analysier))
            {
            }
            else if(FindText(str,")",lnode,text,word_analysier))
            {
            }
            else if(FindText(str,"{",lnode,text,word_analysier))
            {
            }
            else if(FindText(str,"}",lnode,text,word_analysier))
            {

            }
            else if(FindText(str,"++",lnode,text,word_analysier))
            {

            }
            else if(FindText(str,"--",lnode,text,word_analysier))
            {

            }
            else if(FindText(str,"+",lnode,text,word_analysier)
            {

            }
            else if(FindText(str,"-",lnode,text,word_analysier))
            {

            }
            else if(FindText(str,"=",lnode,text,word_analysier))
            {

            }
            else if(FindText(str,";",lnode,text,word_analysier))
            {
            }
            else if(FindText(str,"\"",lnode,text,word_analysier))
             {
                while(!FindText(str,"\"",lnode,text,word_analysier))
                    str++;
            }else if(FindText(str,"\\\\",lnode,text,word_analysier))
            {
                lnode.word.pop_back();
                lnode.word_number--;
            }
            else if(FindText(str,"\\*",lnode,text,word_analysier))
            {
                lnode.word.pop_back();
                lnode.word_number--;
                 while(!FindText(str,"*\\",lnode,text,word_analysier))\
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


        }

    }

}
bool FindText(char *&str,const char *text1,line_node &lnode,string &text)
{
    size_t len =strlen(text);
    char * read=str;
    while(*read==' ')read++;
    if(strncmp(read,text,len))
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
        if(*str=='\0')
        {
            word_analysier.push_back(lnode);
            getline(input,line);
            line_number++;
            lnode.line_number=line_number;
            lnode.word_number=0;
            str=const_cast<char*>(line.c_str());
        }
        return true;
    }else{
        return false;
    }
}
