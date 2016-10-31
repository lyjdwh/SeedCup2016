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
void PreProcess(vector<line_node> &word_analysier);//词法分析,能很好地处理注释
bool FindText(char *&str,const char *text1,line_node &lnode,string &text);//寻找特定字符，并过滤之前空格
int main()
{
    vector <line_node> word_analysier;//存储词法分析器运行结果
    PreProcess(word_analysier);
    //输出结果
    for (int j=0;j<word_analysier.size();j++)
    {
    for(int i=0;i<word_analysier[j].word_number;i++)//word_analysier[10].word_number
        cout <<word_analysier[j].word[i]<<"\t";
    cout <<word_analysier[j].line_number<<endl;
    }
}
void PreProcess(vector <line_node> &word_analysier)
{
    char *str;
    string line;
    string text;
    ifstream input;
    line_node *lnode;
    int line_number=0;
    input.open("input.txt");
    if(!input)
        cerr << "couldn't open: input.txt";
    while(getline(input,line))
    {
        lnode = new line_node;
        line_number++;
        lnode->line_number=line_number;
        lnode->word_number=0;
        str=const_cast<char*>(line.c_str());

        while(*str!='\r')//因为一行的结尾为\r\n，getline把\n去掉了,所以通过判断\r看是否到末尾
        {
            if(*str == ' '&&!text.empty())
            {
                lnode->word.push_back(text);
                lnode->word_number++;
                text="";
            }else if(FindText(str,"//",*lnode,text))
            {
                lnode->word.pop_back();
                lnode->word_number--;
                word_analysier.push_back(*lnode);
                break;
            }
            else if(FindText(str,"/*",*lnode,text))
            {
                lnode->word.pop_back();
                lnode->word_number--;
                 while(!FindText(str,"*/",*lnode,text))\
                 {
                     str++;
                     if(*str=='\r')
                     {
                         word_analysier.push_back(*lnode);
                         lnode = new line_node;
                         getline(input,line);
                         line_number++;
                         lnode->line_number=line_number;
                         lnode->word_number=0;
                         str=const_cast<char*>(line.c_str());

                     }
                 }
                 lnode->word.pop_back();
                 lnode->word_number--;
            }
            else if(FindText(str,"(",*lnode,text))
            {
            }
            else if(FindText(str,")",*lnode,text))
            {
            }
            else if(FindText(str,"{",*lnode,text))
            {
            }
            else if(FindText(str,"}",*lnode,text))
            {

            }
            else if(FindText(str,"++",*lnode,text))
            {

            }
            else if(FindText(str,"--",*lnode,text))
            {

            }
            else if(FindText(str,"+",*lnode,text))
            {

            }
            else if(FindText(str,"-",*lnode,text))
            {

            }
            else if(FindText(str,"==",*lnode,text))
            {

            }
            else if(FindText(str,"=",*lnode,text))
            {

            }
            else if(FindText(str,";",*lnode,text))
            {
            }
            else if(FindText(str,"\"",*lnode,text))
             {
                while(!FindText(str,"\"",*lnode,text))
                    str++;
            }else{
                text=text+*str;
                str++;
            }
            if(*str=='\r')
            {
                if(!text.empty())
                {
                    lnode->word.push_back(text);
                    lnode->word_number++;
                }
                word_analysier.push_back(*lnode);
                lnode = new line_node;


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
    if(*read=='\t')//\t不属于空格
        read++;
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


