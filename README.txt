rm -r build
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../arm-gcc.cmake ..
make
cd ..
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/lora-mesh.elf verify reset exit"