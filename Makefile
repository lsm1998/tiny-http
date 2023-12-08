CC := gcc

INCLUDE_DIR := -I ../include/

OBJ_DIR := $(shell pwd)/obj
BIN_DIR := $(shell pwd)/bin
SUB_DIR := main fun global obj

TARGET := main_exec

# 设置变量导出为全局变量，子Makefile可以访问
export CC INCLUDE_DIR OBJ_DIR BIN_DIR SUB_DIR TARGET

all: $(SUB_DIR)

$(SUB_DIR): MK_BIN
	make -C $@

MK_BIN:
	mkdir -p ./bin

install:
	sudo cp $(BIN_DIR)/$(TARGET) /usr/local/bin

uninstall:
	sudo rm -rf /usr/local/bin/$(TARGET)

clean:
	rm -rf ./bin ./obj/*.o