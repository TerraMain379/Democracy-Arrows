# SETTINGS 
OBJECTS_FOLDER=cache/o
PROGRAM_FOLDER=cache
FLAGS_GCC= -c -Wall

# SOURCES
SOURCES=main.c world/world.c world/worldlogic.c logicarrows/logicarrows.c str.c
SRC=src

# CLEAN
all: clean build
clean:
	rm -d -r -f $(OBJECTS_FOLDER)

# BUILD

OBJECTS=$(patsubst %.c,$(OBJECTS_FOLDER)/%.o,$(SOURCES))
build: info program
	@echo "file: $(PROGRAM_FOLDER)/program"
	@echo "BUILDING SUCCESS!"

info:
	@echo "src Dericory: $(SRC)"
	@echo "Global sources: $(SOURCE_GLOBAL)"
	@echo SOURCES: $(SOURCES)
	@echo OBJECTS: $(OBJECTS)

program: $(OBJECTS)
	gcc $(OBJECTS) -o $(PROGRAM_FOLDER)/program


$(OBJECTS_FOLDER)/%.o: $(SRC)/%.c
	@mkdir -p "$$(dirname $@)"
	gcc $(FLAGS_GCC) $< -o $@

run:
	@./$(PROGRAM_FOLDER)/program
