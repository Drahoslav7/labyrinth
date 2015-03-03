FLAGS=-std=c++11 
LFLAGS=  -lwsock32 -lws2_32 -l boost_system

labyrinth: labyrinth2015-server labyrinth2015

labyrinth2015: client.c
	g++ $(FLAGS) -o $@ $^ $(LFLAGS) 

labyrinth2015-server: server.c
	g++ $(FLAGS) -o $@ $^  $(DEFS) $(LFLAGS) 

run:
	./labyrinth2015-server 1620

d: labyrinth run
