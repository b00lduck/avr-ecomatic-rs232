#include "stdinc.h"

unsigned char parseCommand(char* line, char* cmd) {
	char* oldline = line;
	unsigned char len = strlen(line);

	while((len) && (*line != 32)) { // read first datafield
		if ((*line != 10) && (*line != 13)) {
			*(cmd++) = *line;
		}
		line++;
		len--;
	}

	line = oldline;

	return SUCCESS;
}