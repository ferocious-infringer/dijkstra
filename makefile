CC = gcc
INCLUDE = -Iinclude
LIBRARY = -Llib
LINKER = -lglfw3 -lopengl32 -lgdi32
OBJECTS = main.o list.o point.o tag.o link.o path.o ext_parser.o ext_debug.o window.c
OUTPUT = run.exe

.PHONY: run
run: build
	.\$(OUTPUT) input.txt

.PHONY: force
force: clean build run

main.o: list.h link.h ext_parser.h ext_debug.h window.h
path.o: path.h link.h
ext_parser.o: ext_parser.h list.h point.h tag.h link.h
ext_debug.o: ext_debug.h list.h point.h tag.h link.h path.h

$(OUTPUT): $(OBJECTS)
	$(CC) -o $@ $^ $(INCLUDE) $(LIBRARY) $(LINKER)

%.o: %.c %.h
	$(CC) -o $@ -c $< $(INCLUDE)

%.o: %.c
	$(CC) -o $@ -c $< $(INCLUDE)

.PHONY: build
build: $(OUTPUT)

.PHONY: clean
clean:
	rm -rf *.o *.exe
