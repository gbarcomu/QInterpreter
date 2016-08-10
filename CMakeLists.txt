CMAKE_MINIMUM_REQUIRED( VERSION 3.0 )

# SET( CMAKE_CXX_FLAGS 	"${CMAKE_CXX_FLAGS} -std=c++11" )
SET( PROJ_NAME		"QInterpreter" )
SET( PROJ_PATH		${CMAKE_SOURCE_DIR} )
SET( PROJ_OUT_PATH	${CMAKE_BINARY_DIR} )
SET( PROJ_LIBRARIES	"curl" )
SET( PROJ_INCLUDES 	"include" )

FILE( GLOB_RECURSE PROJ_SOURCES src/*.cpp )
FILE( GLOB_RECURSE PROJ_HEADERS include/*.h )

PROJECT( ${PROJ_NAME} )

INCLUDE_DIRECTORIES( ${PROJ_INCLUDES} )

FIND_PACKAGE(BISON)
SET(BisonOutput ${CMAKE_CURRENT_BINARY_DIR}/../src/Parser.cpp)
SET(BisonHeader ${CMAKE_CURRENT_BINARY_DIR}/../include/Parser.h)
SET(BisonSource ${CMAKE_CURRENT_BINARY_DIR}/../Parser.y)
#IF(BISON_FOUND)
#	ADD_CUSTOM_COMMAND(
#		OUTPUT ${BisonOutput}
#		COMMAND ${BISON_EXECUTABLE}
#			--defines=${BisonHeader}
#			--output=${BisonOutput}
#			${BisonSource}
#		COMMENT "Generating Parser"
#	)
#ENDIF()

FIND_PACKAGE(FLEX)
SET(FlexOutput ${CMAKE_CURRENT_BINARY_DIR}/../src/Lexer.cpp)
SET(FlexHeader ${CMAKE_CURRENT_BINARY_DIR}/../include/Lexer.h)
SET(FlexSource ${CMAKE_CURRENT_BINARY_DIR}/../Lexer.l)
#IF(FLEX_FOUND)
#	ADD_CUSTOM_COMMAND(
#		OUTPUT ${FlexOutput}
#		COMMAND ${FLEX_EXECUTABLE}
#			--header-file=${FlexHeader}
#			--out-file=${FlexOutput}
#			${FlexSource}
#		COMMENT "Generating Lexer"
#	)
#ENDIF()


SET_SOURCE_FILES_PROPERTIES( ${BisonOutput} ${FlexOutput} PROPERTIES LANGUAGE CXX )
BISON_TARGET(Parser Parser.y ${BisonOutput} COMPILE_FLAGS "--defines=${BisonHeader}")
FLEX_TARGET(Lexer Lexer.l ${FlexOutput} COMPILE_FLAGS "--header-file=${FlexHeader} --noyywrap --bison-bridge --reentrant --warn --nodefault --never-interactive")
ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

ADD_EXECUTABLE( ${PROJ_NAME} ${BISON_Parser_OUTPUTS} ${FLEX_Lexer_OUTPUTS} ${PROJ_SOURCES} )

# Only works for CMake +3.0
SET_PROPERTY(TARGET ${PROJ_NAME} PROPERTY CXX_STANDARD 11)
SET_PROPERTY(TARGET ${PROJ_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

TARGET_LINK_LIBRARIES( ${PROJ_NAME} ${PROJ_LIBRARIES} )
