################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../packages/MD5.c \
../packages/contrib.c \
../packages/contrib_spec.c \
../packages/db.c \
../packages/db_spec.c \
../packages/develop.c \
../packages/develop_spec.c \
../packages/external.c \
../packages/external_spec.c \
../packages/gdbm.c \
../packages/math.c \
../packages/math_spec.c \
../packages/matrix.c \
../packages/matrix_spec.c \
../packages/moon.c \
../packages/moon_spec.c \
../packages/mudlib_stats.c \
../packages/mudlib_stats_spec.c \
../packages/parser.c \
../packages/parser_spec.c \
../packages/sockets.c \
../packages/sockets_spec.c \
../packages/uids.c \
../packages/uids_spec.c 

OBJS += \
./packages/MD5.o \
./packages/contrib.o \
./packages/contrib_spec.o \
./packages/db.o \
./packages/db_spec.o \
./packages/develop.o \
./packages/develop_spec.o \
./packages/external.o \
./packages/external_spec.o \
./packages/gdbm.o \
./packages/math.o \
./packages/math_spec.o \
./packages/matrix.o \
./packages/matrix_spec.o \
./packages/moon.o \
./packages/moon_spec.o \
./packages/mudlib_stats.o \
./packages/mudlib_stats_spec.o \
./packages/parser.o \
./packages/parser_spec.o \
./packages/sockets.o \
./packages/sockets_spec.o \
./packages/uids.o \
./packages/uids_spec.o 

C_DEPS += \
./packages/MD5.d \
./packages/contrib.d \
./packages/contrib_spec.d \
./packages/db.d \
./packages/db_spec.d \
./packages/develop.d \
./packages/develop_spec.d \
./packages/external.d \
./packages/external_spec.d \
./packages/gdbm.d \
./packages/math.d \
./packages/math_spec.d \
./packages/matrix.d \
./packages/matrix_spec.d \
./packages/moon.d \
./packages/moon_spec.d \
./packages/mudlib_stats.d \
./packages/mudlib_stats_spec.d \
./packages/parser.d \
./packages/parser_spec.d \
./packages/sockets.d \
./packages/sockets_spec.d \
./packages/uids.d \
./packages/uids_spec.d 


# Each subdirectory must supply rules for building sources it contributes
packages/%.o: ../packages/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


