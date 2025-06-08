CC = gcc
OFLAGS = -o

FLEX = flex
FLEXFLAGS = --outfile=

BISON = bison
BISONFLAGS = --yacc --defines
BISONOUT = --output=

RM = rm -f

all: calc

calc: lexer.c parser.c  stackFrames.c symbolTable.c phase3.c phase4.c 
	$(CC) $(OFLAGS) calc lexer.c parser.c stackFrames.c symbolTable.c phase3.c phase4.c

lexer.c: lexer.l
	$(FLEX) $(FLEXFLAGS)lexer.c lexer.l

parser.c: parser.y
	$(BISON) $(BISONFLAGS) $(BISONOUT)parser.c parser.y -v


clean:
	$(RM) calc lexer.c parser.c parser.h parser.output file.bin output.txt

