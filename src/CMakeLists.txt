# 添加CMakeList头信息，cmake最低版本
cmake_minimum_required(VERSION 2.8.12)

# 设置解决方案名称
project(MEEngine)

# 配置需要的第三方库
set(ThirdParty_DIR "" CACHE PATH "third party directory")

# 如果不配置第三方库，则不进行之后的生成
if(NOT ThirdParty_DIR)
	message(FATAL_ERROR "ThirdParty_DIR variable is not set appropriate!")
endif()

# 判断生成的是32位还是64位
if(${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	SET(Platform "x64")
else(${CMAKE_SIZEOF_VOID_P} MATCHES 8)
	SET(Platform "win32")
endif(${CMAKE_SIZEOF_VOID_P} MATCHES 8)

# 设置输出路径，区分32、64
set(OUTPUT_BINDIR ${CMAKE_SOURCE_DIR}/bin_${Platform})

# 设置lib库的输出路径，区分32、64
set(OUTPUT_LIBDIR ${CMAKE_BINARY_DIR}/${Platform}/lib)

# 对每一个平台，设置其输出路径
foreach(CONF ${CMAKE_CONFIGURATION_TYPES})
	string(TOUPPER "${CONF}" CONF_UC)
	set("CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONF_UC}" ${OUTPUT_LIBDIR})
	set("CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONF_UC}" ${OUTPUT_BINDIR})
	set("CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONF_UC}" "${OUTPUT_BINDIR}${SEPARATE_FOLDER}")
endforeach()

# Debug库输出带d,Release不带
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "add a postfix, usually d on windows")
set(CMAKE_RELEASE_POSTFIX "" CACHE STRING "add a postfix, usually empty on windows")
if(CMAKE_BUILD_TYPE MATCHES "Release")
	SET(CMAKE_BUILD_POSTFIX "${CMAKE_RELEASE_POSTFIX}")
elseif(CMAKE_BUILD_TYPE MATCHES "Debug")
	SET(CMAKE_BUILD_POSTFIX "${CMAKE_DEBUG_POSTFIX}")
else()
	SET(CMAKE_BUILD_POSTFIX "")
endif()

# 设置第三方头文件与链接库的路径
include_directories(
	${ThirdParty_DIR}/include
	${CMAKE_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
)

link_directories(
	${ThirdParty_DIR}/lib
	${CMAKE_BINARY_DIR}/lib
)

# 添加子项目

#基础层
#add_subdirectory(0-Base)
#抽象模型层
#add_subdirectory(1-Model)
#功能层
#add_subdirectory(2-Funcation)
#逻辑层
#add_subdirectory(3-Logic)
#应用
#add_subdirectory(Application)

#add_subdirectory(Geometry)
add_subdirectory(GeometryModel)
add_subdirectory(OSGGraphics)
add_subdirectory(GUITool)
add_subdirectory(ModelEdit)
