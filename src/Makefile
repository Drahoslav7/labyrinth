FLAGS=-std=c++11 
LFLAGS=   -l boost_system
ifeq ($(OS),Windows_NT)
	LFLAGS+=  -lwsock32 -lws2_32
endif

labyrinth: labyrinth2015-server labyrinth2015

labyrinth2015: client.c
	g++ $(FLAGS) -o $@ $^ $(LFLAGS) 

labyrinth2015-server: server.c
	g++ $(FLAGS) -o $@ $^  $(DEFS) $(LFLAGS) 

run:
	./labyrinth2015-server 1620

d: labyrinth run
