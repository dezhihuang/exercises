/**
Description

对数值很大、精度很高的数进行高精度计算是一类十分常见的问题。比如，对国债进行计算就是属于这类问题。 

现在要你解决的问题是：对一个实数R( 0.0 < R < 99.999 )，要求写程序精确计算 R 的 n 次方(Rn)，其中n 是整数并且 0 < n <= 25。


Input

T输入包括多组 R 和 n。 R 的值占第 1 到第 6 列，n 的值占第 8 和第 9 列。


Output

对于每组输入，要求输出一行，该行包含精确的 R 的 n 次方。输出需要去掉前导的 0 后不要的 0 。如果输出是整数，不要输出小数点。
**/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
* 描述：多位数乘以一位数
* 参数：
*   many:  多位数字符串
*   one:   一位数，字符表示
*   offset: 表示one当前所处在的位置，0表示个位，1表示十位，2表示百位
* 返回值：
*   返回运算结果的字符串，调用者释放内存。
**/
char *ManyMOne(const char *many, char one, int offset)
{
    if (many == NULL)
    {
        return NULL;
    }
    if (one > '9' || one < '0')
    {
        return NULL;
    }
    
    // 多位数的位数
    int iLen = strlen(many);
    
    //加第一个1为高位保留位，因为可能乘积高于many的位数
    //加第二个1，字符串结束符0
    char *result = (char *)malloc(iLen+1+offset+1);
    if (result == NULL)
    {
        printf("内存分配失败！\n");
        return NULL;
    }
    memset(result, 0, iLen+1+offset+1);
    for(int i=0; i<iLen+1+offset+1; i++)
    {
        result[i] = '0';          // 初始化为0 
    }
    result[iLen+1+offset] = '\0'; // 字符串结束符
    
    int iOne = one - '0';
    int iCarry = 0; //进位
    for (int i=iLen-1; i>=0; i--) 
    {
        int iTmp     = many[i] - '0';
        int iProduct = iTmp * iOne + iCarry; // 整数相乘并加上进位
        iCarry       = iProduct / 10;        // 进位
        result[i+1]  = iProduct % 10 + '0';
    }
    result[0] = iCarry + '0'; //高位为进位

    return result;
}


/**
* 描述：多位数加多位数
* 参数：
*   num1: 字符串类型的多位数1，存储计算结果
*   num2: 字符串类型的多位数2
* 返回值：  
*   无
**/
void Add(char * const num1, const char *num2)
{
    if (num1 == NULL || num2 == NULL)
    {
        return;
    }
    int iLen1 = strlen(num1);
    int iLen2 = strlen(num2);

    // 第一个多位数存储空间不能小于第二个多位数，目的是为了将结果保存在第一个变量中
    if (sizeof(num1) < sizeof(num1))
    {
        return;
    }
    int n = iLen1 - iLen2;
    
    int iCarry = 0; //进位
    for (int i = iLen2-1,j=iLen1-1; i>=0; i--,j--)
    {
        int iNum1 = num1[j] - '0';
        int iNum2 = num2[i] - '0';
        int sum   = iNum1 + iNum2 + iCarry;
        
        num1[i+n] = sum % 10 + '0';
        iCarry = sum / 10;
    }
    if (iCarry != 0)
    {
       num1[n-1] = iCarry + '0'; 
    } 
}


/**
* 描述：多位数相乘
* 参数：
*   num1：多位乘数1
*   num2：多位乘数2
* 返回值：
*   返回两数相乘结果。需要调用者释放内存。
**/
char *ManyM(const char *num1, const char *num2)
{
    if (num1 == NULL || num2 == NULL)
    {
        return NULL;
    }

    int iLen1 = strlen(num1);
    int iLen2 = strlen(num2);
    int iLen = iLen1+iLen2+1;

    // 分配空间并初始化
    char *result = (char *)malloc(iLen);
    if (result == NULL)
    {
        printf("内存分配失败！\n");
        return NULL;
    }
    memset(result, 0, iLen);
    for (int i=0; i<iLen-1; i++)
    {
        result[i] = '0';
    }
    result[iLen-1] = '\0';
    
    // 以位数最小的作为乘数，以减小相乘次数
    if (iLen1 > iLen2)
    {
        for (int i=iLen2-1; i>=0; i--)
        { 
            char *sr = ManyMOne(num1, num2[i], iLen2-i-1); 
            if (sr != NULL)
            {
                Add(result, sr);
                free(sr);
                sr = NULL;
            }
            else
            {
                return NULL;
            }
        }
    }
    else
    {
       for (int i=iLen1-1; i>=0; i--)
        { 
            char *sr = ManyMOne(num2, num1[i], iLen1-i-1);
            if (sr != NULL)
            {
                Add(result, sr);
                free(sr);
                sr = NULL;
            }
            else
            {
                return NULL;
            }
        } 
    }

    return result;
}

/**
*  描述：输出符合要求的数据
*  参数：  
*   in：原始数据
*   flag: 是否为小数。1是小数，0不是小数
*  返回值：返回经过处理的符合要求的数据
*
**/
char *Out(const char *in, int flag)
{
    int len = strlen(in);
    if (len == 0)
    {
        return NULL;
    }
    else if(len == 1)
    {
       return (char *)in; 
    }

    if (flag) //是小数
    {
        //起始位置和结束位置都不为'0'表示数据符合要求，直接返回
        if (in[0] != '0' && in[len-1] != '0')
        {
            return (char *)in;
        } 
        
        char *result = (char *)malloc(len+1);
        memset(result, 0, len+1);
        int pos1 = -1;
        int pos2 = -1;
        
        // 查找整数部分第一个不为'0'的位置
        for (int i=0; i<len; i++)
        {
            if (in[i] > '0' || in[i] == '.')
            {
                pos1 = i;
                break;
            }
        }        
        // 查找小数部分最后一个不为'0'的位置
        for (int i=len-1; i>=0; i--)
        {
            if (in[i] > '0' || in[i] == '.')
            {
                pos2 = i;
                break;
            }
        }
        for (int i=pos1,j=0; i<=pos2; i++)
        {
            result[j++] = in[i];
        }
        if (in[pos2] == '.')
        {
            result[pos2-pos1] = '\0';
        }
        else
        {
            result[pos2-pos1+1] = '\0';  
        }
        if(strlen(result) == 0)
        {
            result[0] = '0';
        }
        return result;
    }
    else 
    {        
        //起始位置不为'0'表示数据符合要求，直接返回
        if (in[0] != '0')
        {
            return (char *)in;
        }

        char *result = (char *)malloc(len);
        memset(result, 0, len);
        int isZero = 1;
        int j = 0;
        for (int i=0; i<len; i++)
        {
            if (in[i] != '0')
            {
                isZero = 0;
            }
            if (!isZero)
            {
                result[j++] = in[i];
            }
        }
        if(strlen(result) == 0)
        {
            result[0] = '0';
            result[1] = '\0';
        }
        else
        {
            result[j] = '\0';
        }
        return result;
    }
}


/**
*  描述：求高精度幂
*  参数：
*   num1：底数
*   n:    指数
*  返回值：
*   返回字符串类型的计算结果
**/
char *myPower(const char *num1, int n)
{
    if (n == 0)
    {
        return (char *)"1";
    }
   
    int iLen = strlen(num1);
    char *tmpNum = (char *)malloc(iLen+1);
    if (tmpNum == NULL)
    {
        printf("内存分配失败！\n");
        return NULL;
    }
    memset(tmpNum, 0, iLen+1);
    
    // 查找是否有小数点，并记下其下标
    int iPos = -1;
    char *tmp = (char *)num1;
    char *p = strchr(tmp, '.');
    if (p == NULL) // 没有小数点
    {
        strcpy(tmpNum, num1);
    }
    else
    {
        for (int i=0,j=0; i<iLen; i++)
        {
            if (num1[i] == '.')
            {
                iPos = i; // 小数点的小标
                continue;
            }
            tmpNum[j++] = num1[i];
        }
        tmpNum[iLen-1] = '\0';
    }

    if (n == 1)
    {
        if (iPos == -1) // 没有小数点
        {
            return Out(num1, 0);
        }
        else
        {
            return Out(num1, 1);
        }   
    }

    char *result = ManyM(tmpNum, tmpNum);
    if (result == NULL)
    {
        return NULL;
    }

    for (int i=n; i>2; i--)
    {
        char *p = result;       
        result = ManyM(result, tmpNum);           
        if (result == NULL)
        {
            return NULL;
        }
        if (p != NULL)
        {
            free(p);
            p = NULL;
        }
    }

    if (tmpNum != NULL)
    {
        free(tmpNum);
        tmpNum = NULL;
    }
    
    if (iPos == -1)
    {
        return Out(result, 0);
    }
    
    int n2 = iLen - iPos - 1; // 小数位数
    n2 = n2 * n;
    int iLen2 = strlen(result);
    int tmpPos = iLen2 - n2 - 1;
    if (tmpPos < 0)
    {
        tmpPos = 0;
    }
    
    char *tmpResult = (char *)malloc(iLen2+2);
    if (tmpResult == NULL)
    {
        printf("内存分配失败！\n");
        return NULL;
    }
    memset(tmpResult, 0, iLen2+2);

    tmpResult[iLen2+1] = '\0';
    int j = iLen2;
    for (int i=iLen2-1; i>=0; i--)
    {
        if (i == tmpPos)
        {
            tmpResult[j--] = '.';
        }
        tmpResult[j--] = result[i];
    }
    return Out(tmpResult, 1);
}


int main()
{ 
#if 0
    char number[256] = {0};
    int n = 0;
    while(scanf("%s %d", number, &n) != EOF)
    {
        printf("%s\n", myPower(number, n));
    }
#endif

#if 1
    char data[][8] ={"95.123", "0.4321", "5.1234", "6.7592", "98.999", "1.0100", ".00001", ".12345", "0001.1", "1.1000",
                     "10.000", "000.10", "000000", "000.00", ".00000", "000010", "000.10", "0000.1", "00.111", "0.0001",
                     "0.0001", "0.0010", "0.0010", "0.0100", "0.0100", "0.1000", "0.1000", "1.0000", "1.0000", "1.0001",
                     "1.0001", "1.0010", "1.0010", "1.0100", "1.0100", "1.1000", "1.1000", "10.000", "10.000", "10.001",
                     "10.001", "10.010", "10.010", "10.100", "10.100", "99.000", "99.000", "99.001", "99.001", "99.010",
                     "99.010", "99.100", "99.100", "99.998", "99.998"} ;

    for (int i=0; i<55; i++)
    {
        int n = i%2 == 0 ? 1:3;
        printf("%d: %d %s\n", i, n, myPower(data[i], n));
    } 

    char data2[][8] = {"95.123", "0.4321", "5.1234", "6.7592", "98.999", "1.0100"};
    int n[] = {12, 20, 15, 9, 10, 12};
    for (int i=0; i<6; i++)
    {
        printf("%d: %d %s\n", i, n[i], myPower(data2[i], n[i]));
    }
    
    char data3[][18] = {"00.00", "11.11", "0011.1100", "001100", "1234", "1.00", "100", "001", "1.1"};
    for (int i=0; i<9; i++) 
    {
        printf("%d: %s\n", i, myPower(data3[i], 0));
    }
    for (int i=0; i<9; i++) 
    {
        printf("%d: %s\n", i, myPower(data3[i], 1));
    }
    for (int i=0; i<9; i++) 
    {
        printf("%d: %s\n", i, myPower(data3[i], 2));
    }
    for (int i=0; i<9; i++) 
    {
        printf("%d: %s\n", i, myPower(data3[i], 3));
    }
    for (int i=0; i<9; i++) 
    {
        printf("%d: %s\n", i, myPower(data3[i], 4));
    }
    
#endif    
    return 0;

}

