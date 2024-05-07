cmake_minimum_required(VERSION 3.27)
project(SDHDGunplayTweaks)

SET(CMAKE_SYSTEM_NAME Windows)

SET(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
SET(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
SET(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)
SET(CMAKE_RANLIB x86_64-w64-mingw32-ranlib)

SET(CMAKE_CXX_STANDARD 20)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -masm=intel -s -static")

add_library(SDHDGunplayTweaks SHARED main.cpp)
target_include_directories(SDHDGunplayTweaks PUBLIC ../nya-common)
target_include_directories(SDHDGunplayTweaks PUBLIC ../nya-common/3rdparty)
target_link_options(SDHDGunplayTweaks PRIVATE "-Wl,--exclude-all-symbols")

set_target_properties(SDHDGunplayTweaks PROPERTIES PREFIX "")
set_target_properties(SDHDGunplayTweaks PROPERTIES SUFFIX "_gcp.dll")