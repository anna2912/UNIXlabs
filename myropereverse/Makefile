CC              = gcc
CFLAGS          = -std=c99
SOURCES         = myropereverse.c
OBJECTS         = $(SOURCES:.c=.o)
PRODUCT_NAME    = myropereverse

all: $(PRODUCT_NAME)

rebuild: clean all

$(PRODUCT_NAME): $(OBJECTS) 
	$(CC) -o $(PRODUCT_NAME) $(OBJECTS)
	rm -rf $(OBJECTS)

$(OBJECTS):
	$(CC) -c $(SOURCES) $(CFLAGS) 

clean:
	rm -rf $(OBJECTS) $(PRODUCT_NAME)

