macro(COPY_ASSETS)
    set (EXCLUDE_DIR ${PROJECT_SOURCE_DIR}/Assets/)

    file (GLOB SOURCE_FILES 
	    ${PROJECT_SOURCE_DIR}/Assets/*	
    )
    foreach (FILE ${SOURCE_FILES})
        string (FIND ${FILE} ${EXCLUDE_DIR} EXCLUDE_DIR_FOUND)
        if (NOT ${EXCLUDE_DIR_FOUND} EQUAL -1)
            string(REPLACE ${EXCLUDE_DIR} "" REPLACED_PATH ${FILE})
            configure_file(Assets/${REPLACED_PATH} ${CMAKE_BINARY_DIR}/Assets/${REPLACED_PATH} COPYONLY)
        endif ()
    endforeach(FILE)
endmacro()