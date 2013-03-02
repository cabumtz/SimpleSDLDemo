## -*- Makefile -*-
##
## User: carlos
## Time: 21/06/2012 07:41:00 AM
## Makefile created by Oracle Solaris Studio.
##
## This file is generated automatically.
##


## Target: all
all: build/Makefile
	(cd build ; make)

## Regenerate Build Makefile
build/Makefile:
	(rm -rf build ; mkdir build ; cd build ; cmake -G "Unix Makefiles" ../ )

## Run
all-run: all
	(cd build ; make run)




#### Clean target deletes all generated files ####
clean:
	(cd build ; make clean)

build-dir-clean:
	(rm -rf build)

dist-clean: clean build-dir-clean



# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-i386-Linux

