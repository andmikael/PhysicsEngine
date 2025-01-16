#pragma once

#include <ctime>

// static class to fetch dt
class Time {
    public:
        static float getTime() {
            return(float)clock()/CLOCKS_PER_SEC;
        }
};