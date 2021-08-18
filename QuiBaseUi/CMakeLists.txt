# CMakeList.txt: CMakeProject 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

#-----------------TODO 自定义编译选项
# set(CMAKE_CXX_FLAGS “-std=c++11 -O2 -g”)

STRING( REGEX REPLACE ".*/(.*)" "\\1" PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} ) 

SET(QT_CMAKE_PATH ${QT_PATH}/lib/cmake)

#-----------------TODO 添加模块变量
set(_INC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../${PROJECT_NAME}/include)
set(_SRC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../${PROJECT_NAME}/src)

#将各种文件归类到指定变量
FILE(GLOB_RECURSE HEADER_FILES ${_INC_PATH}/*.h)
FILE(GLOB_RECURSE SOURCE_FILES ${_SRC_PATH}/*.cpp)


SET(CMAKE_PREFIX_PATH ${QT_CMAKE_PATH})
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
#FIND_PACKAGE(Qt5Sql REQUIRED)
#FIND_PACKAGE(Qt5Network REQUIRED)

FILE(GLOB MOC_FILES ${_SRC_PATH}/moc_*.cpp)
FILE(GLOB_RECURSE FORMS ${_SRC_PATH}/*.ui)

IF(FORMS)
	QT5_WRAP_UI(FORMS_UIC ${FORMS})
	QT5_ADD_RESOURCES(qrc_FILES ${_SRC_PATH}/${PROJECT_NAME}.qrc)
ENDIF()

QT5_WRAP_CPP(MOC_FILES ${HEADER_FILES})

#将ui文件和生成文件整理在一个文件夹中
SOURCE_GROUP("Form Files" FILES ${FORMS})
#将qrc资源文件整理在一个文件夹中
SOURCE_GROUP("Resource Files" FILES ${_SRC_PATH}/${PROJECT_NAME}.qrc)
#将MOC,UI,QRC的中间生成文件编译进EXE中
SOURCE_GROUP("Generated Files" FILES ${MOC_FILES} ${FORMS_UIC})


#查找当前目录下所有的.h和.cpp文件
SOURCE_GROUP("Header Files" FILES ${HEADER_FILES})
SOURCE_GROUP("Source Files" FILES ${SOURCE_FILES})


#-----------------TODO 创建工程内的库
#-----------------STATIC表示创建静态库，目标文件为 libmylib.a，如果是 SHARED， 则为创建动态库.
IF(OUTPUT_TYPE STREQUAL "dll")
add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES} ${MOC_FILES} ${FORMS_UIC} ${qrc_FILES})
ELSEIF(OUTPUT_TYPE STREQUAL "lib")
add_library(${PROJECT_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES} ${MOC_FILES} ${FORMS_UIC} ${qrc_FILES})
ELSE()
add_executable (${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} ${MOC_FILES} ${FORMS_UIC} ${qrc_FILES})
ENDIF()
#-----------------TODO EXE编译连接
#add_executable (${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} ${MOC_FILES} ${FORMS_UIC} ${qrc_FILES})

#-----------------TODO添加头文件的搜索目录
include_directories(${_INC_PATH}
					${_SRC_PATH})
					
#-----------------TODO 添加lib文件的搜索目录
link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../${PROJECT_NAME}/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib)


target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
#target_link_libraries(${PROJECT_NAME} Qt5::Network)
#target_link_libraries(${PROJECT_NAME} Qt5::Sql)


QT5_USE_MODULES(${PROJECT_NAME} Core)
QT5_USE_MODULES(${PROJECT_NAME} Gui)
QT5_USE_MODULES(${PROJECT_NAME} Widgets)
#QT5_USE_MODULES(${PROJECT_NAME} Network)
#QT5_USE_MODULES(${PROJECT_NAME} Sql)



