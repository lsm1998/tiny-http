CC := g++

INCLUDE_DIR := -I $(shell pwd)/include/

OBJ_DIR := $(shell pwd)/obj
BIN_DIR := $(shell pwd)/bin
LD_FLAGS := -pthread

STD := c++17

TARGET := tiny_http

SUBDIRS := src obj

# 设置变量导出为全局变量，子Makefile可以访问
export CC INCLUDE_DIR OBJ_DIR BIN_DIR TARGET STD LD_FLAGS

all: $(SUBDIRS)

$(SUBDIRS): MK_BIN
	$(MAKE) -C $@

MK_BIN:
	mkdir -p ./bin

install:
	sudo cp $(BIN_DIR)/$(TARGET) /usr/local/bin

uninstall:
	sudo rm -rf /usr/local/bin/$(TARGET)

clean:
	rm -rf ./bin ./obj/*.o
