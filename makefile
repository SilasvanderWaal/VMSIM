CC = gcc

NAME = VMSIM

BUILD = build
SRC = src

CFLAGS = -Wall -g
LDFLAGS =

# Get all the source files in the SRC directory and its subdirectories
SRCFILES = $(wildcard $(SRC)/*.c) $(wildcard $(SRC)/**/*.c)

# Generate object file names from source file names
OBJFILES = $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCFILES))

.PHONY: build clean memCheck

# Target to build the executable
build: $(OBJFILES)
	@echo "Building $(NAME)"
	@$(CC) $(CFLAGS) $^ -o $(NAME) $(LDFLAGS)
	@echo "Done!"

# Rule to compile each source file into an object file
$(BUILD)/%.o: $(SRC)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c -o $@ $<

# Target to clean up generated files
clean:
	@rm -f $(OBJFILES) $(NAME)
	@rm -r $(BUILD)
