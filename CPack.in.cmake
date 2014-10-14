SET(OPENFLUID_PACKAGE_TITLE "OpenFLUID")
SET(OPENFLUID_PACKAGE_SUMMARY "OpenFLUID software environment for modelling landscapes functionning")
SET(OPENFLUID_PACKAGE_DESCRIPTION "This package contains the OpenFLUID software environment for modelling landscapes functionning, mainly for spatial fluxes modelling. It also includes API and tools for development.")
SET(OPENFLUID_PACKAGE_LICENSE "GPLv3")

SET(CPACK_CMAKE_GENERATOR "${CMAKE_GENERATOR}")

CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/resources/packaging/readme.txt ${CMAKE_BINARY_DIR}/readme.txt COPYONLY)
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/COPYING ${CMAKE_BINARY_DIR}/copyright.txt COPYONLY)
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/resources/packaging/welcome.txt ${CMAKE_BINARY_DIR}/welcome.txt COPYONLY)


SET(CPACK_INSTALL_CMAKE_PROJECTS "${PROJECT_BINARY_DIR};${PROJECT_NAME};ALL;/") 

SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_BINARY_DIR}/copyright.txt")
SET(CPACK_RESOURCE_FILE_README "${CMAKE_BINARY_DIR}/readme.txt")
SET(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_BINARY_DIR}/welcome.txt")  

SET(CPACK_PACKAGE_NAME "openfluid")
SET(CPACK_PACKAGE_VERSION "${FULL_VERSION}")
SET(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
SET(CPACK_PACKAGE_CONTACT "Jean-Christophe Fabre <fabrejc@supagro.inra.fr>")
SET(CPACK_PACKAGE_VENDOR "LISAH (INRA-IRD-SupAgro)")
SET(CPACK_PACKAGE_DESCRIPTION "${OPENFLUID_PACKAGE_TITLE}.\n ${OPENFLUID_PACKAGE_DESCRIPTION}")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${OPENFLUID_PACKAGE_SUMMARY}")


##### Windows
IF(WIN32)

  SET(CPACK_GENERATOR "NSIS")
  SET(CPACK_SOURCE_GENERATOR "ZIP")
  SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/resources/packaging;${CMAKE_MODULE_PATH}")        

  SET(CPACK_PACKAGE_INSTALL_DIRECTORY "OpenFLUID-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
  
  SET(CPACK_PACKAGE_NAME "OpenFLUID")
  
  SET(CPACK_NSIS_DISPLAY_NAME "OpenFLUID")
  SET(CPACK_NSIS_HELP_LINK "http://www.openfluid-project.org/")
  SET(CPACK_NSIS_URL_INFO_ABOUT "http://www.openfluid-project.org/")
  SET(CPACK_NSIS_CONTACT "OpenFLUID contact <contact@openfluid-project.org>")  
  SET(CPACK_PACKAGE_ICON "${PROJECT_SOURCE_DIR}/resources/packaging\\\\OF_logo.bmp")  
  SET(CPACK_NSIS_MENU_LINKS 
      "http://www.openfluid-project.org/" "OpenFLUID web site"
      "http://www.openfluid-project.org/community/" "OpenFLUID community site")
  SET(CPACK_PACKAGE_EXECUTABLES "openfluid-builder" "OpenFLUID-Builder")   
   
  SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "${CPACK_PACKAGE_NAME} ${FULL_VERSION}")
  SET(CPACK_NSIS_MODIFY_PATH ON)

  # This packaging includes Boost libs and includes, Qt libs, GEOS libs and GDAL libs
  # It requires the SUPPORT_DIR and QT5_PLUGINS_DIR environment variables

  FIND_PATH(QT_MINGW_BINARY_DIR qt5core.dll)
  
  FILE(TO_CMAKE_PATH "${Boost_LIBRARY_DIRS}" BOOST_LIBRARYDIR_MOD)
  FILE(TO_CMAKE_PATH "${Boost_INCLUDE_DIR}" BOOST_INCLUDEDIR_MOD)  
  FILE(TO_CMAKE_PATH "$ENV{SUPPORT_DIR}" SUPPORT_DIR_MOD)
  FILE(TO_CMAKE_PATH "$ENV{SUPPORT_DIR}/bin" SUPPORT_BINDIR_MOD)
  FILE(TO_CMAKE_PATH "$ENV{SUPPORT_DIR}/lib" SUPPORT_LIBDIR_MOD)
  FILE(TO_CMAKE_PATH "$ENV{QT5_PLUGINS_DIR}" QT5_PLUGINS_DIR_MOD)  
  FILE(TO_CMAKE_PATH "${QT_MINGW_BINARY_DIR}" QT_MINGW_BINARY_DIR_MOD)
 
  # support libraries
  IF(NOT SUPPORT_DIR_MOD)
    MESSAGE(FATAL_ERROR "environment variable SUPPORT_DIR is not set!")
  ENDIF()
  
  # QT5 plugins
  IF(NOT QT5_PLUGINS_DIR_MOD)
    MESSAGE(FATAL_ERROR "environment variable QT5_PLUGINS_DIR is not set!")
  ENDIF()
 
   # MinGW from Qt
  INSTALL(FILES "${QT_MINGW_BINARY_DIR_MOD}/libgcc_s_dw2-1.dll" DESTINATION ${BIN_INSTALL_PATH})
  INSTALL(FILES "${QT_MINGW_BINARY_DIR_MOD}/libstdc++-6.dll" DESTINATION ${BIN_INSTALL_PATH})
  INSTALL(FILES "${QT_MINGW_BINARY_DIR_MOD}/libwinpthread-1.dll" DESTINATION ${BIN_INSTALL_PATH})
 
  # Boost
  INSTALL(DIRECTORY "${BOOST_INCLUDEDIR_MOD}/boost" DESTINATION include)
  INSTALL(DIRECTORY "${BOOST_LIBRARYDIR_MOD}/" DESTINATION ${BIN_INSTALL_PATH} FILES_MATCHING PATTERN "libboost_*.dll") 
  INSTALL(DIRECTORY "${BOOST_LIBRARYDIR_MOD}/" DESTINATION ${LIB_INSTALL_PATH} FILES_MATCHING PATTERN "libboost_*.a")  
  
  # GDAL  
  INSTALL(DIRECTORY "${SUPPORT_BINDIR_MOD}/" DESTINATION ${BIN_INSTALL_PATH} FILES_MATCHING PATTERN "libgdal*.dll") 
  INSTALL(DIRECTORY "${SUPPORT_LIBDIR_MOD}/" DESTINATION ${BIN_INSTALL_PATH} FILES_MATCHING PATTERN "libgdal*.dll") 
  
  # GEOS
  IF(OPENFLUID_ENABLE_LANDR)
    INSTALL(DIRECTORY "${SUPPORT_BINDIR_MOD}/" DESTINATION ${BIN_INSTALL_PATH} FILES_MATCHING PATTERN "libgeos*.dll") 
    INSTALL(DIRECTORY "${SUPPORT_LIBDIR_MOD}/" DESTINATION ${BIN_INSTALL_PATH} FILES_MATCHING PATTERN "libgeos*.dll") 
  ENDIF()
  
  # Qt
  INSTALL(FILES ${QT_MINGW_BINARY_DIR_MOD}/qt5core.dll DESTINATION ${BIN_INSTALL_PATH})
  INSTALL(FILES ${QT_MINGW_BINARY_DIR_MOD}/qt5widgets.dll DESTINATION ${BIN_INSTALL_PATH})
  INSTALL(FILES ${QT_MINGW_BINARY_DIR_MOD}/qt5gui.dll DESTINATION ${BIN_INSTALL_PATH})
  INSTALL(FILES ${QT_MINGW_BINARY_DIR_MOD}/qt5svg.dll DESTINATION ${BIN_INSTALL_PATH})
  INSTALL(FILES ${QT_MINGW_BINARY_DIR_MOD}/qt5declarative.dll DESTINATION ${BIN_INSTALL_PATH})
  INSTALL(FILES ${QT_MINGW_BINARY_DIR_MOD}/qt5xml.dll DESTINATION ${BIN_INSTALL_PATH})
  INSTALL(FILES ${QT_MINGW_BINARY_DIR_MOD}/qt5concurrent.dll DESTINATION ${BIN_INSTALL_PATH})
  INSTALL(FILES ${QT_MINGW_BINARY_DIR_MOD}/qt5network.dll DESTINATION ${BIN_INSTALL_PATH})
  INSTALL(FILES ${QT_MINGW_BINARY_DIR_MOD}/icuin51.dll DESTINATION ${BIN_INSTALL_PATH})
  INSTALL(FILES ${QT_MINGW_BINARY_DIR_MOD}/icuuc51.dll DESTINATION ${BIN_INSTALL_PATH})
  INSTALL(FILES ${QT_MINGW_BINARY_DIR_MOD}/icudt51.dll DESTINATION ${BIN_INSTALL_PATH})
  INSTALL(FILES "${QT5_PLUGINS_DIR_MOD}/platforms/qwindows.dll" DESTINATION ${BIN_INSTALL_PATH}/platforms/)

ENDIF(WIN32)

##### UNIX
IF(UNIX AND NOT APPLE AND NOT CYGWIN)
  SET(CPACK_SOURCE_GENERATOR "TGZ")
  
  IF(OF_DISTRO_IS_UBUNTU)  
    SET(CPACK_GENERATOR "DEB")      
    SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}-dev, libboost-date-time${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}-dev, libboost-filesystem${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}-dev, libboost-math${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}-dev, libboost-program-options${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}-dev, libboost-regex${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}-dev, libboost-iostreams${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}-dev, libboost-test${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}-dev, libqt4-dev (>= 4.8.0), libgdal1-dev, gcc, g++, cmake (>= 2.8.9), gnuplot (>= 4.2), p7zip-full, graphviz")    
    IF(OPENFLUID_ENABLE_LANDR)
      IF(${OF_DISTRO_VERSION} VERSION_GREATER "12.04")
        SET(CPACK_DEBIAN_PACKAGE_DEPENDS "${CPACK_DEBIAN_PACKAGE_DEPENDS}, libgeos++-dev (>= 3.3.0)")
      ELSE()
        SET(CPACK_DEBIAN_PACKAGE_DEPENDS "${CPACK_DEBIAN_PACKAGE_DEPENDS}, libgeos-dev (>= 3.3.0)")    
      ENDIF()
    ENDIF()  
    SET(CPACK_DEBIAN_PACKAGE_RECOMMENDS "gnuplot (>= 4.2), p7zip-full, graphviz") 
    SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "${OF_SYSTEM_ARCH}")
    SET(CPACK_DEBIAN_PACKAGE_SECTION "science")
    SET(CPACK_DEBIAN_PACKAGE_PRIORITY "extra")
    SET(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${OF_DISTRO_CODE}_${OF_SYSTEM_ARCH}")
  ENDIF(OF_DISTRO_IS_UBUNTU)
  
  IF(OF_DISTRO_IS_CENTOS)  
    SET(CPACK_GENERATOR "RPM") 
    SET(CPACK_RPM_PACKAGE_REQUIRES "gcc-c++, boost-devel >= 1.40, gdal-devel, qt47-devel")
    IF(OPENFLUID_ENABLE_LANDR)
      SET(CPACK_RPM_PACKAGE_REQUIRES "${CPACK_RPM_PACKAGE_REQUIRES}, libgeos-devel >= 3.3.0")
    ENDIF()  
    SET(CPACK_RPM_PACKAGE_ARCHITECTURE "${OF_SYSTEM_ARCH}")
    SET(CPACK_PACKAGE_DESCRIPTION "This package contains the OpenFLUID software environment for modelling landscapes functionning, mainly oriented on spatial fluxes modelling. It also includes API and tools for development.")
    SET(CPACK_RPM_PACKAGE_DESCRIPTION "${OPENFLUID_PACKAGE_DESCRIPTION}")
    SET(CPACK_RPM_PACKAGE_SUMMARY "${OPENFLUID_PACKAGE_SUMMARY}")
    SET(CPACK_RPM_PACKAGE_GROUP "science")
    SET(CPACK_RPM_PACKAGE_LICENSE "${OPENFLUID_PACKAGE_LICENSE}")
    SET(CPACK_RPM_PACKAGE_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
    STRING(SUBSTRING ${OF_DISTRO_VERSION} 0 1 CENTOS_EL_VERSION)
    SET(CPACK_RPM_PACKAGE_RELEASE "1.el${CENTOS_EL_VERSION}")
    IF(VERSION_STATUS)
      SET(CPACK_RPM_PACKAGE_RELEASE "0.${VERSION_STATUS}.el${CENTOS_EL_VERSION}")
    ENDIF(VERSION_STATUS)    
    SET(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_RPM_PACKAGE_VERSION}-${CPACK_RPM_PACKAGE_RELEASE}.${OF_SYSTEM_ARCH}")
  ENDIF(OF_DISTRO_IS_CENTOS)
ENDIF(UNIX AND NOT APPLE AND NOT CYGWIN)

##### Apple
IF(APPLE)
  SET(CPACK_GENERATOR "OSXX11;TGZ;PackageMaker")
  SET(CPACK_SOURCE_GENERATOR "TGZ")  
ENDIF(APPLE)



SET(CPACK_SOURCE_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_src")
SET(CPACK_SOURCE_IGNORE_FILES "${CMAKE_BINARY_DIR}/*;/\\\\.svn/;"/\\\\..+$"")

INCLUDE(CPack)

