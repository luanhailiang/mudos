################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../amiga/crypt.c \
../amiga/cstrip.c \
../amiga/replace.c \
../amiga/signal.c \
../amiga/signal_rr.c \
../amiga/socket.c \
../amiga/touch.c 

OBJS += \
./amiga/crypt.o \
./amiga/cstrip.o \
./amiga/replace.o \
./amiga/signal.o \
./amiga/signal_rr.o \
./amiga/socket.o \
./amiga/touch.o 

C_DEPS += \
./amiga/crypt.d \
./amiga/cstrip.d \
./amiga/replace.d \
./amiga/signal.d \
./amiga/signal_rr.d \
./amiga/socket.d \
./amiga/touch.d 


# Each subdirectory must supply rules for building sources it contributes
amiga/%.o: ../amiga/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


