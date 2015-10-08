cc=gcc
clean:  
	rm parser.lex  
	rm parser.lex.c  
	rm parser.tab.h  
	rm parser.tab.c

my: parser.y parser.l
	bison -d parser.y  
	flex -o parser.lex.c parser.l  
