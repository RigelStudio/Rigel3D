# Set porject name

set(TargetName RigelCore)
string(TOUPPER ${TargetName} TargetNameUP)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find all Files
set(headers
			Export.h
			Version.h
			FileUtils.h
			SigSlot.h
			)

set(sources InputLib.cpp
			FileUtils.cpp
			SigSlot.cpp
			)

# add definitions,unicode and export
add_definitions(-DUNICODE -D_UNICODE -D${TargetNameUP})

# Set porject filiter
source_group("Header Files" FILES ${headers})
source_group("Resource Files" FILES ${qrcs})

# Tell CMake to create the helloworld executable
add_library(${TargetName} SHARED ${sources} ${headers})

# Use the Widgets module from Qt 5.
target_link_libraries(${TargetName}  OpenThreads.lib)
