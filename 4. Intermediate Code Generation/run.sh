bison -d -y -v Parser.y
g++ -w -c -o y.o y.tab.c
flex Scanner.l
g++ -w -c -o l.o lex.yy.c
g++ -o bison y.o l.o
./bison 1905095_input.c