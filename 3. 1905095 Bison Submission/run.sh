bison -d -y -v 1905095.y
g++ -w -c -o y.o y.tab.c
flex 1905095.l
g++ -w -c -o l.o lex.yy.c
g++ -o bison y.o l.o
./bison 1905095_input.txt