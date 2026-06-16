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
	"src/renderer.cpp" 
	"src/renderer.h" "src/VertexBuffer.h" "src/VertexBuffer.cpp"  "src/IndexBuffer.h" "src/IndexBuffer.cpp" "src/VertexBufferLayout.h" "src/VertexArray.h" "src/VertexArray.cpp" "src/Shader.h" "src/Shader.cpp" "src/external/stb_image.cpp" "src/Texture.h" "src/Texture.cpp" "src/Camera.cpp" "src/Camera.h" "src/Mesh.h" "src/Mesh.cpp" "src/Model.h" "src/Model.cpp")
target_include_directories(Renderer PRIVATE 
	${CMAKE_SOURCE_DIR}/dependencies/glm
)
add_library(GLEW STATIC IMPORTED)
add_library(GLFW STATIC IMPORTED)

set_target_properties(GLEW PROPERTIES 
	IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/dependencies/GLEW/lib/Release/x64/glew32s.lib
	INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/dependencies/GLEW/include
)
set_target_properties(GLFW PROPERTIES 
	IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/dependencies/GLFW/lib-vc2022/glfw3.lib
	INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/dependencies/GLFW/include
)

include(FetchContent)

# Assimp options (set BEFORE FetchContent_MakeAvailable)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG v6.0.2
)

FetchContent_MakeAvailable(assimp)

target_link_libraries(Renderer PRIVATE 
	GLEW
	GLFW
	opengl32
	assimp
)
target_compile_definitions(Renderer PRIVATE 
	GLEW_STATIC
)

# This passes a macro called ROOT_DIR as a string to your C++ code
target_compile_definitions(Renderer PRIVATE ROOT_DIR="${CMAKE_SOURCE_DIR}")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Renderer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
