CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -MMD -Werror=vla
EXEC = chess
OBJECTS = checkandcheckmate.o main.o observer.o chess.o grid.o bishop.o king.o knight.o humanmove.o pawn.o rook.o queen.o player.o textdisplay.o GraphicsDisplay.o window.o getpiece.o castle.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

