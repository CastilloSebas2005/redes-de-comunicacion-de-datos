# Copyright (c) 2025 Author Sebastian Orozco Castillo. All Rights Reserved.

.PHONY: tests

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

EXE := $(BIN_DIR)/main

TARGET := $(OBJECTS)

# Regla por defecto
all: $(EXE)

# Enlazar main
$(EXE): $(TARGET) | $(BIN_DIR)
	$(CXX) $(TARGET) -o $@ $(LDFLAGS)

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

# asan
asan: CFLAGS += -fsanitize=address -g
asan: CXXFLAGS += -fsanitize=address -g
asan: LDFLAGS := -fsanitize=address -g
asan: clean
	$(MAKE) all CFLAGS="$(CFLAGS)" CXXFLAGS="$(CXXFLAGS)" LDFLAGS="$(LDFLAGS)"

# Linter
lint:
		cpplint --extensions=c,h,cc,hh --filter=-build/header_guard $(shell find $(SRC_DIR) include \( -name '*.c' -o -name '*.h' -o -name '*.cc' -o -name '*.hh' \))

# Documentación
doc:
	doxygen

# Limpieza
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) latex html doc/

tests:
	for f in tests/*.txt; do \
		echo "==> $$(basename $$f)"; \
		./bin/main "$$(basename $$f)"; \
	done


