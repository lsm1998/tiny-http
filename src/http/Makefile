SRC := $(wildcard *.cpp)

OBJ := $(patsubst %.cpp,%.o,$(SRC))

all: $(OBJ)

$(OBJ): %.o : %.cpp
	$(CC) -std=$(STD) ${LD_FLAGS} $(INCLUDE_DIR) -c $^ -o $(OBJ_DIR)/$@
