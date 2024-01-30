.PHONY: all clean run
# change application name here (executable output name)
TARGET=mapworld

# compiler
CC=clang
# linker
LD=clang
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

# CFLAGS=$(DEBUG) $(OPT) $(WARN)

## Statically linked build
# Need to build raylib from source first

# raylib
CFLAGS += -Ilib/raylib-5.0/src
# LDFLAGS += -Llib/raylib-5.0/src -lraylib
# LDFLAGS += build/macos/libraylib.a
FRAMEWORKS = -framework IOKit -framework Cocoa

all: $(TARGET)


# Main Siumulation
$(TARGET) : main.o canvas.o build/macos/libraylib.a build/macos/liblua.a
	$(LD) -o $(TARGET) $^ $(FRAMEWORKS) $(LDFLAGS)

canvas.o: src/canvas.c src/graph_editor.h src/map.h
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

main.o: src/main.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

release: $(TARGET)
	cp ./$(TARGET) build/macos/$(TARGET).app/Contents/MacOS/

app: release
	open build/macos/$(TARGET).app


# Script
script.o: src/script.c lib/physics2d.h lib/nature2d.h
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

script : main.o script.o
	$(LD) -o script $^ $(FRAMEWORKS) $(LDFLAGS)
	./script
	rm script

#emcc -o game.html game.c -Os -Wall ./path-to/libraylib.a -I. -Ipath-to-raylib-h -L. -Lpath-to-libraylib-a -s USE_GLFW=3 --shell-file path-to/shell.html -DPLATFORM_WEB
web: build/web/libraylib.a src/main.c src/canvas.c web/index.html
	emcc -o build/web/index.html src/main.c src/canvas.c -Os -Wall \
		build/web/libraylib.a \
		-Ilib/raylib-5.0/src \
		-s USE_GLFW=3 \
		--shell-file web/index.html \
		-DPLATFORM_WEB

#
# all: $(TARGET)

# $(TARGET): %.o
# 	$(LD) -o $(TARGET) $< $(LDFLAGS)

# %.o: src/%.c
# 	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

raylib: build/macos/libraylib.a

build/macos/libraylib.a:
	cd lib/raylib-5.0/src && \
	make && \
	cp libraylib.a ../../../build/macos/


lua: build/macos/liblua.a

build/macos/liblua.a:
	cd lib/lua-5.4.6/src && \
	make && \
	cp liblua.a ../../../build/macos/


raylib-web: build/web/libraylib.a

build/web/libraylib.a:
	cd lib/raylib-5.0/src && \
	make PLATFORM=PLATFORM_WEB && \
	cp libraylib.a ../../../build/web/

run:
	./$(TARGET)

clean:
	rm -f *.o 
	rm -f ./$(TARGET)
	rm -f release/$(TARGET).app/Contents/MacOS/$(TARGET)

clean-raylib:
	cd lib/raylib-5.0/src && \
	make clean
	rm -f build/web/libraylib.a
	rm -f build/macos/libraylib.a

clean-lua:
	cd lib/lua-5.4.6/src && \
	make clean
	rm -f build/macos/liblua.a

clean-all: clean clean-raylib clean-lua

test: src/map.h src/map_test.c
	@clang src/map_test.c -o src/map_test
	@./src/map_test
	@rm src/map_test

