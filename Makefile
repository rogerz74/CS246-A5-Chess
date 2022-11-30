XX = g++
CXXFLAGS = -std=c++14 -Wall -Werror -Wextra -g -MMD
EXEC = chess
OBJECTS = main.o chessGame.o subject.o observer.o human.o computer.o box.o piece.o bishop.o queen.o knight.o rook.o record.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
		${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
		rm ${OBJECTS} ${EXEC} ${DEPENDS}

