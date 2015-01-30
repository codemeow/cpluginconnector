#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "plugtypes.h"

typedef struct
{
    Hash hash;
    ProcessHeader callback;
} HeaderProcessor;

typedef struct
{
    Hash hashheader;
    Hash hashvalue;
    ProcessValues callback;
} ValuesProcessor;

HeaderProcessor * hparr;
int               hplen;

ValuesProcessor * vparr;
int               vplen;

DataStorage * pluginsdata;
int           pluginsdatalen;

Hash currentheader;

uint32_t strhash(char * line)
{
    /* Fowler–Noll–Vo hash function */
    uint32_t hval = 0x811c9dc5;

    if (!(line))
        return hval;

    while (*line)
    {
        hval ^= (uint32_t)*line++;
        hval *= (uint32_t)0x01000193;
    }

    return hval;
}

void registerheader(Hash header, ProcessHeader callback)
{
    hparr = realloc(hparr, ++hplen * sizeof(HeaderProcessor));
    hparr[hplen - 1].hash     = header;
    hparr[hplen - 1].callback = callback;
}


void registervalues(Hash header, Hash values, ProcessValues callback)
{
    vparr = realloc(vparr, ++vplen * sizeof(ValuesProcessor));
    vparr[vplen - 1].hashheader = header;
    vparr[vplen - 1].hashvalue  = values;
    vparr[vplen - 1].callback   = callback;
}


void initregistrator()
{
    hparr = NULL;
    hplen = 0;
    vparr = NULL;
    vplen = 0;
    pluginsdata    = NULL;
    pluginsdatalen = 0;
    currentheader  = 0;
    currentdatapos = 0;
}

int isheader(char * line)
{
    return (line[0] == '[') && (line[strlen(line) - 1] == ']');
}

void processheader(Hash hash)
{
    currentheader = hash;

    int i;
    for (i = 0; i < hplen; i++)
    {
        if (hparr[i].hash == hash)
        {
            pluginsdata = realloc(pluginsdata, ++pluginsdatalen * sizeof(DataStorage));
            hparr[i].callback(&pluginsdata[pluginsdatalen - 1]);
            return;
        }
    }

    printf("Unregistered header: 0x%x\n", hash);
}

void processvalue(Hash hash)
{
    int i;
    for (i = 0; i < vplen; i++)
    {
        if ((vparr[i].hashheader == currentheader) &&
            (vparr[i].hashvalue  == hash))
        {
            vparr[i].callback(hash, &pluginsdata[pluginsdatalen - 1]);
            return;
        }
    }

    printf("Unregistered value: 0x%x\n", hash);
}

void processline(char * line)
{
    Hash hash = strhash(line);

    if (isheader(line)) processheader(hash);
                   else processvalue(hash);
}

void showstats()
{
    int i;
    for (i = 0; i < pluginsdatalen; i++)
    {
        pluginsdata[i].printer(pluginsdata[i].structdata);
    }
}
