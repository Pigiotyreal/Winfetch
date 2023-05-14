TARGET = bin/winfetch.exe
GUITARGET = bin/winfetch-gui.exe
SRC = src/main.cpp
GUISRC = src/gui.cpp
LDLIBS = -ld3d9 -liphlpapi -ldxgi
INCPATH = src/inc
LIBPATH = src/lib
GUIARGS = -lSDL2main -lSDL2
CC = g++

all: $(TARGET)

gui: $(GUITARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(LDLIBS)

$(GUITARGET): $(GUISRC)
	$(CC) $(GUISRC) -o $(GUITARGET) -I$(INCPATH) -L$(LIBPATH) $(GUIARGS)

clean:
	rm -f $(TARGET) $(GUITARGET)