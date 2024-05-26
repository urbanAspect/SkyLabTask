#include "consumer_task.h"



void notify_consumer_3d_fix_mode(const int currMode, int *prevMode) {
    if (currMode != prevMode) {
        if (currMode == 3) {
            printf("Entering 3d fix mode\n");
        } else if(currMode == 0) {
            printf("Exiting 3D fix mode.\n");
        }
        prevMode = currMode;
    }

}


void notify_consumer_position_time(Position position, Time time) {
    printf("\nFix taken at: %02d:%02d:%02d.%06.6f\n", time.hours, time.minutes, time.seconds, time.microseconds);
    printf("Latitude: %d degrees %.3f minutes %c\n", position.latitude.degrees, position.latitude.minutes, position.latitude.direction);
    printf("Longitude: %d degrees %.3f minutes %c\n", position.longitude.degrees, position.longitude.minutes, position.longitude.direction);
    printf("Altitude: %.3f m\n", position.altitude);
}
