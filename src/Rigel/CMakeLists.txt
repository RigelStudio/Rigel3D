# Set porject name
set(TargetName Rigel)
string(TOUPPER ${TargetName} TargetNameUP)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Find the Qt librarys
find_package(Qt5 COMPONENTS Core Quick REQUIRED)

# Find all Files
set(qrcs
	${TargetName}.qrc
)

#set(icon ${TargetName}.ico ${TargetName}.rc)

set(forms
	main.qml
)

set(headers
	TopPanel.h
)

set(sources
	main.cpp
	InputLib.cpp
	TopPanel.cpp
)


# add definitions,unicode and export
add_definitions(-DUNICODE -D_UNICODE -D${TargetNameUP}_EXPORTS)

# Set porject filiter
source_group("Header Files" FILES ${headers})
source_group("Form Files" FILES ${forms})
source_group("Resource Files" FILES ${qrcs} ${icon})

# Tell CMake to create the TargetName executable
add_executable(${TargetName}
	${sources}
	${qrcs}
	${headers}
	${forms}
)

# Add dependncies
#add_dependencies(${TargetName} )

set_target_properties(${TargetName} PROPERTIES DEBUG_OUTPUT_NAME "${TargetName}${CMAKE_DEBUG_POSTFIX}")
set_target_properties(${TargetName} PROPERTIES RELEASE_OUTPUT_NAME "${TargetName}${CMAKE_RELEASE_POSTFIX}")

# Use the Qt5 modules
target_link_libraries(${TargetName} Qt5::Core Qt5::Quick Qt5::Qml)
