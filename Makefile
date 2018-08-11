CXXC=g++ -fsanitize=address
CXXFLAGS= -std=c++14 -W -Wall -Wextra -Werror -Wfatal-errors #-Weffc++
LDFLAGS=
EXEC=main
SRC= $(wildcard *.cpp)
OBJ=$(SRC:.cpp=.oo)

all: $(EXEC)

main: $(OBJ)
	$(CXXC) -o $@ $^ $(LDFLAGS)

%.oo: %.cpp
	$(CXXC) -o $@ -c $< $(CXXFLAGS)

.PHONY: clean


clean: 
	rm -rf *.oo $(EXEC)
