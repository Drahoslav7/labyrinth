FLAGS = -std=c++11 

LFLAGS = -l boost_system -l Qt5Core -l Qt5Gui
ifeq ($(OS),Windows_NT)
	LFLAGS += -lwsock32 -lws2_32
endif

FILES = shared/components.o shared/debug.o
CFILES = client/client.o
SFILES =  server/server.o server/player.o server/game.o

labyrinth: labyrinth2015-server labyrinth2015

labyrinth2015: $(CFILES) $(FILES)
	g++ $(FLAGS) -o $@ $^ $(LFLAGS) 

labyrinth2015-server: server/main.o $(SFILES) $(FILES)
	g++ $(FLAGS) -o $@ $^ $(LFLAGS) 


%.o: %.cpp %.h
	g++ $(FLAGS) -c $< -o $@

run:
	./labyrinth2015-server 1620

setdebug: 
	$(eval FLAGS += -D DEBUG=1)	

dd: setdebug labyrinth run 

d: labyrinth run 

test: tests/main.o $(SFILES)
	g++ $(FLAGS) -o $@ $^ $(LFLAGS)
	./test.exe

clean:
	rm labyrinth2015.exe labyrinth2015-server.exe labyrinth2015 labyrinth2015-server test test.exe server/*.o client/*.o shared/*.o tests/*.o

pack:
	#todo

.PHONY: setdebug labyrinth run
