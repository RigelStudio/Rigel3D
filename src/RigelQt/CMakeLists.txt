# Set porject name
set(TargetName RigelQt)
string(TOUPPER ${TargetName} TargetNameUP)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find the Qt librarys
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)

# Find all Files
set(qrcs ${TargetName}.qrc)

set(forms )

set(headers
Export.h
DialogBase.h
)

set(sources
DialogBase.cpp
)

# Qt warp files
qt5_wrap_ui(Forms_Ui ${forms})
qt5_wrap_cpp(Headers_Moc ${headers})
qt5_add_resources(Res_Qrc ${qrcs})

# add definitions,unicode and export
add_definitions(-DUNICODE -D_UNICODE -D${TargetNameUP})

# Set porject filiter
source_group("Header Files" FILES ${headers})
source_group("Form Files" FILES ${forms})
source_group("Resource Files" FILES ${qrcs})
source_group("Generated Files" FILES ${Forms_Ui} ${Headers_Moc} ${Res_Qrc})

# Tell CMake to create the helloworld executable
add_library(${TargetName} SHARED ${sources} ${Forms_Ui} ${Headers_Moc} ${Res_Qrc} ${headers})

# Use the Widgets module from Qt 5.
target_link_libraries(${TargetName} Qt5::Core Qt5::Gui Qt5::Widgets)
