#include "main.h"


uint16_t temp_adc[TEMP_LEVELS] = { \
    0,			\ //0 OFF
    180,		\ //1 200C
    220,		\ //2 250C
    260,		\ //3 300C
    300,		\ //4 350C
    340,		\ //5 400C
    390,		\ //6 450C
    450			\ //7 480C (MAX)
};

