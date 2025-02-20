tools = gcc
flags = -Wextra -Wall

todo = To-Do-List.c
tasks = tasks
buildDir = build
obj = $(todo:.c=.o)

all: $(tasks)

$(tasks): $(todo) 
	@echo "Compiling $<"
	$(tools) -o $(tasks) $(todo) $(flags)

clean:
	rm -rf $(tasks)
