#ifndef TEMP_API_H
#define TEMP_API_H

struct TemperatureData
{
int year;
int month;
int day;
int hour;
int minute;
int temperature;
};

struct Stat
{
int count;
int sum;
int minTemp;
int maxTemp;
};

int CheckDate(int, int, int);
int CheckTime(int, int);
struct TemperatureData* LoadFile(const char*, int*);
void printMonthlyStats(const struct TemperatureData*, int, int);
void printYearlyStats(const struct TemperatureData*, int);

#endif
