#include<stdio.h>

typedef struct {
    int hours;
    int minutes;
    int seconds;
    int microseconds;
} Time;

typedef struct {
    int degrees;
    float minutes;
    char direction;
} GeoCoord;

typedef struct {
    GeoCoord latitude;
    GeoCoord longitude;
    float altitude;
} Position;

void notify_consumer_3d_fix_mode(const int currMode, int *prevMode);
void notify_consumer_position_time(Position position, Time time);
