#ifndef _PROJECT__H_
#define _PROJECT__H_

typedef struct Country{
    char* name;  //can be arbitrary length
    unsigned int gold;
    unsigned int silver;
    unsigned int bronze;
    struct Country* next;
} Country;


#endif //! _PROJECT__H_