################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/GARunner.cpp \
../src/Optimizer.cpp \
../src/TSPProblem.cpp \
../src/TSPSolver.cpp 

OBJS += \
./src/GARunner.o \
./src/Optimizer.o \
./src/TSPProblem.o \
./src/TSPSolver.o 

CPP_DEPS += \
./src/GARunner.d \
./src/Optimizer.d \
./src/TSPProblem.d \
./src/TSPSolver.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


