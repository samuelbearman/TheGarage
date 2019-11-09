NASM=nasm -f elf64 -g -F dwarf
OBJS=proj4.o driver.o library.o

proj4: $(OBJS)
	$(LD) -o $@ $(OBJS)

test: proj4
	./test.sh

clean:
	rm -f *.o proj4 output.txt

%.o: %.asm
	$(NASM) $<

%.o: %.c
	gcc -g -o $@ -c $<
