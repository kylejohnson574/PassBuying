cmake_minimum_required(VERSION 3.5)
project(PASSBUYING C)
#add_subdirectory( PassBuying )

set( SOURCE
 ${SOURCE}
 Buy.c
 PassManager.c
 PassQueue.c
 Costs.c 
 TransMain.c
 UsePass.c
 PassBuying.c
 )

set( HEADERS
 ${HEADERS}
 PassDef.h
 Buy.h
 PassManager.h
 PassQueue.h
 TransDef.h
 UserDefine.h
 Costs.h
 TransMain.h
 stdafx.h
 UsePass.h

)

include_directories(
 ./
)

add_executable(PASSBUYING ${SOURCE} )
