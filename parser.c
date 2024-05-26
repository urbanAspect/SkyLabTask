#include "parser.h"


void parse() {
    char receivedMessage[ MAX_MESSAGE_SIZE ] = {0};
    char NMEAsentence[ 128 ] = {0};

    // Var to store 3D fix data
    Position position;
    Time time;
    // Store if we are in 3D fix mode or not
    int currMode, prevMode = -1;

    while(1) {
        xStreamBufferReceive(gnssStreamBuffer,
                             (void *)receivedMessage,
                             MAX_MESSAGE_SIZE,
                             NULL);
        
        // If satelite status sentence is available
        if (find_sentence(receivedMessage, NMEAsentence, "$GPGSA") == 1) {
            // Vertify that all data in sentence was received correctly 
            if (checksum(NMEAsentence) == 1){
                // Check if 3D fix is available
                currMode = atoi(extract_value(NMEAsentence, ',', 2, 1));
                notify_consumer_3d_fix_mode(currMode, prevMode);
                if (currMode == 3) {
                    // Find Global Positioning System Fix Data sentence

                    if (find_sentence(receivedMessage, NMEAsentence, "$GPGGA") == 1) {            
                        // Vertify that all data in sentence was received correctly 
                        if (checksum(NMEAsentence) == 1){
                            // extract data (cell index {GP... is cell 0})
                            // time (1)
                            sscanf(extract_value(NMEAsentence, ',', 1, 1), "%2d%2d%2d.%d", &time.hours, &time.minutes, &time.seconds, &time.microseconds);
                            // lat (2, 3)
                            sscanf(extract_value(NMEAsentence, ',', 2, 2), "%2d%f,%c",  &position.latitude.degrees, &position.latitude.minutes, &position.latitude.direction);
                            // lon (3, 4)
                            sscanf(extract_value(NMEAsentence, ',', 3, 2), "%3d%f,%c",  &position.longitude.degrees, &position.longitude.minutes, &position.longitude.direction);
                            // alt (8) in meters
                            sscanf(extract_value(NMEAsentence, ',', 8, 1), "%f",  &position.altitude);

                            // pass data to consumer_task
                            notify_consumer_position_time(position, time);

                        } else { printf("Checksum for    $GPGGA    failed.\n"); continue; }
                    } else { printf("No $GPGGA message was found.\n"); continue; }
                } else { continue; }  
            } else { printf("Checksum for    $GPGSA    failed.\n"); continue; }            
        } else { printf("No    $GPGSA    message was found.\n"); continue; }
    } 
    
    
    
}

//                              where to copy to
//               where to copy from          what should the sentence start with 
int find_sentence(const char *message, char *sentence, char *sentenceName) {
    // Find sentence by its name e.g. $GPGLL
    char *start = strstr(message, sentenceName);
    char *end = strstr(start, "\n");

    if (start == NULL) {
        // If message was not found return null
        return 0;
    } else {
        // Copy sentence to *sentence
        memcpy(sentence, message, end - start);
        sentence[end - start + 1] = '\0';
        return 1;
    }
}

// Returns extracted value
// Used usually to extract coma separated values or values up to the end of line
// Where to extract from, separation character, 
// (k) number of occurances of separation char infront of the data we want to extract
// (n) number of cells we want to extract at once
char *extract_value(const char *sentence, char ch, int k, int n) {
    int count = 0;
    int start = -1, end = -1;
    for (int i = 0; sentence[i] != '\0'; i++) {
        if (sentence[i] == ch) {
            count++;
            if (count == k) {
                start = i;
            } else if (count == (k + n)) {
                end = i;
                break;
            }
        } else if (sentence[i] == '\n') {
            end = i - 1;
            break;
        }
    }
    // If occurence not found
    if (start == -1 || end == -1 || (end - start) == 0) { return NULL; }
    
    // Allocate space for value and reutrn it
    char *value = malloc(end - start + 1);
    memcpy(value, sentence + start, end - start);
    value[end - start] = '\0';

    return value; 
}

int checksum(const char *sentence) {
    int sum = 0;
    int i = 0;

    // Extract 0x checksum from message and convert to int
    int checksum = (int)strtol(extract_value(sentence, '*', 1, 1), NULL, 16);
    // Skip start of the message
    while (sentence[i] != '$' && sentence[i] != '\0') {
        i++;
    }
    // No message was found (missing $ as start of message)
    if (sentence[i] == '\0') { return NULL; }

    // Skip $
    i++; 
    // Perform checksum
    for (; sentence[i] != '*'; i++) {
        sum ^= (unsigned char)sentence[i];
    }
    // No end of message (*) was found
    if (sentence[i] == '\0') { return NULL; }
    
    // Valid checksum return TRUE
    if (sum == checksum) { return 1; }
    else{ return NULL; }
}