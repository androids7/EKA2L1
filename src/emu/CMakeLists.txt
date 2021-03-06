if (WIN32)
    add_definitions(-DNOMINMAX)
    message("NOMINMAX")
        
    if (MSVC AND ENABLE_SEH_HANDLER)
        # Replace SEH flag if there is one
        string (REGEX REPLACE "\/(EH).+" "\/EHa" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHa")
    endif()
endif()

# Many of our code are optimized to utilize offsetof.
# But it complains a lot with non-POD type, that's not what we want, so disable the warn flag.
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof")
endif()

add_subdirectory(arm)
add_subdirectory(common)
add_subdirectory(console)
add_subdirectory(debugger)
add_subdirectory(disasm)
add_subdirectory(drivers)
add_subdirectory(epoc)
add_subdirectory(gdbstub)
add_subdirectory(hle)
add_subdirectory(manager)

if (ENABLE_SCRIPTING_ABILITY)
    add_subdirectory(scripting)
endif()
