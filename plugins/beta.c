#include <stdlib.h>
#include <stdio.h>
#include "beta.h"

#define HASH_BETA (0x11ebc4cf)

#define HASH_B (0xc70bfb85)
#define HASH_D (0xc10bf213)

void BetaSays(void *data);

typedef struct
{
    int b;
    int d;
} BetaStruct;

void initbeta()
{
    registerheader(HASH_BETA, BetaHeader);

    registervalues(HASH_BETA, HASH_B, BetaValues);
    registervalues(HASH_BETA, HASH_D, BetaValues);
}

errorcode BetaHeader(DataStorage * data)
{
    data->printer    = BetaSays;
    data->structsize = sizeof(BetaStruct);

    BetaStruct * structdata = malloc(sizeof(BetaStruct));
    data->structdata = (void *)structdata;

    structdata->b = 0;
    structdata->d = 0;

    return 0;
}

errorcode BetaValues(Hash value, DataStorage * data)
{
    switch (value)
    {
    case HASH_B: ((BetaStruct *)(data->structdata))->b += 1; break;
    case HASH_D: ((BetaStruct *)(data->structdata))->d += 1; break;
    default :
        return 1;
    }

    return 0;
}

void BetaSays(void * data)
{
    printf("Beta.b = %d\n", ((BetaStruct *)(data))->b);
    printf("Beta.d = %d\n", ((BetaStruct *)(data))->d);
}
