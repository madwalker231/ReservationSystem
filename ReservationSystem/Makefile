.POSIX:

C++ := /usr/bin/c++
CFLAGS := -c -g
DOS2UNIX := /usr/bin/dos2unix

BASE_SRC = Car.cpp \
	Pump.cpp \
	Station.cpp
HDRS = ${BASE_SRC:.cpp=.h}
SRC = ${BASE_SRC} \
	main.cpp
OBJ = ${SRC:.cpp=.o}
NAME = ReservationSystem

all: ${NAME}

${NAME}: ${OBJ}
	${C++} -o $@ ${OBJ}

Car.o: Car.cpp Car.h
Pump.o: Pump.cpp Pump.h
Station.o: Station.cpp Station.h

.cpp.o:
	${DOS2UNIX} $<
	${C++} ${CFLAGS} -o $@ $<

clean:
	rm -f ${OBJ} ${NAME}
