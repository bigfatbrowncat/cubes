TAG := $(shell git describe --abbrev=0 --tags)
#TAG := 0.0.12

all: setup

setup:
	mkdir -p out/Release
	makensis -NOCD -DVERSION=${TAG} -DBUILD_TYPE=Release -- Cubes.nsi 
	
	mkdir -p out/Debug
	makensis -NOCD -DVERSION=${TAG} -DBUILD_TYPE=Debug -- Cubes.nsi 