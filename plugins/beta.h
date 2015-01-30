#ifndef BETA_H
#define BETA_H

#include "plugtypes.h"

void initbeta();

errorcode BetaHeader(DataStorage * data);
errorcode BetaValues(Hash value, DataStorage * data);

#endif // BETA_H
