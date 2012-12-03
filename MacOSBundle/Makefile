bundle:
	mkdir -p out/Release
	cp -rf src/Cubes out/Release/Cubes.app
	mkdir -p out/Release/Cubes.app/Contents/Resources/
	mkdir -p out/Release/Cubes.app/Contents/MacOS/
	cp -rf ../sfmlcube/res out/Release/Cubes.app/Contents/Resources/
	cp -rf ../sfmlcube/OSX-Release/sfmlcube out/Release/Cubes.app/Contents/MacOS/
	cp -rf ../icon/Cubes.icns out/Release/Cubes.app/Contents/Resources/

	mkdir -p out/Debug
	cp -rf src/Cubes out/Debug/Cubes.app
	mkdir -p out/Debug/Cubes.app/Contents/Resources/
	mkdir -p out/Debug/Cubes.app/Contents/MacOS/
	cp -rf ../sfmlcube/res out/Debug/Cubes.app/Contents/Resources/
	cp -rf ../sfmlcube/OSX-Debug/sfmlcube out/Debug/Cubes.app/Contents/MacOS/
	cp -rf ../icon/Cubes.icns out/Debug/Cubes.app/Contents/Resources/

clean:
	rm -rf out