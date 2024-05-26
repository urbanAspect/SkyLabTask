#include "gnss_simulator.h"
#include "consumer_task.h"



void parse();
int find_sentence(const char *message, char *sentence, char *sentenceName);
char *extract_value(const char *sentence, char ch, int k, int n);
int checksum(const char *sentence);