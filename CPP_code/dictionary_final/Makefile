# This is a Makefile for the dictionary
# Typing 'make' will create the executable file
#
# define some Makefile variables for the compiler and compiler
# flags to use Makefile variables later in the Makefile: $()
CC = g++ -std=c++11
CFLAGS  = -c -Wall

# typing 'make' will invoke the first target entry in the file
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
default:	dictionary

# To create the executable file dictionary we need the object files
dictionary:	main.o Leaves.o Leaf.o decodingindexNode.o encodingindexNode.o Tree.o Node.o
	$(CC) main.o Leaves.o Leaf.o decodingindexNode.o encodingindexNode.o Tree.o Node.o -o dictionary

# To create the object file main.o, we need the source file main.cpp
main.o:	main.cpp
	$(CC) $(CFLAGS) main.cpp

# To create the object file Leaves.o need the source file Leaves,cpp
Leaves.o:	Leaves.cpp
	$(CC) $(CFLAGS)	Leaves.cpp

# To create the object file Leaf.o, we need the source file Leaf.cpp
Leaf.o:	Leaf.cpp
	$(CC) $(CFLAGS) Leaf.cpp

# To create the object file decodingindexNode.o need to the source file decodingindexNode.cpp
decodingindexNode.o:	decodingindexNode.cpp
	$(CC) $(CFLAGS) decodingindexNode.cpp

# To create the object file encodingindexNode.o need the source file encodingindexNode.cpp
encodingindexNode.o:	encodingindexNode.cpp
	$(CC) $(CFLAGS) encodingindexNode.cpp

# To create the object file Tree.o need the source file Tree.cpp
Tree.o:	Tree.cpp
	$(CC) $(CFLAGS) Tree.cpp

# To create the object file Node.o need the source file Node.cpp
Node.o:	Node.cpp
	$(CC) $(CFLAGS)	Node.cpp

# Clean all the object files
clean:
	rm -rf *o dictionary
