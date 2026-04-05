# CMakeList.txt : CMake project for Learning, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Renderer")

# Add source to this project's executable.
add_executable (Renderer 
	"src/application.cpp"
)
target_include_directories(Renderer PRIVATE 
	${CMAKE_SOURCE_DIR}/dependencies/GLFW/include
	${CMAKE_SOURCE_DIR}/dependencies/GLEW/include
)
target_link_directories(Renderer PRIVATE
	${CMAKE_SOURCE_DIR}/dependencies/GLFW/lib-vc2022/
	${CMAKE_SOURCE_DIR}/dependencies/GLEW/lib/Release/Win32/
)
target_link_libraries(Renderer PRIVATE 
	glfw3
	opengl32
	glew32s
)
target_compile_definitions(Renderer PRIVATE 
	GLEW_STATIC
)

# This passes a macro called ROOT_DIR to your C++ code
target_compile_definitions(Renderer PRIVATE ROOT_DIR="${CMAKE_SOURCE_DIR}")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Renderer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
