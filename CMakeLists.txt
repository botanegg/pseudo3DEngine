cmake_minimum_required(VERSION 3.7)
project(Pseudo3DEngine)

# Download automatically, you can also just copy the conan.cmake file
if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
	message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
	file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
			"${CMAKE_BINARY_DIR}/conan.cmake")
endif ()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_add_remote(NAME bincrafters URL
		https://api.bintray.com/conan/bincrafters/public-conan)

conan_cmake_run(
		REQUIRES
		sfml/2.5.1@bincrafters/stable
		OPTIONS
		sfml:shared=False sfml:graphics=True sfml:audio=True sfml:window=True sfml:network=True
		BASIC_SETUP
		CMAKE_TARGETS # individual targets to link to
		BUILD
		missing)

set(SOURCE_FILES
		src/main.cpp
		src/settings.h
		src/World.cpp
		src/World.h
		src/Object2D.cpp
		src/Object2D.h
		src/Camera.cpp
		src/Camera.h
		src/Idrawable.h
		src/Point2D.cpp
		src/Point2D.h
		src/Polygon2D.cpp
		src/Polygon2D.h
		src/Circle2D.cpp
		src/Circle2D.h
		src/Menu.cpp
		src/Menu.h
		src/Weapon.cpp
		src/Weapon.h
		src/UDPSocketConnection.cpp
		src/UDPSocketConnection.h
		)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_link_libraries(${PROJECT_NAME} CONAN_PKG::sfml)
