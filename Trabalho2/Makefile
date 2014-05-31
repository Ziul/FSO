
XX = gcc

SRC = 	convert.c	\
		main.c

OBJS = ${SRC:.cpp=.o}

CFLAGS =-I./  -g3 -ansi -pedantic -lpthread

OUTPUT = Trabalho

.SUFFIXES:.cpp.o

.cpp.o:
	echo -n "compiling... " $<
	$(XX) $< -c -g $(CFLAGS) 
	echo  " Done"

all: $(OBJS)
	$(XX) $(OBJS) -o $(OUTPUT) $(CFLAGS) 


clean:
	echo "Cleaning all..."
	rm -rfv $(OUTPUT) *.o *.d *.a

.SILENT: