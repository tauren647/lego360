cmake_minimum_required(VERSION 3.8)
project(lego360)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES lego360.ino L_Color.hpp L_Led.hpp L_Pins.hpp L_Servo.hpp L_Shooter.hpp L_Stepper.hpp)
add_executable(main ${SOURCE_FILES})