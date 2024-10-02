//
// Created by muntr on 21. 9. 2024.
//

#ifndef MYGLFWPROJECT_TIME_H
#define MYGLFWPROJECT_TIME_H


#include <time.h>

#define NS_PER_SECOND (1000000000)
#define NS_PER_MS (1000000)

static inline long long NOW() {
    struct timespec ts;
    timespec_get(&ts, 1);
    return (ts.tv_sec * NS_PER_SECOND) + ts.tv_nsec;
}

#endif //MYGLFWPROJECT_TIME_H
