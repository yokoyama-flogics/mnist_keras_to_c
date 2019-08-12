################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/mnist.c \
../src/test_images.c \
../src/test_labels.c \
../src/utils.c 

OBJS += \
./src/main.o \
./src/mnist.o \
./src/test_images.o \
./src/test_labels.o \
./src/utils.o 

C_DEPS += \
./src/main.d \
./src/mnist.d \
./src/test_images.d \
./src/test_labels.d \
./src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


