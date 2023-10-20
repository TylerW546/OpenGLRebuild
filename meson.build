project('OpenGL', ['cpp','c'],
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++14'])

# PUT glfw3.dll IN THE BUILD DIRECTORY
# USE https://mesonbuild.com/Build-targets.html FOR DOING THIS AUTOMATICALLY
# https://mesonbuild.com/Reference-manual_builtin_meson.html

project_dir = meson.current_source_dir()
build_dir = meson.current_build_dir()

inc = [include_directories('Libraries/include'), include_directories('include')]

cpp = meson.get_compiler('cpp')
c = meson.get_compiler('c')

source_files = ['main.cpp', 'glad.c', 'source/Game.cpp', 'source/Shader.cpp', 'source/Entity.cpp', 'source/Sprite.cpp',
    'source/Window.cpp', 'source/Texture.cpp', 'source/ResourceManager.cpp']

deps = []

host_system = host_machine.system()
if host_system == 'windows'
  # Undefined references without this one
  deps += cpp.find_library('glfw3dll', dirs : project_dir / 'Libraries/lib', static : true)
  deps += cpp.find_library('glfw3', dirs : project_dir / 'Libraries/lib', static : true)

elif host_system == 'darwin'
  deps += cpp.find_library('libglfw.3.3', dirs : project_dir + '/Libraries/lib', static : false)

elif host_system == 'linux'
  deps += dependency('GL')
  deps += cpp.find_library('glfw', dirs : project_dir / 'Libraries/lib')
endif

install_data(project_dir / 'Libraries/lib/glfw3.dll')
install_subdir(project_dir / 'Libraries', install_dir : '')

install_subdir(project_dir / 'shaders', install_dir: build_dir, strip_directory : false)
install_subdir(project_dir / 'sprites', install_dir: build_dir, strip_directory : false)
install_data(project_dir / 'Libraries/lib/glfw3.dll', install_dir: build_dir)

subdir('include')
#subdir('dependencies')
subdir('source')

exe = executable('OpenGL', source_files,
    include_directories : inc,
    dependencies : deps,
    install : true)

pkg_mod = import('pkgconfig')
pkg_mod.generate(libraries : glBase,
                 version : '1.0.0',
                 name : 'glBase',
                 filebase : 'glBase',
                 description : 'A base program for using OpenGL.')

                 