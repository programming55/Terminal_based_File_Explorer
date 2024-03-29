#Trailblazer File Explorer
#By:
#  Ankit Pant
#  2018201035

CC = g++
CFLAGS = -Wall -std=c++14
DEPS = ui.h show_dir.h commandproc.h
OBJ = ui_implement.o show_dir.o commandproc.o main.o 
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^