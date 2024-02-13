add_executable(App
  main.cpp
  UserInactivityTime.h UserInactivityTime.cpp
  MyRequest.h MyRequest.cpp
)

target_link_libraries(App PRIVATE
 Qt${QT_VERSION_MAJOR}::Core
 Qt6::Network)

include(GNUInstallDirs)

install(TARGETS App
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
