#include <stdio.h>

#include "plugtypes.h"

#include "plugins/alpha.h"
#include "plugins/beta.h"

int main(void)
{
    initregistrator();

    initalpha();
    initbeta();

    processline("[Alpha]");
    processline("A");
    processline("A");
    processline("A");
    processline("B");
    processline("C");
    processline("C");
    processline("[Beta]");
    processline("B");
    processline("B");
    processline("B");
    processline("B");
    processline("D");
    processline("E");

    showstats();

    return 0;
}

