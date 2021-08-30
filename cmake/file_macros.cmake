macro(COPY_FILES_FROM_FOLDER DIR_PATH)
    set (EXCLUDE_DIR ${PROJECT_SOURCE_DIR}/${DIR_PATH}/)

    file (GLOB SOURCE_FILES 
	    ${PROJECT_SOURCE_DIR}/${DIR_PATH}/*	
    )
    foreach (FILE ${SOURCE_FILES})
        string (FIND ${FILE} ${EXCLUDE_DIR} EXCLUDE_DIR_FOUND)
        if (NOT ${EXCLUDE_DIR_FOUND} EQUAL -1)
            string(REPLACE ${EXCLUDE_DIR} "" REPLACED_PATH ${FILE})
            message("new path " ${CMAKE_BINARY_DIR}/${DIR_PATH}/${REPLACED_PATH})
            configure_file(${DIR_PATH}/${REPLACED_PATH} ${CMAKE_BINARY_DIR}/${DIR_PATH}/${REPLACED_PATH} COPYONLY)
        endif ()
    endforeach(FILE)
endmacro()

macro(MOVE_DLLS_FROM_FOLDER SRC_PATH TGT_PATH)
    set (EXCLUDE_DIR ${SRC_PATH})

    file (GLOB SOURCE_FILES 
	    ${SRC_PATH}/*.dll
    )
    foreach (FILE ${SOURCE_FILES})
        message("old path " ${FILE})
        string (FIND ${FILE} ${EXCLUDE_DIR} EXCLUDE_DIR_FOUND)
        if (NOT ${EXCLUDE_DIR_FOUND} EQUAL -1)
            string(REPLACE ${EXCLUDE_DIR} "" REPLACED_PATH ${FILE})
            #message("antes " ${REPLACED_PATH})
            string(REPLACE "/" "" REPLACED_PATH ${REPLACED_PATH})
            #message("depois " ${TGT_PATH}/${REPLACED_PATH})
            file(RENAME ${FILE} ${TGT_PATH}/${REPLACED_PATH})
            #configure_file(${DIR_PATH}/${REPLACED_PATH} ${CMAKE_BINARY_DIR}/${DIR_PATH}/${REPLACED_PATH} COPYONLY)
        endif ()
    endforeach(FILE)
endmacro()
    