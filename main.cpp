#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <new>
#include <cstring>
#include <stack>
#include <queue>
#include <map>
#include <sstream>

using namespace std;
typedef struct {
    vector<string> word;
    int word_number;
    int line_number;
} line_node;

typedef struct  var_node {
    string name;
    bool is_var;
    union
    {
        int value;
        struct var_node *scope;
    }content;
    struct var_node *next;
    struct var_node *parent;
} var_node; //

void PreProcess(vector<line_node> &word_analysier);//词法分析,能很好地处理注释
bool FindText(char *&str,const char *text1,line_node &lnode,string &text);//寻找特定字符，并过滤之前空格
void CreateVarTree(vector<line_node> &word_a,var_node *current,vector <line_node>::iterator &iter_c1,vector <string>::iterator &iter_c2,int &flag1);
var_node* SearchVar(string name,var_node *base);
bool IsStr(string str);
int Precede(string str1,string str2);
int CalcExpression(queue <string>& expression);
int main()
{
    vector <line_node> word_analysier;//存储词法分析器运行结果
    var_node * var_tree=new var_node;
    vector <line_node>::iterator iter_c1;
    vector <string>::iterator iter_c2;
    int flag1=0;
    var_tree->is_var=false;
    PreProcess(word_analysier);
    iter_c1=word_analysier.begin();
    iter_c2=((word_analysier.begin())->word).begin();
    cout <<*(((word_analysier.begin())->word).begin())<<endl;
    CreateVarTree(word_analysier,var_tree,iter_c1,iter_c2,flag1);
    //输出结果
//    for (int j=0;j<word_analysier.size();j++)
//    {
//    for(int i=0;i<word_analysier[j].word_number;i++)//word_analysier[10].word_number
//        cout <<word_analysier[j].word[i]<<"\t";
//    cout <<word_analysier[j].line_number<<endl;
//    }
    queue <string> expression;

    expression.push("3");
    expression.push("+");
    expression.push("3");
    expression.push("*");
    expression.push("2");

    int result=CalcExpression(expression);
    cout << result <<endl;

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
            else if(FindText(str,",",*lnode,text))
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

void CreateVarTree(vector <line_node> &word_a,var_node *current,vector <line_node>::iterator &iter_c1,vector <string>::iterator &iter_c2,int &flag1)

{
    int flag=0;
    var_node * p;
    var_node *base=current;
    vector<line_node>::iterator iter_1;
    vector <string>::iterator iter_2;
    for(iter_1=iter_c1;iter_1!=word_a.end();iter_1++)
    {
        if(flag==0)
        {
            iter_2=iter_c2;
            flag++;
        }else{
            iter_2=iter_1->word.begin();
        }

        for(;iter_2!=(iter_1->word).end();iter_2++)
        {
            if(*iter_2=="for")
            {
                iter_2++;
                current->content.scope=new var_node;
                current->content.scope->is_var=false;
                current->content.scope->parent=current;
                flag1++;
                CreateVarTree(word_a,current->content.scope,iter_1,iter_2,flag1);
                flag1--;
            }
            if(*iter_2=="int")
            {
                while(*iter_2!=";")
                {
                    iter_2++;
                    if(IsStr(*(iter_2))&&*(iter_2+1)!="=")
                    {
                        p=new var_node;
                        p->name=*iter_2;
                        p->is_var=true;
                        p->parent=base;
                        current->next=p;
                        current=p;

                    }else if(IsStr(*(iter_2))&&*(iter_2+1)=="=")
                    {
                        p=new var_node;
                        p->name=*iter_2;
                        p->is_var=true;
                        p->parent=base;
                        current->next=p;
                        current=p;
                        while(1)
                        {
                            if(*iter_2==","||*iter_2==";")
                            {
                                break;
                            }else{
                                iter_2++;
                            }
                        }


                    }

                }
                if(flag1!=0)
                {
                    iter_c1=iter_1;
                    iter_c2=iter_2;
                    return;
                }
            }
        }
    }

}
bool IsStr(string str)
{
    if(str!="+"&&str!="-"&&str!="++"&&str!="--"&&str!="="&&str!="=="&&str!="}"&&str!=")"
            &&str!="{"&&str!="("&&str!="}"&&str!="\""&&str!=";"&&str!=","&&str!="#"&&str!="*"&&str!="/"&&str!="(")
    {
        return true;
    }else{
        return false;
    }
}
var_node * SearchVar(string name,var_node *base)
{
    int has_found;
    var_node * cursor=base->next;
    while(cursor!=NULL)
    {
        if(cursor->is_var &&cursor->name==name)
        {
            has_found=true;
            break;
        }
        if(cursor->next==NULL){
            cursor =cursor ->parent;
            cursor=cursor->parent;
        }else{
            cursor =cursor->next;
        }
    }
    if(has_found)
    {
        return cursor;
    }else{
        return NULL;
    }
}

int CalcExpression(queue <string> &expression)
{
    stack <string,vector<string> > optr,oped;//oped:number; optr:fuhao
    stringstream stream;
    int a;
    int b;
    int flag=0;
    string temp;
    string result;
    expression.push("#");

    while(!expression.empty())
    {
        if(IsStr(expression.front()))
        {
            oped.push(expression.front());
            expression.pop();
        }else{
            if (flag==0)
            {
                 optr.push(expression.front());
                 expression.pop();
                 flag++;

            }
            else
            {
                 if(optr.empty()){
                     stream <<oped.top();
                     stream >> a;
                     stream.clear();
                     oped.pop();
                     temp=expression.front();
                     expression.pop();
                     stream <<expression.front();
                     stream >> b;
                     stream.clear();
                     expression.pop();
                     if(temp=="+")
                     {
                         a=a+b;

                     }
                    else if(temp=="-")
                     {
                         a=b-a;

                     }
                     else if(temp=="*")
                     {
                         a=a*b;

                     }
                    else if(temp=="/")
                     {
                         a=b/a;

                     }
                         stream <<a;
                         stream >> result;
                         stream.clear();
                         oped.push(result);

 //                    optr.push(expression.front());


                 }
                else if(Precede(expression.front(),optr.top())==0){
                    optr.pop();
                    expression.pop();
                }else if(Precede(expression.front(),optr.top())==-2)
                {
                    optr.push(expression.front());
                    expression.pop();

                }else if(optr.top()=="(")
                {
                    optr.push(expression.front());
                    expression.pop();

                }
                else if((Precede(expression.front(),optr.top())==-1) ||expression.front()==")"){
                    stream <<oped.top();
                    stream >> a;
                    stream.clear();
                    oped.pop();

                    stream <<oped.top();
                    stream >> b;
                    stream.clear();
                    oped.pop();
                    temp=optr.top();
                    optr.pop();
                    if(temp=="+")
                    {
                        a=a+b;

                    }
                   else if(temp=="-")
                    {
                        a=b-a;

                    }
                    else if(temp=="*")
                    {
                        a=a*b;

                    }
                   else if(temp=="/")
                    {
                        a=b/a;

                    }
                        stream <<a;
                        stream >> result;
                        stream.clear();
                        oped.push(result);

//                    optr.push(expression.front());
                        optr.pop();
                    expression.pop();
                }else if(Precede(expression.front(),optr.top())==1)
                {
                    temp=expression.front();
                    expression.pop();
                    stream <<oped.top();
                    stream >> a;
                    stream.clear();
                    oped.pop();
                    stream << expression.front();
                    stream >> b;
                    stream.clear();
                    expression.pop();

                    if(temp=="+")
                    {
                        a=a+b;

                    }
                   else if(temp=="-")
                    {
                        a=b-a;

                    }
                    else if(temp=="*")
                    {
                        a=a*b;

                    }
                   else if(temp=="/")
                    {
                        a=b/a;

                    }

                        stream <<a;
                        stream >> result;
                        stream.clear();
                        oped.push(result);
                }


            }
        }
    }
    stream << oped.top();
    stream >> a;
    stream.clear();
    return a;

}
int Precede(string str1,string str2)
{
    map <string,map<string,int> > str_map;
    vector<string> str={"+","-","*","/","(",")","#"};
    int i,j;
    int value[7][7]={1,1,-1,-1,-1,1,1,1,1,-1,-1,-1,1,1,1,1,1,1,-1,1,1,1,1,1,1,-1,1,1,-1,-1,-1,-1,-1,0,-2,1,1,1,1,1,1,1,-1,-1,-1,-1,-1,1,0};
    for(i=0;i<7;i++)
        for(j=0;j<7;j++)
            str_map[str[i]][str[j]]=value[i][j];
    str_map["+"]["+"]=1;

    return str_map[str1][str2];

}

