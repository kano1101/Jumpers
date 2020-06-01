CC = clang++
LD = clang++
CCFLAGS = -Wall -Wextra -c -std=c++2a
LDFLAGS = -lglew -lglfw -lglpng -lm -framework OpenGL

SourceDir = src
BuildDir = build
BinDir = bin
ProductName = Jumpers
UnixExecDir = $(BinDir)/unix-exec
UnixExec = $(UnixExecDir)/$(ProductName)
MacOSBundleDir = $(BinDir)/macos-bundle
MacOSBundle = $(MacOSBundleDir)/$(ProductName).app
MacOSBundleStructure  = $(MacOSBundle)/Contents
MacOSBundleStructure += $(MacOSBundle)/Contents/Resources
MacOSBundleStructure += $(MacOSBundle)/Contents/Frameworks
MacOSBundleStructure += $(MacOSBundle)/Contents/MacOS

ResourcesDir = resc
Images = $(wildcard $(ResourcesDir)/imgs/*)

Sources = $(wildcard src/*.cpp)

Objects = $(patsubst $(SourceDir)/%.cpp,$(BuildDir)/%.o,$(Sources)) 

Infoplist = $(ResourcesDir)/Info.plist


all: $(MacOSBundle) $(UnixExec)

unix: $(UnixExec)

$(MacOSBundle): $(UnixExec) 
	mkdir -p $(MacOSBundleStructure)
	cp $(UnixExec) $(MacOSBundle)/Contents/MacOS/
	cp $(Infoplist) $(MacOSBundle)/Contents/
	cp $(ResourcesDir)/launcher.sh $(MacOSBundle)/Contents/MacOS/
	chmod +x $(MacOSBundle)/Contents/MacOS/launcher.sh
	cp $(Images) $(MacOSBundle)/Contents/Resources/
# Copy dylibs
	otool -L $(MacOSBundle)/Contents/MacOS/$(ProductName) |\
	ggrep -Po '((?<=\t)(?!((\/usr\/lib)|(\/System)))\S+)' |\
	xargs -n 1 -I {} cp {} $(MacOSBundle)/Contents/Frameworks
# Change references
	otool -L  $(MacOSBundle)/Contents/MacOS/$(ProductName) |\
	ggrep -Po '((?<=\t)(?!((\/usr\/lib)|(\/System)))\S+)' |\
	perl -pe 's/(\S*)(?=(lib.+dylib))/\@executable_path\/..\/Frameworks\//; print "$$1$$2 $$3"' |\
	xargs -J {} -L 1 install_name_tool -change {} $(MacOSBundle)/Contents/MacOS/$(ProductName)


$(UnixExec): $(Objects) $(Images)
#	mkdir $(BuildDir)
#	mkdir -p $(UnixExecDir)
	$(CC) $(LDFLAGS) $(Objects) -o $(UnixExec)
	cp $(Images) $(UnixExecDir)

$(Objects): $(BuildDir)/%.o: $(SourceDir)/%.cpp 
	$(CC) $(CCFLAGS) $< -o $@

test:
	cd $(UnixExecDir); ./$(ProductName)

.PHONY: clean
clean:
	rm -f $(BuildDir)/*o 
	rm -rf $(UnixExecDir)/* $(MacOSBundleDir)/*

.PHONY: run
run:
	make clean
	make all
	make test
