src=$(wildcard ./*.c)
target=$(patsubst %.c,%,$(src))

ALL:$(target)
myArg= -Wall -g

%:%.c
	gcc $< -o $@

.PHONY:clean ALL
clean:
	-rm -rf $(target)
