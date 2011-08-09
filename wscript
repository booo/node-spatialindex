import Options, Utils
from os import unlink, symlink, popen
from os.path import exists

srcdir = '.'
blddir = 'build'
VERSION = '0.0.1'

def set_options(opt):
  opt.tool_options('compiler_cxx')

def configure(conf):
  conf.check_tool('compiler_cxx')
  conf.check_tool('node_addon')

  conf.env.append_value("LIBPATH_SPATIALINDEX", "/usr/lib")
  conf.env.append_value("LIBPATH_SPATIALINDEX", "/usr/local/lib")
  conf.env.append_value("LIBPATH_SPATIALINDEX", "/opt/local/lib")
  conf.env.append_value("LIB_SPATIALINDEX", "spatialindex")
  conf.env.append_value("CPPPATH_SPATIALINDEX", "/usr/include")
  conf.env.append_value("CPPPATH_SPATIALINDEX", "/usr/local/include")
  conf.env.append_value("CPPPATH_SPATIALINDEX", "/opt/local/include")

def build(bld):
  obj = bld.new_task_gen('cxx', 'shlib', 'node_addon')
  obj.cxxflags = ["-g", "-D_LARGEFILE_SOURCE", "-Wall"]
  obj.target = 'spatialindex'
  obj.source = "src/binding.cpp"
  #obj.uselib = ""