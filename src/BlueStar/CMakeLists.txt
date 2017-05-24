# Set porject name
set(TargetName BlueStar)
string(TOUPPER ${TargetName} TargetNameUP)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
#set(CMAKE_AUTOMOC ON)

# Find the Qt librarys
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5OpenGL)

# Qt资源文件
set(qrcs main.qrc)

#set(icon ${TargetName}.ico ${TargetName}.rc)

#oe配置文件(earth文件, 网络配置, 数据库配置等)
set(ConfigFile )

set(forms
MainWindow.ui
)

set(headers
MainWindow.h
)

set(sources
main.cpp
InputLib.cpp
MainWindow.cpp
)

# Qt warp files
qt5_wrap_ui(Forms_Ui ${forms} ${mainWidgetForms})
qt5_wrap_cpp(Headers_Moc ${headers} ${mainWidgetHeaders})
qt5_add_resources(Res_Qrc ${qrcs} ${ConfigFile})

# add definitions,unicode and export
add_definitions(-DUNICODE -D_UNICODE -D${TargetNameUP}_EXPORTS)

# Set porject filiter
source_group("Header Files" FILES ${headers})
source_group("Form Files" FILES ${forms})
source_group("Resource Files" FILES ${qrcs} ${ConfigFile})
source_group("Generated Files" FILES ${Forms_Ui} ${Headers_Moc} ${Res_Qrc})
#source_group("MainWidget" FILES ${mainWidgetForms} ${mainWidgetHeaders} ${mainWidgetSources})

# Tell CMake to create the TargetName executable
add_executable(${TargetName} ${sources} ${Forms_Ui} ${Headers_Moc} ${Res_Qrc} ${headers} ${icon}
				)

# Add dependncies
add_dependencies(${TargetName} MECore )

set_target_properties(${TargetName} PROPERTIES DEBUG_OUTPUT_NAME "${TargetName}${CMAKE_DEBUG_POSTFIX}")
set_target_properties(${TargetName} PROPERTIES RELEASE_OUTPUT_NAME "${TargetName}${CMAKE_RELEASE_POSTFIX}")

# Use the Qt5 modules
target_link_libraries(${TargetName} Qt5::Core Qt5::Gui Qt5::Widgets
	Qt5::OpenGL)
