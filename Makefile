FLAGS = -Wall -Wextra
OBJS = main.o gen.o player.o queue.o render.o solve.o stack.o

all: maze

maze: $(OBJS)
	gcc $(FLAGS) $(OBJS) -o maze

main.o: c/main.c h/main.h h/gen.h h/render.h h/solve.h h/player.h
	gcc $(FLAGS) -c c/main.c

gen.o: c/gen.c h/gen.h h/stack.h h/main.h
	gcc $(FLAGS) -c c/gen.c

player.o: c/player.c h/player.h h/gen.h h/render.h h/main.h
	gcc $(FLAGS) -c c/player.c

queue.o: c/queue.c h/queue.h
	gcc $(FLAGS) -c c/queue.c

render.o: c/render.c h/render.h h/main.h
	gcc $(FLAGS) -c c/render.c

solve.o: c/solve.c h/solve.h h/queue.h h/stack.h h/main.h
	gcc $(FLAGS) -c c/solve.c

stack.o: c/stack.c h/stack.h
	gcc $(FLAGS) -c c/stack.c

clean:
	rm -f $(OBJS) maze .vscode/*

