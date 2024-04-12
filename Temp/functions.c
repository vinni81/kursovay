#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

const char *Months[12] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};
int CheckDate(int Year, int Month, int Day)
{
int Days[12]={31,28,31,30,31,30,31,31,30,31,30,31};

if(Year<0 || Month<1 || Month>12 || Day<1) return 1;
if((Year%400==0) || (Year%4==0 && Year%100!=0)) Days[1]++;
return Day<=Days[Month-1] ? 0 : 1;
}


int CheckTime(int Hours, int Minutes)
{
return Hours>=0 && Hours<24 && Minutes>=0 && Minutes<60 ? 0 : 1;
}


struct TemperatureData* LoadFile(const char* FileName, int* size)
{
    struct TemperatureData *data = NULL;
    struct TemperatureData tmp;
    FILE *F = fopen(FileName, "r");
    char Buf[40];
    int N = 0;

    *size = 0;
    if (!F)
    {
        puts("ERROR: Data file not found!");
        return NULL;
    }
    while (1)
    {
        fgets(Buf, 40, F);
        N++;
        if (feof(F))
            break;
        if (sscanf(Buf, "%d;%d;%d;%d;%d;%d", &tmp.year, &tmp.month, &tmp.day, &tmp.hour, &tmp.minute, &tmp.temperature) != 6)
        {
            printf("ERROR: Invalid data format at line %d\n", N);
            continue;
        }
        if (CheckDate(tmp.year, tmp.month, tmp.day))
        {
            printf("ERROR: Invalid date at line %d\n", N);
            continue;
        }
        if (CheckTime(tmp.hour, tmp.minute))
        {
            printf("ERROR: Invalid time at line %d\n", N);
            continue;
        }
        if (tmp.temperature < -99 || tmp.temperature > 99)
        {
            printf("ERROR: Invalid temperature at line %d\n", N);
            continue;
        }
        (*size)++;
        data = (struct TemperatureData*)realloc(data, (*size) * sizeof(struct TemperatureData));
        data[(*size) - 1] = tmp;
    }
    fclose(F);
    return data;
}


void printMonthlyStats(const struct TemperatureData* data, int size, int month)
{
struct Stat St;
int i;

St.count=0;
St.sum=0;
St.minTemp=99;
St.maxTemp=-99;
for(i=0;i<size;i++)
 if(data[i].month==month)
  {
  St.count++;
  St.sum+=data[i].temperature;
  if(data[i].temperature<St.minTemp)
   St.minTemp=data[i].temperature;
  if(data[i].temperature>St.maxTemp)
   St.maxTemp=data[i].temperature;
  }
puts("      MONTH TEMPERATURE STATISTICS");
puts("-----------------------------------------");
puts("|  Month   | Avegare | Minmum | Maximum |");
puts("-----------------------------------------");
printf("|%-10s|",Months[month-1]);
if(St.count)
 printf("%7.2lf  |%5d   |%6d   |\n",(double)(St.sum)/St.count,St.minTemp,St.maxTemp);
else puts(" NO DATA |NO DATA | NO DATA |");
puts("-----------------------------------------");
}

void printYearlyStats(const struct TemperatureData* data, int size)
{
struct Stat Year[13];
int i;

for(i=0;i<13;i++)
 {
 Year[i].sum=0;
 Year[i].count=0;
 Year[i].minTemp=99;
 Year[i].maxTemp=-99;
 }
for(i=0;i<size;i++)
 {
 Year[0].sum+=data[i].temperature;
 Year[0].count++;
 Year[data[i].month].sum+=data[i].temperature;
 Year[data[i].month].count++;
 if(data[i].temperature<Year[0].minTemp)
  Year[0].minTemp=data[i].temperature;
 if(data[i].temperature>Year[0].maxTemp)
  Year[0].maxTemp=data[i].temperature;
 if(data[i].temperature<Year[data[i].month].minTemp)
  Year[data[i].month].minTemp=data[i].temperature;
 if(data[i].temperature>Year[data[i].month].maxTemp)
  Year[data[i].month].maxTemp=data[i].temperature;
 }
puts("      YEAR TEMPERATURE STATISTICS");
puts("-----------------------------------------");
puts("|  Month   | Avegare | Minmum | Maximum |");
puts("-----------------------------------------");
for(i=1;i<=12;i++)
 {
 printf("|%-10s|",Months[i-1]);
 if(Year[i].count)
  printf("%7.2lf  |%5d   |%6d   |\n",(double)(Year[i].sum)/Year[i].count,Year[i].minTemp,Year[i].maxTemp);
 else puts(" NO DATA |NO DATA | NO DATA |");
 }
puts("-----------------------------------------");
printf("|%7d   |",data[0].year);
if(Year[0].count)
 printf("%7.2lf  |%5d   |%6d   |\n",(double)(Year[0].sum)/Year[0].count,Year[0].minTemp,Year[0].maxTemp);
else puts(" NO DATA |NO DATA | NO DATA |");
puts("-----------------------------------------");
}
