# ### Makefile.mk Documentation
# EXE =space
# CC = g++ -g 
# LIBS=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system 
# #DOXYGEN = doxygen
# PROGRAM = space
# CFLAGS =-std=c++14 -o $(EXE) 
# CFILES = SpaceInvaders.cpp #player.cpp lives.cpp enemyFly.cpp enemyBullets.cpp enemy.cpp bullets.cpp block.cpp
# HFILES = #player.h lives.h enemyFly.h enemyBullets.h enemy.h bullets.h block.h

# # working more advanced
# ALL:$(PROGRAM)

# #Rule for linking
# $(PROGRAM):$(CFILES) $(HFILES)
# 	$(CC) $(CFLAGS) *.cpp -o $(EXE)  $(LIBS) $(DEBUGFLAGS)
# 	$(DOXYGEN) Doxyfile

# DEBUG: DEBUGFLAGS = -g -O0
# DEBUG: ALL

# CLEAN:
# 	rm -f *.o
# .PHONY: all clean


LIBS=-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system 

all: run

run:space
	./space


SpaceInvaders.o: SpaceInvaders.cpp
	g++ -std=c++11 -c "SpaceInvaders.cpp" -o SpaceInvaders.o 
	
enemy.o: enemy.cpp
	g++ -std=c++11 -c "enemy.cpp" -o enemy.o 

space: SpaceInvaders.o player.o lives.o invaders.o  enemyFly.o enemyBullets.o enemy.o bullets.o block.o
	@echo "** Building the game Space Invagers"
	g++ -o space SpaceInvaders.o player.o lives.o invaders.o  enemyFly.o enemyBullets.o enemy.o bullets.o block.o $(LIBS) 

clean:
	@echo "** Removing object files and executable..."
	rm -f *.o

.PHONY: all clean
