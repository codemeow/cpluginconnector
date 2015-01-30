#include <stdlib.h>
#include <stdio.h>
#include "alpha.h"

#define HASH_ALPHA (0x178f8a8d)

#define HASH_A (0xc40bf6cc)
#define HASH_B (0xc70bfb85)
#define HASH_C (0xc60bf9f2)

void AlphaSays(void *data);

typedef struct
{
    int a;
    int b;
    int c;
} AlphaStruct;

void initalpha()
{
    registerheader(HASH_ALPHA, AlphaHeader);

    registervalues(HASH_ALPHA, HASH_A, AlphaValues);
    registervalues(HASH_ALPHA, HASH_B, AlphaValues);
    registervalues(HASH_ALPHA, HASH_C, AlphaValues);
}

errorcode AlphaHeader(DataStorage * data)
{
    data->printer    = AlphaSays;
    data->structsize = sizeof(AlphaStruct);

    AlphaStruct * structdata = malloc(sizeof(AlphaStruct));
    data->structdata = (void *)structdata;

    structdata->a = 0;
    structdata->b = 0;
    structdata->c = 0;

    return 0;
}

errorcode AlphaValues(Hash value, DataStorage *data)
{
    switch (value)
    {
    case HASH_A: ((AlphaStruct *)(data->structdata))->a += 1; break;
    case HASH_B: ((AlphaStruct *)(data->structdata))->b += 1; break;
    case HASH_C: ((AlphaStruct *)(data->structdata))->c += 1; break;
    default :
        return 1;
    }

    return 0;
}

void AlphaSays(void * data)
{
    printf("Alpha.a = %d\n", ((AlphaStruct *)(data))->a);
    printf("Alpha.b = %d\n", ((AlphaStruct *)(data))->b);
    printf("Alpha.c = %d\n", ((AlphaStruct *)(data))->c);
}
