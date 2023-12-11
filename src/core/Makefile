SRC := $(wildcard *.cpp)

OBJ := $(patsubst %.cpp,%.o,$(SRC))

all: $(OBJ)

$(OBJ): %.o : %.cpp
	$(CC) -std=$(STD) $(INCLUDE_DIR) -c $^ -o $(OBJ_DIR)/$@