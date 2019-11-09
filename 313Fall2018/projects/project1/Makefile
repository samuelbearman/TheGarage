# Leave the following lines alone!!!
AS=nasm
LD=ld
ASFLAGS=-f elf64 -g -F dwarf
LDFLAGS= 
.PREFIXES=.o .asm
#
# End of provided rules
#
# Modify following to the name of your assembly source file
ALL_SOURCES=atbash.asm
# Modify following to the name of your linked program
ALL_TARGETS=atbash.out

# Do not modify remainder of this Makefile

ASM_OBJECTS=$(ALL_SOURCES:.asm=.o)

all: $(ALL_SOURCES) $(ALL_TARGETS)

$(ALL_TARGETS): $(ASM_OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $<

$(ASM_OBJECTS): $(ALL_SOURCES)
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm $(ALL_TARGETS) $(ASM_OBJECTS)
