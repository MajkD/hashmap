g++ -c -o obj/main.o main.cpp
g++ -c -o obj/hashmap.o lib/hashmap/hashmap.cpp

before=$(stat bin/main)
g++ -W -Wall -pedantic -g -rdynamic -o bin/main obj/hashmap.o obj/main.o
after=$(stat bin/main)
# Only execute main if it was written to
if [ "$before" != "$after" ];
then
  ./bin/main
fi