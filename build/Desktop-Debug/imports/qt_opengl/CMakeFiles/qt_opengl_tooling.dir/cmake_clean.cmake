file(REMOVE_RECURSE
  "../../qml/qt_opengl/Constants.qml"
  "../../qml/qt_opengl/DirectoryFontLoader.qml"
  "../../qml/qt_opengl/EventListModel.qml"
  "../../qml/qt_opengl/EventListSimulator.qml"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/qt_opengl_tooling.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
