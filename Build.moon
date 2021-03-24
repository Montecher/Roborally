var NAME: 'app'

public var CXX: 'g++'
public var LD: 'g++'
public var RM: {'rm', '-f'}

var CFLAGS: {'-Wall', '-Wextra', '-g', '--std=c++14', '-pedantic'}
var LDFLAGS: {'-lpthread'}

var MODULES: {'board', 'Graph', 'test', 'MoveTree'}

var SOURCES: _.patsubst MODULES, '%', 'src/%.cpp'
var OBJS:    _.patsubst MODULES, '%', 'build/%.o'
var BINARY:  "out/#{NAME}"

with public default target 'all'
	\depends BINARY

with public target 'run'
	\depends BINARY
	\fn => _.cmd "./#{BINARY}", 'appdata/board.txt'

with public target 'clean'
	\fn => _.cmd RM, OBJS, DEPS

with public target 'mrproper'
	\after 'clean'
	\fn => _.cmd RM, BINARY

with target BINARY
	\depends OBJS
	\produces BINARY
	\fn => _.cmd LD, @infiles, '-o', @out

with target OBJS, pattern: 'build/%.o'
	\depends 'src/%.cpp'
	\depends => _.cdeps[CXX] CFLAGS, @infile
	\produces 'build/%.o'
	\fn => _.cmd CXX, CFLAGS, '-c', @infile, '-o', @out
