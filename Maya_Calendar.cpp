#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char haabMonth[][7] = { "pop", "no",     "zip",   "zotz",   "tzec",
                        "xul", "yoxkin", "mol",   "chen",   "yax", 
                        "zac", "ceh",    "mac",   "kankin", "muan", 
                        "pax", "koyab",  "cumhu", "uayet"};

char tzolkinDay[][9] = {"imix",  "ik",    "akbal", "kan",   "chicchan", 
                        "cimi",  "manik", "lamat", "muluk", "ok", 
                        "chuen", "eb",    "ben",   "ix",    "mem", 
                        "cib",   "caban", "eznab", "canac", "ahau"};                        

                        
/************************************************
功  能：
        将字符串格式的Haab日期
        转换为到世界开始的总天数
参  数：
        haab：Haab表示的日期
返回值：
        返回到世界开始的总天数
************************************************/                        
long HaabToDay(const char *haab)
{
    char sDay[3]   = {0};
    char sMonth[7] = {0};
    char sYear[5]  = {0};
    int iLen = strlen(haab);
    int p=0, j=0, k=0, l=0;
    for (int i=0; i<iLen; i++)
    {
        if (haab[i] == '.')
        {
            p = 1;
        }
        if (p == 0)
        {
            sDay[j++] = haab[i];
        } 
        else
        {
            if (haab[i]>='0' && haab[i]<='9')
            {
                sYear[l++] = haab[i];
            }
            else if (haab[i]>='a' && haab[i]<='z')
            {
                sMonth[k++] = haab[i];
            }
        }
    }
    sDay[j]   = '\0';
    sMonth[k] = '\0';
    sYear[l]  = '\0';
    
    int month = 0;
    for(int i=0; i<19; i++)
    {
        if(!strcmp(sMonth, haabMonth[i]))
        {
            month = i;
        }
    }
    
    int day   = atoi(sDay);
    int year  = atoi(sYear);
    
    long ret = year*365 + month*20 + day;
    return ret;
}


/************************************************
功  能：
        将Haab历法中世界开始的总天数
        转换为Tzolkin历
参  数：
        day：Haab历法中世界开始的总天数
返回值：
        返回世界开始的总天数在Tzolkin历中
        表示的具体的某一天。
        返回值由调用者释放。
************************************************/ 
char *DayToTzolkin(long day)
{
    int year   = day / 260;
    int iTmp   = day % 260;
    int period = iTmp % 13 + 1;
    char sDay[9] = {0};
    strcpy(sDay, tzolkinDay[iTmp%20]);
    
    char *ret = (char *)malloc(32);
    memset(ret, 0, 32);
    sprintf(ret, "%d %s %d", period, sDay, year);
    return ret;
}



int main()
{
    int iCount = 0;
    char sCount[4] = {0};
    gets(sCount); //从标准输入设备读字符串函数,以回车结束读取。
    iCount = atoi(sCount);
    
    char (*data)[32] = (char(*)[32])malloc(32*iCount);
    memset(data, 0, 32*iCount);
    for (int i=0; i<iCount; i++)
    {
        gets(data[i]);
    }
    
    printf("%d\n", iCount);
    for (int i=0; i<iCount; i++)
    {
        char *result = DayToTzolkin(HaabToDay(data[i]));
        
        if (result != NULL)
        {
           printf("%s\n", result);
           free(result);
           result = NULL;
        }
    }
    
    return 0;
}