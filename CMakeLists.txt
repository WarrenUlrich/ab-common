cmake_minimum_required(VERSION 3.15)

project(ab-common VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(
    ${PROJECT_NAME} STATIC 
        src/gear_manager.cpp
        src/consumable.cpp
        src/equippable.cpp
        src/equipment_set.cpp
)

list(
    APPEND EXTRA_INCLUDE_DIRS 
        "$ENV{USERPROFILE}/AlpacaBot/Include"
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

list(
    APPEND EXTRA_LIB_DIRS 
        "$ENV{USERPROFILE}/AlpacaBot/Library"
)

include_directories(${EXTRA_INCLUDE_DIRS})

find_library(ALPACABOT_LIBRARY NAMES AlpacaLibrary PATHS ${EXTRA_LIB_DIRS} NO_DEFAULT_PATH)
if(NOT ALPACABOT_LIBRARY)
    message(FATAL_ERROR "AlpacaBot library (libAlpacaLibrary.a) not found!")
endif()

target_link_libraries(
    ${PROJECT_NAME} PRIVATE 
        ${ALPACABOT_LIBRARY}
)

# Set the output directory for the shared library
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "$ENV{USERPROFILE}/AlpacaBot/Scripts/Local/${PROJECT_NAME}"
    LIBRARY_OUTPUT_DIRECTORY "$ENV{USERPROFILE}/AlpacaBot/Scripts/Local/${PROJECT_NAME}"
    ARCHIVE_OUTPUT_DIRECTORY "$ENV{USERPROFILE}/AlpacaBot/Scripts/Local/${PROJECT_NAME}"
)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

# If you want to explicitly set the output filename as well (though it should already be ab-alcher.dll)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")
