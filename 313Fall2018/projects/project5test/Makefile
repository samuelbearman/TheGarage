NASM=nasm -f elf64 -g -F dwarf

# Modify following to the name of your linked program
TARGET=proj5

# Modify following to the list of component object files
OBJS=driver.c proj5.c bookcmp.o 

#
# Do not modify remainder of this Makefile
#
%.o: %.asm
	$(NASM) $<

${TARGET}: ${OBJS}
	gcc -g ${OBJS} -o $@

test: proj5
	./test.sh

clean:
	rm -f *.o proj5 output.txt
