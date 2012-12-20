TAG := $(shell git describe --abbrev=0 --tags)
CUBES=Cubes\ $(TAG)

release:
	mkdir -p out/Release/$(CUBES)
	cp -rf src/Cubes out/Release/$(CUBES)/Cubes.app
	mkdir -p out/Release/$(CUBES)/Cubes.app/Contents/Resources/
	mkdir -p out/Release/$(CUBES)/Cubes.app/Contents/MacOS/
	cp -rf ../sfmlcube/res out/Release/$(CUBES)/Cubes.app/Contents/Resources/
	cp -rf ../sfmlcube/OSX-Release/sfmlcube out/Release/$(CUBES)/Cubes.app/Contents/MacOS/
	cp -rf ../icon/Cubes.icns out/Release/$(CUBES)/Cubes.app/Contents/Resources/
	hdiutil create out/Release/Cubes-$(TAG)-darwin-universal.dmg -srcfolder out/Release/$(CUBES) -ov

debug:
	mkdir -p out/Debug/$(CUBES)
	cp -rf src/Cubes out/Debug/$(CUBES)/Cubes.app
	mkdir -p out/Debug/$(CUBES)/Cubes.app/Contents/Resources/
	mkdir -p out/Debug/$(CUBES)/Cubes.app/Contents/MacOS/
	cp -rf ../sfmlcube/res out/Debug/$(CUBES)/Cubes.app/Contents/Resources/
	cp -rf ../sfmlcube/OSX-Debug/sfmlcube out/Debug/$(CUBES)/Cubes.app/Contents/MacOS/
	cp -rf ../icon/Cubes.icns out/Debug/$(CUBES)/Cubes.app/Contents/Resources/
	hdiutil create out/Debug/Cubes-$(TAG)-darwin-universal.dmg -srcfolder out/Debug/$(CUBES) -ov


clean:
	rm -rf out