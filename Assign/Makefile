

CC=gcc

CFLAGS=-ansi -pedantic -lm -W -Wall -O2 -g -c 


SOURCE1 = htable-main.c mylib.c htable.c


SOURCE2 = tree-main.c mylib.c tree.c   
	
OBJ1 = mylib.o htable.o htable-main.o  
OBJ2 = mylib.o tree.o tree-main.o

TARGET1= htable-main
TARGET2= tree-main
$(TARGET1): $(SOURCE1)
	$(CC) $(SOURCE1)  $(CFLAGS) 
	$(CC) -o $(TARGET1) $(OBJ1)
	chmod +x $(TARGET1)

$(TARGET2): $(SOURCE2)
	$(CC) $(SOURCE2) $(CFLAGS)
	$(CC) -o $(TARGET2) $(OBJ2)
	chmod +x $(TARGET2) 


clean:
	rm -rf *.o 
	rm -rf tree-main
	rm -rf htable-main
