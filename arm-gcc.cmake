# bare-metal STM32F407
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Використовуємо ARM GCC
# set(CMAKE_C_COMPILER /opt/homebrew/bin/arm-none-eabi-gcc)
# set(CMAKE_ASM_COMPILER /opt/homebrew/bin/arm-none-eabi-gcc)
# set(CMAKE_CXX_COMPILER /opt/homebrew/bin/arm-none-eabi-g++)


#set(CMAKE_C_COMPILER arm-none-eabi-gcc)
#set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
#sset(CMAKE_CXX_COMPILER arm-none-eabi-g++)


# Виключаємо стандартну бібліотеку
set(CMAKE_EXE_LINKER_FLAGS "-T${CMAKE_SOURCE_DIR}/linker.ld -nostartfiles -nostdlib -Wl,-Map=${CMAKE_PROJECT_NAME}.map")

# Флаги компілятора
set(CMAKE_C_FLAGS "-mcpu=cortex-m4 -mthumb -O2 -Wall -ffreestanding -fno-builtin")
set(CMAKE_ASM_FLAGS "-mcpu=cortex-m4 -mthumb -x assembler-with-cpp")
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)