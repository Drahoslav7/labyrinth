

labyrinth: labyrinth2015-server labyrinth2015

labyrinth2015: client.c
	g++ -std=c++11 -o $@ $^	

labyrinth2015-server: server.c
	g++ -std=c++11 -o $@ $^

run:
	labyrinth2015-server

d: labyrinth run
