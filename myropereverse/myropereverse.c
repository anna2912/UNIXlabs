#include <unistd.h>
#include <stdio.h>
//#include <stdlib.h>

#define SIZE 10
#define BUFSIZE 3

typedef struct node node;
struct node
{
    node* next;
    char* str;
    int length;
    int total;
};

/*void print_reverse (char* buffer, int len) {
	int i;
	for (i = len - 2; i >= 0; i--) {
		write(1, buffer+i, 1);
	}
	write(1, buffer+len-1, 1);
}*/

void add(node* rope, char* buffer, int start, int end) {

    int len = end - start + 1;
   // printf("add %d chars \n", len);
    while(1){
        rope->total += len;
        if(rope->next != 0)
            rope = rope->next;
        else
            break;
    }
    if(rope->str != 0) {
        rope->next = (node*)malloc(sizeof(node));
        rope = rope->next;
    }
    rope->next = 0;
    rope->length = len;
    rope->total = len;
    rope->str = (char*)malloc(len * sizeof(char));
    memcpy(rope->str, buffer + start, len);
    //printf("exit add\n");
}

void clear (node* rope){
    //printf("clear\n");
    if(rope->str != 0)
        free(rope->str);
    if(rope->next != 0){
        clear(rope->next);
    }
    free(rope);
    //printf("exit clear\n");
}

void print_reverse (node* rope){
    //printf("print_reverse\n");
    int i;
    if(rope->next != 0) {
        print_reverse(rope->next);
        i = rope->length - 1;
    }
    else{
        i = rope->length - 2;
    }
    for(i; i>=0; i--)
        write(1, rope->str + i, 1);
    //printf("exit print_reverse\n");
}

int main () {
    char buffer[BUFSIZE];
    int len, i;
	int discard_line = 0;
	int start = 0;
    int end = 0;

	node* rope = (node*)malloc(sizeof(node));
    rope->next = 0;
	rope->str = 0;
	rope->length = 0;
	rope->total = 0;
	
	while (1) {
		len = read (0, buffer, BUFSIZE);
        //printf("read %d chars\n", len);
		if(len!=0) {
            start = 0;
            end = 0;
            while(end != -1){
                end = -1;
                for(i = start; i < len; i++)
                    if(buffer[i] == '\n') {
                        end = i;
                        break;
                    }
                if(end == -1) {
                    if(!discard_line) {
                        if(rope->total + len - start > SIZE)
                            discard_line = 1;
                        else
                            add(rope, buffer, start, len -1);
                    }
                }
                else {
                    if(rope->total + end - start + 1 > SIZE)
                        discard_line = 1;

                    if(!discard_line) {
                        add(rope, buffer, start, end);
                        print_reverse(rope);
                        write(1, buffer+end, 1);
                    }

                    discard_line = 0;
                    clear(rope);
                    node* rope = (node*)malloc(sizeof(node));
                    rope->next = 0;
                    rope->str = 0;
                    rope->length = 0;
                    rope->total = 0;
                }
                start = i + 1;
                if(start>=len)
                    break;
            }
		}
		else {
			break;
		}
	}

    clear(rope);

	return 0;
}

