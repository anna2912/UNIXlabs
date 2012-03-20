#include <unistd.h>
#include <stdio.h>
//#include <stdlib.h>

#define SIZE 10

void print_reverse (char* buffer, int len) {
	int i;
	for (i = len - 2; i >= 0; i--) {
		write(1, buffer+i, 1);
	}
	write(1, buffer+len-1, 1);
}

int main () {

	char buffer[SIZE];
	int len, i;
	int offset = 0;
	int discard_line = 0;
	int f = 0;
	int start;

	while (1) {
		len = read (0, buffer + offset, SIZE - offset);

		if(len!=0) {
			f = 0;
			start = 0;
			i = offset;
			while(i < offset + len) {
				if(buffer[i] == '\n') {
					if(!discard_line) {
						print_reverse(buffer + start, i + 1 - start);
					}
					start = i + 1;
					discard_line = 0;
					f = 1;
				}
				i++;
			}
			if(!f && i == SIZE) {
				discard_line = 1;
			}
			memmove(buffer, buffer + start, len + offset - start);
			offset = (len + offset - start) % SIZE;
		}
	}

	return 0;
}
