# Copyright (c) 2025 Author Sebastian Orozco Castillo. All Rights Reserved.

# Compiladores y banderas
CC = gcc
CXX = g++
CFLAGS = -c -Wall -Iinclude
CXXFLAGS = -c -Wall -Iinclude

# Directorios
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Archivos fuente y headers
C_SOURCES := $(shell find $(SRC_DIR) -name '*.c')
CPP_SOURCES := $(shell find $(SRC_DIR) -name '*.cc')
CHEADERS := $(shell find include -name '*.h')
CPPHEADERS := $(shell find include -name '*.hh')

# Archivos objeto
C_OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_SOURCES))
CPP_OBJECTS := $(patsubst $(SRC_DIR)/%.cc, $(BUILD_DIR)/%.o, $(CPP_SOURCES))
OBJECTS := $(C_OBJECTS) $(CPP_OBJECTS)

# Ejecutables individuales
EXE := $(BIN_DIR)/main

# Objetos por ejecutable (excluyen el otro main)
TARGET := $(OBJECTS)

# Regla por defecto
all: $(EXE)

# Enlazar main
$(EXE): $(TARGET) | $(BIN_DIR)
	$(CXX) $(TARGET) -o $@

# Compilar archivos C
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(CHEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

# Compilar archivos C++:
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc $(CHEADERS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $< -o $@

# Crear bin/
$(BIN_DIR):
	mkdir -p $@

# Linter
lint:
	cpplint --extensions=c,h,cc,hh --filter=-build/header_guard $(shell find $(SRC_DIR) include -name '*.[ch]pp' -o -name '*.[ch]')

# Documentación
doc:
	doxygen

# Limpieza
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) latex html doc/

