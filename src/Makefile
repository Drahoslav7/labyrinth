# Projekt ICP 
# Labyrint
# 
# Drahoslav Bednář - xbedna55
# Jiří Kunčák -xkunca55
# 
# 2014/2015
#

FLAGS = -std=c++11 
# -I include/

LFLAGS = -L lib/ -l boost_system 
# -l Qt5Core -l Qt5Gui
ifeq ($(OS),Windows_NT)
	LFLAGS += -l boost_thread -lwsock32 -lws2_32
else
	LFLAGS += -l pthread 
endif

FILES = shared/tools.o shared/components.o shared/debug.o shared/connection.o
CFILES = client/client.o
SFILES = server/server.o server/player.o server/game.o

labyrinth: labyrinth2015-server labyrinth2015-cli labyrinth2015

labyrinth2015: client/main.o $(CFILES) $(FILES)
	# GUI NOT IMPLEMENTED
	# g++ $(FLAGS) -o $@ $^ $(LFLAGS) 

labyrinth2015-cli: client/main.o $(CFILES) $(FILES)
	g++ $(FLAGS) -o $@ $^ $(LFLAGS) 

labyrinth2015-server: server/main.o $(SFILES) $(FILES)
	g++ $(FLAGS) -o $@ $^ $(LFLAGS)
	-mkdir saves


%.o: %.cpp %.h
	g++ $(FLAGS) -c $< -o $@

%.o: %.cpp
	g++ $(FLAGS) -c $< -o $@

run:
	./labyrinth2015-server 1620

runclient:
	./labyrinth2015 localhost 1620	

setdebug: 
	$(eval FLAGS += -D DEBUG=1)

dd: clean setdebug labyrinth run 

d: labyrinth run 

test: tests/main.o $(SFILES) $(FILES) $(CFILES)
	g++ $(FLAGS) -o $@ $^ $(LFLAGS)
	./test.exe

clean:
	-rm labyrinth*.exe  labyrinth* test test.exe server/*.o client/*.o shared/*.o tests/*.o

.PHONY: setdebug labyrinth run
