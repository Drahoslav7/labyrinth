# Projekt ICP 
# Labyrint
# 
# Drahoslav Bednář - xbedna55
# Jiří Kunčák -xkunca55
# 
# 2014/2015
#
#
all:
	make -C src/

run:
	make run -C src/

d:
	make d -C src/	

dd:
	make dd -C src/

test:
	make test -C src/

doc: doxygen

doxygen: 
	doxygen src/doxyconfig

pack: clean
	# tar -cvzf xbedna55-xkunca07.zip *
	-7z a xbedna55-xkunca07.zip -r *
	-zip -r xbedna55-xkunca07.zip *

clean:
	-rm -r doc/*
	-rm *.zip
	make clean -C src/