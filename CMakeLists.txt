cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(HandlerWindowForm)
## укажем проект 

set(CMAKE_CXX_STANDARD 17)
## используемые языки

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(
        CMAKE_CXX_FLAGS_DEBUG
        "${CMAKE_CXX_FLAGS_DEBUG} /JMC"
    )
else()
    set(
        CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wno-unused-parameter -Wno-implicit-fallthrough"
    )
endif()

set(CMAKE_PREFIX_PATH "C:/dev/SFML-2.6.1/lib/cmake/SFML")
set(SFML_ROOT "C:/dev/SFML-2.6.1/lib/cmake/SFML")
set(SFML_INCLUDE_DIR "C:/dev/SFML-2.6.1/include")
set(SFML_STATIC_LIBRARIES TRUE) #только если статическая сборка библиотеки

## укажем, что мы хотим найти пакет
find_package(SFML 2.6.1 COMPONENTS graphics REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

file(GLOB sources
    ./*.cpp
    ./*.h
	./*.ttf
	./*.jpg
)

##  укажем, что мы хотим собрать exe-файл
add_executable( ${PROJECT_NAME} ${sources} )

## и слинковать его с такими-то библиотеками
target_link_libraries(${PROJECT_NAME} sfml-graphics)

