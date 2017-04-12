/**
电话号码的标准格式是七位十进制数，并在第三、第四位数字之间有一个连接符。
电话拨号盘提供了从字母到数字的映射，映射关系如下： 
A, B, 和C 映射到 2 
D, E, 和F 映射到 3 
G, H, 和I 映射到 4 
J, K, 和L 映射到 5 
M, N, 和O 映射到 6 
P, R, 和S 映射到 7 
T, U, 和V 映射到 8 
W, X, 和Y 映射到 9 

Q和Z没有映射到任何数字，连字符不需要拨号，可以任意添加和删除。 
TUT-GLOP的标准格式是888-4567，310-GINO的标准格式是310-4466，3-10-10-10的标准格式是310-1010。 

如果两个号码有相同的标准格式，那么他们就是等同的（相同的拨号） 

你的公司正在为本地的公司编写一个电话号码薄。作为质量控制的一部分，
你想要检查是否有两个和多个公司拥有相同的电话号码。 

输入的格式是，第一行是一个正整数，指定电话号码薄中号码的数量（最多100000）。
余下的每行是一个电话号码。每个电话号码由数字，大写字母（除了Q和Z）以及连接符组成。
每个电话号码中只会刚好有7个数字或者字母。

对于每个出现重复的号码产生一行输出，输出是号码的标准格式紧跟一个空格然后是它的重复次数。
如果存在多个重复的号码，则按照号码的字典升序输出。如果输入数据中没有重复的号码，输出一行： 
No duplicates. 
**/
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>
using namespace std;

/**
*  功能：根据映射关系把字符转换为0~9的字符，映射关系如下：
*        A, B, 和C 映射到 2 
*        D, E, 和F 映射到 3 
*        G, H, 和I 映射到 4 
*        J, K, 和L 映射到 5 
*        M, N, 和O 映射到 6 
*        P, R, 和S 映射到 7 
*        T, U, 和V 映射到 8 
*        W, X, 和Y 映射到 9 
*  参数：
*    ch：需要转换的字符
*  返回值：
*    返回转换后的0~9的字符。不在映射关系中的返回字符'-'。
**/
char CharToNumber(char ch)
{
    if (ch == 'Q' || ch == 'Z')
    {
        return '-';
    }
    
    if ((ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
    {
        switch(ch)
        {
            case '0':
                return '0';
            case '1':
                return '1';
            case '2':
            case 'A':
            case 'B':
            case 'C':
                return '2';
            case '3':
            case 'D':
            case 'E':
            case 'F':
                return '3';
            case '4':
            case 'G':
            case 'H':
            case 'I':
                return '4';
            case '5':
            case 'J':
            case 'K':
            case 'L':
                return '5';
            case '6':
            case 'M':
            case 'N':
            case 'O':
                return '6';
            case '7':
            case 'P':
            case 'R':
            case 'S':
                return '7';
            case '8':
            case 'T':
            case 'U':
            case 'V':
                return '8';
            case '9':
            case 'W':
            case 'X':
            case 'Y':
                return '9';
            default:
                return '-';
        }
    }
    else
    {
        return '-';
    }
}


/**
*  功能：将字符串转换为数字和'-'组合形式的字符串。
*  参数：
*    str：包含大写字母、'-'或数字的字符串。
*  返回值： 
*    返回值存储在str中。
**/
char* StrToNumbers(char * const str)
{
    if (str == NULL)
    {
        return NULL;
    }

    int iLen = strlen(str);
    for (int i=0; i<iLen; i++)
    {
        str[i] = CharToNumber(str[i]);
    }
    return str;
}


/**
*  功能：转换为标准的电话号码格式
*  参数：
*    str：由数字和'-'组合的字符串。
*  返回值：
*    返回标准的电话号码格式字符串。由调用者释放内存。
**/
char* Out(const char* str)
{
    if (str == NULL)
    {
        return NULL;
    }
    
    int iLen = strlen(str);
    
    char* newStr = (char *)malloc(9);
    if (newStr == NULL)
    {
        return NULL;
    }
    memset(newStr, 0, 9);
    
    int j=0;
    for (int i=0; i<iLen; i++)
    {
        if (str[i] == '-')
        {
            continue;
        }
        if (j == 3)
        {
           newStr[j++] = '-'; 
        }
        newStr[j++] = str[i];
    }
    
    newStr[8] = '\0';
    
    return newStr;
}



int main()
{
#if 0
    int iCount = 0;
    cin >> iCount;
    if (iCount == 0)
    {
        cout << "No duplicates" << endl;
        return 0;
    }
    
    char (*data)[64] = (char(*)[64])malloc(64*iCount);
    memset(data, 0, 64*iCount);
    for (int i=0; i<iCount; i++)
    {
        cin >> data[i];
    }
#endif    
    
    
#if 1
    char data[][16] = { "4873279",  "ITS-EASY", "888-4567",  "3-10-10-10",
                        "888-GLOP", "TUT-GLOP", "967-11-11", "310-GINO",
                        "F101010",  "888-1200", "487-3279",  "-4-8-7-3-2-7-9-",
                        "0000000",  "000-0000"
                      };
    int iCount = 14;
#endif                                        
    
    map<string, int> phone;
    int flag = 0;
    for (int i=0; i<iCount; i++)
    {
        char *result = Out(StrToNumbers( data[i] ) );
        string str = result;
        if (result != NULL)
        {
            free(result);
            result = NULL;
        }
        int count = phone.count(str);
        if ( count == 0)
        {
            phone.insert(make_pair(str, 1));
        }
        else
        {
            phone[str] += 1;
            flag = 1;
        }
    }
    if (flag == 0)
    {
        cout << "No duplicates" << endl;
    }
    else
    {
        map<string, int>::const_iterator it; 
        for (it = phone.begin(); it != phone.end(); ++it)
        {
            if (it->second > 1)
            {
                cout << it->first << " " << it->second << endl;
            }
        }        
    }  
    if (data != NULL)
    {
        //free(data);
        //data = NULL;
    }
    return 0;
}




















