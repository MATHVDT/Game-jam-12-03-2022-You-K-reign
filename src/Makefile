#SRC=main.cpp obj.cpp
SRC=$(wildcard *.cpp)  
EXE=yourKreign.exe


CXXFLAGS+=-Wall -Wextra -MMD -g -O2 -fdiagnostics-color=auto
LDFLAGS=  -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

OBJ=$(addprefix build/,$(SRC:.cpp=.o))
DEP=$(addprefix build/,$(SRC:.cpp=.d))

all: $(OBJ)
	$(CXX) -o $(EXE) $^ $(LDFLAGS)

build/%.o: %.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf build core *.gch

-include $(DEP)
