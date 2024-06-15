# Минимальная версия CMake, необходимая для сборки
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(MyGameProject)                                            #!

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)                                        #!
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Установка директорий для заголовочных файлов и исходников
include_directories(include)
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

# Путь к папке с SFML
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/lib/SFML")

#set(SFML_DIR "d:/university/anp/MyGameProject/lib/sfml/lib/cmake/SFML")

# Установка пути к заголовочным файлам SFML
include_directories(${SFML_ROOT}/include)

# Установка пути к библиотекам SFML
link_libraries(${CMAKE_SOURCE_DIR}/lib/libsfiles)

# Поиск библиотек SFML
#find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)



#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# Сбор всех исходных файлов проекта
file(GLOB SOURCES "src/*.cpp")                                     #!

# Добавление исполняемого файла
add_executable(MyGameExecutable ${SOURCES})
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

# Подключение библиотек SFML
target_link_libraries(MyGameExecutable ${CMAKE_SOURCE_DIR}/lib/libsfiles/sfml-graphics.lib) 
target_link_libraries(MyGameExecutable ${CMAKE_SOURCE_DIR}/lib/libsfiles/sfml-window.lib)
target_link_libraries(MyGameExecutable ${CMAKE_SOURCE_DIR}/lib/libsfiles/sfml-system.lib)

# Копирование ассетов в директорию сборки
#add_custom_command(
#    TARGET MyGameExecutable POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_directory
#    ${CMAKE_SOURCE_DIR}/assets/fonts $<TARGET_FILE_DIR:MyGameExecutable>/assets/fonts
#)

#add_custom_command(
#    TARGET MyGameExecutable POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_directory
#    ${CMAKE_SOURCE_DIR}/assets/images $<TARGET_FILE_DIR:MyGameExecutable>/assets/images
#)
