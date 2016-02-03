set(addresseditor_SRCS
  main.cpp  
)

add_executable(addresseditortest ${addresseditor_SRCS})

target_link_libraries(addresseditortest
  KF5::I18n
  Qt5::Widgets
)

