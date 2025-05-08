cmake_minimum_required(VERSION 3.20)
project(PositionGeofence LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# — Asegúrate de que pkg-config vea tus .pc (ajusta si instalaste en otro sitio) —
# export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH

find_package(PkgConfig REQUIRED)
find_package(fmt     REQUIRED)
find_package(spdlog  REQUIRED)

# Esto leerá libbsoncxx.pc y libmongocxx.pc
pkg_check_modules(BSONCXX REQUIRED libbsoncxx)
pkg_check_modules(MONGOCXX REQUIRED libmongocxx)

# — Crow por FetchContent —
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

add_executable(posgeo_server
  src/main.cpp
  src/decoder.cpp
)

# — Tus includes propios y los de BSON/Mongo —
target_include_directories(posgeo_server
  PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${BSONCXX_INCLUDE_DIRS}
    ${MONGOCXX_INCLUDE_DIRS}
)

# — Linkea con Boost, Crow y MongoDB —
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
)

# — A veces pkg-config necesita estos dirs al linkear —
target_link_directories(posgeo_server
  PRIVATE
    ${BSONCXX_LIBRARY_DIRS}
    ${MONGOCXX_LIBRARY_DIRS}
)
