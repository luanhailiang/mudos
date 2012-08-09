################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../compat/simuls/apply.c \
../compat/simuls/break_string.c \
../compat/simuls/dump_socket_status.c \
../compat/simuls/parse_command.c \
../compat/simuls/process_string.c \
../compat/simuls/tail.c 

OBJS += \
./compat/simuls/apply.o \
./compat/simuls/break_string.o \
./compat/simuls/dump_socket_status.o \
./compat/simuls/parse_command.o \
./compat/simuls/process_string.o \
./compat/simuls/tail.o 

C_DEPS += \
./compat/simuls/apply.d \
./compat/simuls/break_string.d \
./compat/simuls/dump_socket_status.d \
./compat/simuls/parse_command.d \
./compat/simuls/process_string.d \
./compat/simuls/tail.d 


# Each subdirectory must supply rules for building sources it contributes
compat/simuls/%.o: ../compat/simuls/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


