#include <stdlib.h>
#include <unistd.h>
#include "functions.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    struct TemperatureData *Data;
    char *FN = NULL;
    int OptRes = 0;
    int IsM = 0;
    int m = 0;
    int N;

    opterr = 0;
    while ((OptRes = getopt(argc, argv, "hf:m:")) != -1)
    {
        switch (OptRes)
        {
        case 'h':
            puts("This program is designed to display temperature statistics for the year.");
            puts("  Options:");
            puts("-f <Filename>: data file name (required option);");
            puts("-m <Month>: statistics for this month only;");
            puts("-h: display this information.");
            puts("");
            return 0;
        case 'f':
            FN = optarg;
            break;
        case 'm':
            IsM = 1;
            m = atoi(optarg);
            break;
        }
    }

    if (optind < argc)
    {
        fprintf(stderr, "ERROR: Invalid argument: %s\n", argv[optind]);
        return 1;
    }

    if (FN == NULL && !IsM)
    {
        fprintf(stderr, "ERROR: Data file name is missing!\n");
        return 1;
    }

    if (FN != NULL)
    
    {
        Data = LoadFile(FN, &N);
        if (!Data)
        {
            return 1;
        }

        if (!IsM)
        {
            printYearlyStats(Data, N);
        }
        else
        {
            if (m < 1 || m > 12)
            {
                fprintf(stderr, "ERROR: Invalid month number!\n");
                return 1;
            }
            printMonthlyStats(Data, N, m);
        }

        free(Data);
    }

    return 0;
}