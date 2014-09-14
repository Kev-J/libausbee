libausbee is an open-source library providing drivers and functions for robotics application embedding STM32 devices. This library is still under high development.

Compiling
======================

On baremetal (STM32)
----------------------

While calling make, some variables must be defined:

STD_PERIPH_INCLUDES_DIR :
Includes directory of the StdPeriph_Driver library.

DEVICE_INCLUDES_DIR :
Device includes directory. Directory where, for instance, stm32f4xx.h is located.

CMSIS_INCLUDES_DIR :
CMSIS includes directory.

DEVICE :
Device name. The values should be :
-For STM32F4XX : STM32F40\_41xxx, STM32F427\_437xx, STM32F429\_439xx, STM32F401xx
-For STM32F1XX : STM32F10X_LD, STM32F10X_LD_VL, STM32F10X_MD, STM32F10X_MD_VL, STM32F10X_HD, STM32F10X_HD_VL, STM32F10X_XL, STM32F10X_CL
Other devices are not supported yet.

Tools on GNU Linux
----------------------

dependencies for lidar-viewer:
- Qt4

Use CMakeLists. It requires Qt4.
In this directory:
$ mkdir build
$ cd build
$ cmake ..
$ make

The outputs should be in the "bin" directory in your "build" directory.
