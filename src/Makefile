SUB_DIR := core global http route example

export CC INCLUDE_DIR OBJ_DIR BIN_DIR TARGET STD SUB_DIR LD_FLAGS

.PHONY: all $(SUB_DIR)

all: build $(SUB_DIR)

$(SUB_DIR):
	$(MAKE) -C $@

# 编译main
main := main.cpp
OBJ := $(patsubst %.cpp,%.o,$(main))

build: $(OBJ)

$(OBJ): %.o : %.cpp
	$(CC) -std=$(STD) ${LD_FLAGS} $(INCLUDE_DIR) -c $^ -o $(OBJ_DIR)/$@
