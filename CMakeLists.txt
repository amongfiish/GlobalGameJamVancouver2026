cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_NAME "GlobalGameJamVancouver2026")

project(${PROJECT_NAME})

add_subdirectory(lib/LeoEngine)

file(GLOB SOURCES src/*)

if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
else ()
    add_executable(${PROJECT_NAME} ${SOURCES})
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE LeoEngine)

if (APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
                          MACOSX_BUNDLE TRUE
                          MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)
endif ()

