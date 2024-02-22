#Author: Leonardo Oliveira de Jesus - 12111EBI033												#COMMENTS:


# Program name 

PRONAME	:	=	blinky

#<Toolchain> tools 

CC	=	arm-none-eabi-gcc														#executable name (C Compiler)
LD	=	arm-none-eabi-gcc
CP	=	arm-none-eabi-objcopy
RM	=	rm	-	rf

#Object Files Directives and Dependecies List <saved>

DIROBJECT: build

DEPENLIST: .deps

#Files which need to be compiled 

SRCS :  src/startup.c \ 															#"source" which cointains source-code(Código-Fonte)
		src/main.c

#Compiler Flags(compilation parameters)

CFLAGS		= -mcpu=cortex-m4 -thumb -Wall -O0  			 									#Activating Thumb mode, enabling Warnings e supressing optimizations
DEPFLAGS	= -MMD -MP -MF $(DEPENLIST)/$*.d												#generating files(flags), phony target e Dependencies List usage
LFLAGS		= -nostdlib -T stm32f411-rom.ld -Wl,-Map=blinky.map										# Linking procces for stm32 (Read Only Memory)

#Generating Object Files list and directives which will be first saved

OBJS = $(patsubst %, $(DIROBJECT)/%.o, $(basename $(SRCS)))											# generating a succesfull object files list, which have full path and have them saved to existent directives
$(shell mkdir -p $(dir $(OBJS)) > /dev/null)

#Generating Files List of Dependecies List and creating a directive to save them to

DEPS = $(patsubst %, $(DEPENLIST)/%.d, $(basename $(SRCS)))
$(shell mkdir -p $(dir $(DEPS)) > /dev/null)

all: $(OBJS) $(PRONAME).elf $(PRONAME).bin													#verifying: Object Files, Executable and linkable Format (program) and binary (for MCU memory)

$(PRONAME).elf: $(OBJS)																#verifying if all object files were updated and generated and then creating the executable ELF 
	$(LD) $(LFLAGS) -o $@ $^																				

$(PRONAME).bin: $(PRONAME).elf															#.bin depends on .elf (generate the .bin file)
	$(CP) -O binary $^ $@

$(DIROBJECT)/%.o: %.c $(DEPENLIST)/%.d														#compile .c into .o and verify if .d needs its generation
	$(CC) -c $(CFLAGS) $(DEPFLAGS) $< -o $@

#New TARGET for each dependency file

$(DEPS):

#Include the dependency files content

-include $(DEPS)

.PHONY: clean

clean:																		#Remove or Delete
		$(RM) $(DIROBJECT) $(DEPENLIST)
		$(RM) $(PRONAME).elf $(PRONAME).bin $(PRONAME).map
