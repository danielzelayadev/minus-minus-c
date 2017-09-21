CPP_SRC =  $(PARSER) $(LEXER) src/main.cpp src/ast.cpp src/expr.cpp
CPP_SRC += src/unary-expr.cpp src/binary-expr.cpp src/primary-expr.cpp
CPP_SRC += src/postfix-expr.cpp src/statements.cpp src/symbol-table.cpp src/context.cpp
CPP_SRC += src/errors.cpp src/helpers.cpp src/memory.cpp src/utils.cpp

LEXER = src/lexer.cpp
PARSER = src/parser.cpp

TOKENS = src/tokens.h

REPORT = debug/state.txt

FLEX_SRC = src/tokens.l

BISON_SRC = src/grammar.y

OBJ_FILES = ${CPP_SRC:src/%.cpp=obj/%.o}

CXXFLAGS=-std=c++11

TARGET = bin/mmc

.PHONY: clean

build: $(TARGET)

$(LEXER): $(FLEX_SRC)
	flex -o $@ $<

$(PARSER): $(BISON_SRC)
	mkdir -p debug
	bison --defines=$(TOKENS) -v --report-file=$(REPORT) -o $@ $<

obj/%.o: src/%.cpp
	mkdir -p obj
	g++ -std=c++11 -w -g -c -o $@ $<

$(TARGET): $(OBJ_FILES)
	g++ -std=c++11 -w -g -o $@ $^

clean:
	rm -f bin/* obj/* debug/*
	rm -f $(LEXER) $(PARSER) $(TOKENS) $(OUTPUT)