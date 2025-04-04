#ifndef _PROJECT__H_
#define _PROJECT__H_
#define CLAMP_TO_ZERO(x) ((x) < 0 ? 0 : (x))

//name and next pointer need to be dynamically allocated
typedef struct Country{
    char* name;  //can be arbitrary length
    int gold;
    int silver;
    int bronze;
    struct Country* next;
} Country;


#endif //! _PROJECT__H_