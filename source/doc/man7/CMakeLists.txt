cmake_minimum_required (VERSION 3.8)

file (GLOB DOC_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.7.adoc")
set (DOC_FILES)

foreach (SRC ${DOC_SOURCES})
  string (REPLACE ".adoc" "" OUTPUT_FILE_NAME "${SRC}")
  string (REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}" OUTPUT_FILE_NAME "${OUTPUT_FILE_NAME}")

  add_custom_command (OUTPUT "${OUTPUT_FILE_NAME}"
                      COMMAND ${ASCIIDOCTOR_EXECUTABLE} -b manpage ${ASCIIDOCTOR_OPTIONS} ${SRC} -o ${OUTPUT_FILE_NAME}
                      DEPENDS "${SRC}")

  set (DOC_FILES ${DOC_FILES} "${OUTPUT_FILE_NAME}")
endforeach (SRC)

add_custom_target (man7 DEPENDS ${DOC_FILES})

install (FILES ${DOC_FILES} DESTINATION ${TIMEW_MAN7DIR})
