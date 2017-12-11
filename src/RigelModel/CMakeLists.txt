# Set porject name
set(TargetName RigelModel)
string(TOUPPER ${TargetName} TargetNameUP)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(headers
Export.h

)

set(sources
InputLib.cpp
)

set(Geometry
    Style.h
    Style.cpp
    GeometryBase.h
    GeometryFloor.h
    GeometryStrip.h
    GeometryLine.h
    GeometryPipe.h

    GeometryPolygon.h
    GeometryBase.cpp
    GeometryFloor.cpp
    GeometryStrip.cpp
    GeometryLine.cpp
    GeometryPolygon.cpp
    GeometryPipe.cpp
    )

# add definitions,unicode and export
add_definitions(-DUNICODE -D_UNICODE -D${TargetNameUP})

# Set porject filiter
source_group("Header Files" FILES ${headers})
source_group("Geometry" FILES ${Geometry})

# Tell CMake to create the helloworld executable
add_library(${TargetName} SHARED ${sources} ${headers} ${Geometry})

# Add dependncies
add_dependencies(${TargetName}  RigelMath)

target_link_libraries(${TargetName} RigelMath)
