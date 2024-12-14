cmake_minimum_required(VERSION 3.10)

project(P1-RayToy VERSION 1.0 LANGUAGES CXX)

# Configuració de Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Configuració de C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
cmake_policy(SET CMP0100 NEW)
# Make this a GUI application on Windows
if(WIN32)
    set(CMAKE_WIN32_EXECUTABLE ON)
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}
    "./VW"
    "./TEMPORALVW"
    "./DataService"
    "./GUI"
    "./Render"
    "./Rays"
    "./VW/Lights"
    "./VW/Materials"
    "./VW/Objects"
    "./VW/TG"
    )


######################
# TODO: Set your QT5 installation path here (check following options)
######################
# Aules UB
#set(QT5_INSTALLATION_PATH "/opt/Qt/5.9.1/gcc_64")
# Ubuntu 22.04
# set(QT5_INSTALLATION_PATH "/opt/Qt5.12.12/5.12.12/gcc_64")
# MAC OS (change your username!)
#set(QT5_INSTALLATION_PATH "/Users/anna/Qt15/5.15.2/clang_64")
# Diego
# set(QT5_INSTALLATION_PATH "/usr/lib/x86_64-linux-gnu")
# Kevin
#set(QT5_INSTALLATION_PATH "C:/Qt/Qt5.12.12/5.12.12/mingw73_64")
# Pol
set(QT5_INSTALLATION_PATH "/home/polg24/Qt5.12.12/5.12.12/gcc_64")
######################


# Add QT to CMAKE_PREFIX_PATH
set(CMAKE_PREFIX_PATH ${QT5_INSTALLATION_PATH} ${CMAKE_PREFIX_PATH})
# Ruta al ejecutable moc
set(CMAKE_AUTOMOC_MOC_EXECUTABLE ${QT5_INSTALLATION_PATH}"/bin")
# Ruta al ejecutable uic
set(CMAKE_AUTOUIC_SEARCH_PATHS ${QT5_INSTALLATION_PATH}"/bin")

# Add CMake QT path
set(Qt5_DIR ${QT5_INSTALLATION_PATH}"/lib/cmake/Qt5/")


# Troba els mòduls de Qt necessaris
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

if (${Qt5_FOUND})
    message("Found Qt " ${Qt5_VERSION})
else()
    message("Couldn't find Qt")
endif()




# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_VERBOSE_MAKEFILE ON)

# specify resource file names here, required for QML
qt5_add_resources(qrc resources.qrc)

# Afegir els fitxers font
set(SOURCES
    AppMain.cpp
    Controller.cpp
    DataService/Output.cpp
    DataService/SetUp.cpp
    GUI/Builder.cpp
    GUI/CameraMenu.cpp
    GUI/Label.cpp
    GUI/MainWindow.cpp
    Render/Camera.cpp
    Render/AOShading.cpp
    Render/BlinnPhongShading.cpp
    Render/BlinnPhongPenombresShading.cpp
    Render/CelShading.cpp
    Render/ColorShading.cpp
    Render/NormalShading.cpp
    Render/NColorShading.cpp
    Render/RayTracing.cpp
    Render/ShadingFactory.cpp
    Render/ShadingStrategy.cpp
    Scene.cpp
    SceneFactory.cpp
    VW/Lights/Light.cpp
    VW/Lights/LightFactory.cpp
    VW/Lights/PointLight.cpp
    VW/Lights/AreaLight.cpp
    VW/Materials/Lambertian.cpp
    VW/Materials/Metal.cpp
    VW/Materials/Material.cpp
    VW/Materials/MaterialFactory.cpp
    VW/Materials/MaterialTextura.cpp
    VW/Materials/Texture.cpp
    VW/Materials/Transparent.cpp
    VW/Objects/Box.cpp
    VW/Objects/EnvironmentalSphere.cpp
    VW/Objects/Face.cpp
    VW/Objects/FittedPlane.cpp
    VW/Objects/Mesh.cpp
    VW/Objects/Object.cpp
    VW/Objects/ObjectFactory.cpp
    VW/Objects/Plane.cpp
    VW/Objects/Sphere.cpp
    VW/Objects/Triangle.cpp
    VW/SceneFactoryVirtual.cpp
    TemporalVW/SceneFactoryTemporal.cpp
    VW/TG/TG.cpp
    VW/TG/TranslateTG.cpp
    VW/TG/RotateTG.cpp
    VW/TG/ScaleTG.cpp
    TemporalVW/Animation.cpp
)

# Afegir els fitxers de capçalera
set(HEADERS
    Controller.hh
    DataService/Output.hh
    DataService/Serializable.hh
    DataService/SetUp.hh
    GUI/Builder.hh
    GUI/CameraMenu.hh
    GUI/Label.hh
    GUI/MainWindow.hh
    Rays/HitRecord.hh
    Rays/Hittable.hh
    Rays/Ray.hh
    Render/Camera.hh
    Render/AOShading.hh
    Render/BlinnPhongShading.hh
    Render/BlinnPhongPenombresShading.hh
    Render/ColorShading.hh
    Render/CelShading.hh
    Render/NormalShading.hh
    Render/NColorShading.hh
    Render/RayTracing.hh
    Render/ShadingFactory.hh
    Render/ShadingStrategy.hh
    Scene.hh
    SceneFactory.hh
    VW/Lights/Light.hh
    VW/Lights/LightFactory.hh
    VW/Lights/PointLight.hh
    VW/Lights/AreaLight.hh
    VW/Materials/Lambertian.hh
    VW/Materials/Metal.hh
    VW/Materials/Material.hh
    VW/Materials/MaterialFactory.hh
    VW/Materials/MaterialTextura.hh
    VW/Materials/Texture.hh
    VW/Materials/Transparent.hh
    VW/Objects/Box.hh
    VW/Objects/EnvironmentalSphere.hh
    VW/Objects/Face.hh
    VW/Objects/FittedPlane.hh
    VW/Objects/Mesh.hh
    VW/Objects/Object.hh
    VW/Objects/ObjectFactory.hh
    VW/Objects/Plane.hh
    VW/Objects/Sphere.hh
    VW/Objects/Triangle.hh
    VW/SceneFactoryVirtual.hh
    VW/TG/TG.hh
    VW/TG/TranslateTG.hh
    VW/TG/RotateTG.hh
    VW/TG/ScaleTG.hh
    TemporalVW/Animation.hh
    TemporalVW/SceneFactoryTemporal.hh
    glm/core/_detail.hpp
    glm/core/_fixes.hpp
    glm/core/_swizzle.hpp
    glm/core/_swizzle_func.hpp
    glm/core/_vectorize.hpp
    glm/core/func_common.hpp
    glm/core/func_common.inl
    glm/core/func_exponential.hpp
    glm/core/func_exponential.inl
    glm/core/func_geometric.hpp
    glm/core/func_geometric.inl
    glm/core/func_integer.hpp
    glm/core/func_integer.inl
    glm/core/func_matrix.hpp
    glm/core/func_matrix.inl
    glm/core/func_noise.hpp
    glm/core/func_noise.inl
    glm/core/func_packing.hpp
    glm/core/func_packing.inl
    glm/core/func_trigonometric.hpp
    glm/core/func_trigonometric.inl
    glm/core/func_vector_relational.hpp
    glm/core/func_vector_relational.inl
    glm/core/hint.hpp
    glm/core/intrinsic_common.hpp
    glm/core/intrinsic_common.inl
    glm/core/intrinsic_exponential.hpp
    glm/core/intrinsic_exponential.inl
    glm/core/intrinsic_geometric.hpp
    glm/core/intrinsic_geometric.inl
    glm/core/intrinsic_matrix.hpp
    glm/core/intrinsic_matrix.inl
    glm/core/intrinsic_trigonometric.hpp
    glm/core/intrinsic_trigonometric.inl
    glm/core/intrinsic_vector_relational.hpp
    glm/core/intrinsic_vector_relational.inl
    glm/core/setup.hpp
    glm/core/type.hpp
    glm/core/type_float.hpp
    glm/core/type_gentype.hpp
    glm/core/type_gentype.inl
    glm/core/type_half.hpp
    glm/core/type_half.inl
    glm/core/type_int.hpp
    glm/core/type_mat.hpp
    glm/core/type_mat.inl
    glm/core/type_mat2x2.hpp
    glm/core/type_mat2x2.inl
    glm/core/type_mat2x3.hpp
    glm/core/type_mat2x3.inl
)

# Add your UI files
set(FORMS
    GUI/about.ui
    GUI/camera.ui
    GUI/main.ui
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${FORMS} ${qrc})

# Link against Qt5 libraries
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets )
