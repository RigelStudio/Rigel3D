# Set porject name
set(TargetName Geometry)
string(TOUPPER ${TargetName} TargetNameUP)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(headers
Export.h
Style.h
GeometryBase.h
GeometryFloor.h
GeometryStrip.h
GeometryLine.h
GeometryPolygon.h
)

set(sources
InputLib.cpp
Style.cpp
GeometryBase.cpp
GeometryFloor.cpp
GeometryStrip.cpp
GeometryLine.cpp
GeometryPolygon.cpp
)


# add definitions,unicode and export
add_definitions(-DUNICODE -D_UNICODE -D${TargetNameUP}_EXPORTS)

# Add dependncies
#add_dependencies(${TargetName}  MEMath)

# Set porject filiter
source_group("Header Files" FILES ${headers})

# Tell CMake to create the helloworld executable
add_library(${TargetName} SHARED ${sources} ${headers})

target_link_libraries(${TargetName} MEMath)
