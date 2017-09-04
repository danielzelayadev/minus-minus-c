CPP_SRC = $(LEXER) $(PARSER) src/main.cpp

ENTRY = samples/test.c

LEXER = src/lexer.cpp
PARSER = src/parser.cpp

TOKENS = src/tokens.h

REPORT = debug/state.txt

FLEX_SRC = src/tokens.l

BISON_SRC = src/grammar.y

OBJ_FILES = ${CPP_SRC:src/%.cpp=obj/%.o}

TARGET = bin/tinyc

.PHONY: clean

all: run

build: $(TARGET)

run: $(TARGET)
	./$(TARGET) $(ENTRY)

$(LEXER): $(FLEX_SRC)
	flex -o $@ $<

$(PARSER): $(BISON_SRC)
	mkdir -p debug
	bison --defines=$(TOKENS) -v --report-file=$(REPORT) -o $@ $<

obj/%.o: src/%.cpp
	mkdir -p obj
	g++ -w -g -c -o $@ $<

$(TARGET): $(OBJ_FILES)
	g++ -w -g -o $@ $^

clean:
	rm -f bin/* obj/* debug/*
	rm -f $(LEXER) $(PARSER) $(TOKENS)