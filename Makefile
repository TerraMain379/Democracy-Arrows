# for build project run "make <os>" or "make clean <os>"
# oss: windows, linux
# example:
# 	make clean windows
# 	make clean linux
#
# for run project "./<PROGRAM_FOLDER>/program"
# example:
# 	./cache/program




# SETTINGS 
OBJECTS_FOLDER=cache/o
PROGRAM_FOLDER=cache
FLAGS_GCC= -c -Wall

# SOURCES
SOURCE_GLOBAL=main/main.c
SOURCE_SYS_WINDOWS=render/window_windows.c
SOURCE_SYS_LINUX=render/window_linux.c
SRC=src

# CLEAN
clean:
	rm -d -r -f $(OBJECTS_FOLDER)

# BUILD

SYS ?= LINUX

MAKEFLAGS = --no-print-directory
linux:
	@$(MAKE) $(MAKEFLAGS) SYS=LINUX build
windows:
	@$(MAKE) $(MAKEFLAGS) SYS=WINDOWS build

SOURCES=$(SOURCE_GLOBAL) $(SOURCE_SYS_$(SYS))
OBJECTS=$(patsubst %.c,$(OBJECTS_FOLDER)/%.o,$(SOURCES))

build: info program

info:
	@echo "src Dericory: $(SRC)"
	@echo "Global sources: $(SOURCE_GLOBAL)"
	@echo "System sources: $(SOURCE_SYS_$(SYS))"
	@echo "Building for $(SYS)"
	@echo SOURCES: $(SOURCES)
	@echo OBJECTS: $(OBJECTS)

program: $(OBJECTS)
	gcc $(OBJECTS) -o $(PROGRAM_FOLDER)/program


$(OBJECTS_FOLDER)/%.o: $(SRC)/%.c
	@mkdir -p "$$(dirname $@)"
	gcc $(FLAGS_GCC) $< -o $@

