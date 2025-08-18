target = httpServer
target_dir = build
target_path = $(target_dir)/$(target)
source_dir = src

ifeq ($(OS), Windows_NT)
	mkdir_command = if not exist $(target_dir) mkdir $(target_dir)
else
	mkdir_command = mkdir -p $(target_dir)
endif

compile:
	$(mkdir_command)
	clang $(wildcard $(source_dir)/*.c) -o $(target_path) -Wall -Werror -ggdb
	cp -r pages $(target_dir)/

run: compile
	@echo ================ RUNNING =================
	./$(target_path)

dbg: compile
	gdb $(target_path)
