TARGET=analyseData
CC=g++
FLAGS=-std=c++23
OBJECTS=analyseData.o customFunctions.o

# Default target is the executable
all: ${TARGET}

# Link the executable
${TARGET}: ${OBJECTS}
	@echo "Linking..."
	${CC} ${FLAGS} ${OBJECTS} -o ${TARGET}

# Compile object files. Using $@ and $< avoids repetition
%.o: %.cpp %.hh
	${CC} ${FLAGS} -c $< -o $@

# Clean object files and backups
clean:
	@rm -f *.o *~

# Clean everything including the executable
cleantarget: clean
	@rm -f ${TARGET}
