#ifndef PLUGTYPES_H
#define PLUGTYPES_H

#include <stdint.h>

typedef int errorcode;
typedef uint32_t Hash;

/*                          data */
typedef void (*SomeoneSays)(void *);

typedef struct
{
    SomeoneSays printer;
    int         structsize;
    void *      structdata;
} DataStorage;

/*                                 string  data        */
typedef errorcode (*ProcessHeader)(        DataStorage *);
typedef errorcode (*ProcessValues)(Hash,   DataStorage *);

uint32_t strhash(char * line);

void registerheader(Hash header,              ProcessHeader callback);
void registervalues(Hash header, Hash values, ProcessValues callback);

void initregistrator();

void processline(char * line);
void showstats();

#endif // PLUGTYPES_H
