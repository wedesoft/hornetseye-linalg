require 'rake'

PKG_NAME = 'hornetseye-linalg'
PKG_VERSION = '1.0.5'
CFG = RbConfig::CONFIG
CXX = ENV[ 'CXX' ] || 'g++'
RB_FILES = ['config.rb'] + FileList[ 'lib/**/*.rb' ]
CC_FILES = FileList[ 'ext/*.cc' ]
HH_FILES = FileList[ 'ext/*.hh' ] + FileList[ 'ext/*.tcc' ]
TC_FILES = FileList[ 'test/tc_*.rb' ]
TS_FILES = FileList[ 'test/ts_*.rb' ]
SO_FILE = "ext/#{PKG_NAME.tr '\-', '_'}.#{CFG[ 'DLEXT' ]}"
PKG_FILES = [ 'Rakefile', 'README.md', 'COPYING', '.document' ] +
            RB_FILES + CC_FILES + HH_FILES + TS_FILES + TC_FILES
BIN_FILES = [ 'README.md', 'COPYING', '.document', SO_FILE ] +
            RB_FILES + TS_FILES + TC_FILES
SUMMARY = %q{Linalg integration for Hornetseye}
DESCRIPTION = %q{This Ruby extension provides conversion from Hornetseye::MultiArray to Linalg::DMatrix and vice versa.}
LICENSE = 'GPL-3+'
AUTHOR = %q{Jan Wedekind}
EMAIL = %q{jan@wedesoft.de}
HOMEPAGE = %q{http://wedesoft.github.io/hornetseye-linalg/}
