FLAGS = -std=c++11 

LFLAGS = -l boost_system -l Qt5Core -l Qt5Gui
ifeq ($(OS),Windows_NT)
	LFLAGS += -lwsock32 -lws2_32
endif

FILES = components.cpp debug.cpp


labyrinth: labyrinth2015-server labyrinth2015

labyrinth2015: client/client.cpp $(FILES)
	g++ $(FLAGS) -o $@ $^ $(LFLAGS) 

labyrinth2015-server: server/main.cpp server/server.cpp $(FILES)
	g++ $(FLAGS) -o $@ $^ $(LFLAGS) 

run:
	./labyrinth2015-server 1620

setdebug: 
	$(eval FLAGS += -D DEBUG=1)	

dd: setdebug labyrinth run 

d: labyrinth run 

clean:
	rm labyrinth2015.exe labyrinth2015-server.exe labyrinth2015 labyrinth2015-server

.PHONY: setdebug labyrinth run
