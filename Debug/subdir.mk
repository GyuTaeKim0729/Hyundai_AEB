################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Cpu0_Main.c \
../Cpu1_Main.c \
../Cpu2_Main.c \
../button.c \
../buzzer.c \
../led.c \
../led_rgb.c \
../lib.c \
../mode_1.c \
../mode_1_1.c \
../mode_2.c \
../potentiometer.c \
../timer.c \
../ultrasonic.c 

OBJS += \
./Cpu0_Main.o \
./Cpu1_Main.o \
./Cpu2_Main.o \
./button.o \
./buzzer.o \
./led.o \
./led_rgb.o \
./lib.o \
./mode_1.o \
./mode_1_1.o \
./mode_2.o \
./potentiometer.o \
./timer.o \
./ultrasonic.o 

COMPILED_SRCS += \
./Cpu0_Main.src \
./Cpu1_Main.src \
./Cpu2_Main.src \
./button.src \
./buzzer.src \
./led.src \
./led_rgb.src \
./lib.src \
./mode_1.src \
./mode_1_1.src \
./mode_2.src \
./potentiometer.src \
./timer.src \
./ultrasonic.src 

C_DEPS += \
./Cpu0_Main.d \
./Cpu1_Main.d \
./Cpu2_Main.d \
./button.d \
./buzzer.d \
./led.d \
./led_rgb.d \
./lib.d \
./mode_1.d \
./mode_1_1.d \
./mode_2.d \
./potentiometer.d \
./timer.d \
./ultrasonic.d 


# Each subdirectory must supply rules for building sources it contributes
%.src: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc27xd "-fC:/Users/user/Desktop/embedded_project/PATS/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

%.o: ./%.src subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


