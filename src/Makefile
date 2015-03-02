OPTS=-std=c++11 -I.
LIBS=-L$(CURDIR)/stage/lib/ -lboost_system

labyrinth: labyrinth2015-server labyrinth2015

labyrinth2015: client.c
	g++ $(OPTS) $(LIBS) -o $@ $^ 	

labyrinth2015-server: server.c
	g++ $(OPTS) $(LIBS) -o $@ $^ 

run:
	./labyrinth2015-server 1620

d: labyrinth run
