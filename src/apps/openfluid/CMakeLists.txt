
ADD_EXECUTABLE(${OPENFLUID_CMD_APP}
               DefaultIOListener.hpp 
               DefaultBuddiesListener.hpp 
               DefaultMachineListener.hpp VerboseMachineListener.hpp 
               OpenFLUID.cpp OpenFLUID.hpp             
               main.cpp
              )
SET_TARGET_PROPERTIES(${OPENFLUID_CMD_APP} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OFBUILD_DIST_BIN_DIR}")

TARGET_LINK_LIBRARIES(${OPENFLUID_CMD_APP}                       
                      openfluid-base
                      openfluid-buddies
                      openfluid-core
                      openfluid-machine
                      openfluid-tools
                      openfluid-fluidx
                     )


FILE(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/${OPENFLUID_CMD_APP}_path.txt" CONTENT $<TARGET_FILE:${OPENFLUID_CMD_APP}>)


INSTALL(TARGETS ${OPENFLUID_CMD_APP}
        RUNTIME DESTINATION ${OFBUILD_BIN_INSTALL_PATH})

       
      

