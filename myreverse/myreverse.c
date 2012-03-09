#include <unistd.h>

#define SIZE 5

void print_reverse (char* buffer, int len) {
	int i;
	for (i = len - 2; i >= 0; i--) {
		write(1, buffer+i, 1);
	}
	write(1, buffer+len-1, 1);
}

int main () {

	char buffer[SIZE];
	int len;

	len = read(0, buffer, SIZE);

	while (len > 1) {
		if (len < SIZE || buffer[SIZE-1] == '\n') {
			print_reverse(buffer, len);
		}
		else {
			while(1) {
				len = read(0, buffer, SIZE);
				if(buffer[len-1] == '\n')
					break;
			}
		}
		len = read(0, buffer, SIZE);
	}

	return 0;
}