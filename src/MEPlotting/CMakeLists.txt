# Set porject name
set(TargetName MEPlotting)
string(TOUPPER ${TargetName} TargetNameUP)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(headers
Export.h
PosPickHandler.h
)

set(sources
InputLib.cpp
PosPickHandler.cpp
)

#添加测量模块
set(Measure
  Measure/MeasureTool.h
  Measure/MeasureTool.cpp
  Measure/MeasureBase.h
  Measure/MeasureBase.cpp
  Measure/MeasureLength.h
  Measure/MeasureLength.cpp
)
#添加符号化模块
set(Symbols
  Symbols/SymbolTool.h
  Symbols/SymbolTool.cpp
)
#添加标绘模块
set(Plotting
  Plotting/PlottingTool.h
  Plotting/PlottingTool.cpp
)

# add definitions,unicode and export
add_definitions(-DUNICODE -D_UNICODE -D${TargetNameUP}_EXPORTS)

# Add dependncies
#add_dependencies(${TargetName}  MECore)

# Set porject filiter
source_group("Header Files" FILES ${headers})
source_group("Measure" FILES ${Measure} )
source_group("Symbols" FILES ${Symbols} )
source_group("Plotting" FILES ${Plotting} )

# Tell CMake to create the helloworld executable
add_library(${TargetName} SHARED ${sources} ${headers} ${Measure} ${Symbols}
${Plotting} )

target_link_libraries(${TargetName} MECore)
