################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../DIO_program.c \
../GIE_program.c \
../LED_program.c \
../MOTOR_program.c \
../SMART_Slave.c \
../SPI_program.c \
../TMR0_program.c \
../TMR1_program.c \
../ULTRASNK_program.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
DIO_program.o \
GIE_program.o \
LED_program.o \
MOTOR_program.o \
SMART_Slave.o \
SPI_program.o \
TMR0_program.o \
TMR1_program.o \
ULTRASNK_program.o


OBJS_AS_ARGS +=  \
DIO_program.o \
GIE_program.o \
LED_program.o \
MOTOR_program.o \
SMART_Slave.o \
SPI_program.o \
TMR0_program.o \
TMR1_program.o \
ULTRASNK_program.o


C_DEPS +=  \
DIO_program.d \
GIE_program.d \
LED_program.d \
MOTOR_program.d \
SMART_Slave.d \
SPI_program.d \
TMR0_program.d \
TMR1_program.d \
ULTRASNK_program.d


C_DEPS_AS_ARGS +=  \
DIO_program.d \
GIE_program.d \
LED_program.d \
MOTOR_program.d \
SMART_Slave.d \
SPI_program.d \
TMR0_program.d \
TMR1_program.d \
ULTRASNK_program.d


OUTPUT_FILE_PATH +=SMART_Slave.elf

OUTPUT_FILE_PATH_AS_ARGS +=SMART_Slave.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR32/GNU C Compiler



















./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)D:\PROGRAMS\Atmel Studio\atmel\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -funsigned-char -funsigned-bitfields -O1 -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"  -mmcu=atmega32   -o"$@" "$<" 
	@echo Finished building: $<



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : (AVR_8_bit_GNU_Toolchain_3.4.1_830) 4.6.2
	$(QUOTE)D:\PROGRAMS\Atmel Studio\atmel\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="SMART_Slave.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group  -mmcu=atmega32  
	@echo Finished building target: $@
	"D:\PROGRAMS\Atmel Studio\atmel\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "SMART_Slave.elf" "SMART_Slave.hex"
	"D:\PROGRAMS\Atmel Studio\atmel\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "SMART_Slave.elf" "SMART_Slave.eep" || exit 0
	"D:\PROGRAMS\Atmel Studio\atmel\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objdump.exe" -h -S "SMART_Slave.elf" > "SMART_Slave.lss"
	"D:\PROGRAMS\Atmel Studio\atmel\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "SMART_Slave.elf" "SMART_Slave.srec"
	"D:\PROGRAMS\Atmel Studio\atmel\extensions\Atmel\AVRGCC\3.4.1.95\AVRToolchain\bin\avr-size.exe" "SMART_Slave.elf"
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "SMART_Slave.elf" "SMART_Slave.a" "SMART_Slave.hex" "SMART_Slave.lss" "SMART_Slave.eep" "SMART_Slave.map" "SMART_Slave.srec"
	