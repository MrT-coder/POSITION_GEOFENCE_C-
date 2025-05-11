cmake_minimum_required(VERSION 3.20)
project(PositionGeofence LANGUAGES CXX)

#Versión de c++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# pkg para la instalación de dependencias
find_package(PkgConfig REQUIRED)


find_package(fmt     REQUIRED)
find_package(spdlog  REQUIRED)

# — MongoDB C++ drivers 
pkg_check_modules(BSONCXX   REQUIRED libbsoncxx)
pkg_check_modules(MONGOCXX  REQUIRED libmongocxx)


pkg_check_modules(ICAL REQUIRED libical)

# — Crow por FetchContent directo de github —
include(FetchContent)
set(CROW_USE_BOOST ON CACHE BOOL "")
FetchContent_Declare(
  Crow
  GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
  GIT_TAG        v1.2.0
)
FetchContent_MakeAvailable(Crow)

# — Boost del sistema —
find_package(Boost REQUIRED COMPONENTS system thread chrono)

# — Ejecutable —
add_executable(posgeo_server
  src/main.cpp
)

# — Includes propios —
target_include_directories(posgeo_server
  PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${BSONCXX_INCLUDE_DIRS}
    ${MONGOCXX_INCLUDE_DIRS}
    ${ICAL_INCLUDE_DIRS}        
)


add_definitions(${ICAL_CFLAGS_OTHER})


target_link_libraries(posgeo_server
  PRIVATE
    fmt::fmt
    spdlog::spdlog
    Boost::system
    Boost::thread
    Boost::chrono
    Crow::Crow
    ${BSONCXX_LIBRARIES}
    ${MONGOCXX_LIBRARIES}
    ${ICAL_LIBRARIES}           
)


target_link_directories(posgeo_server
  PRIVATE
    ${BSONCXX_LIBRARY_DIRS}
    ${MONGOCXX_LIBRARY_DIRS}
    ${ICAL_LIBRARY_DIRS}        
)
