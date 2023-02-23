SDK_HOME := $(HOME)/Library/Reason/SDK
BUILD_TOOLS := $(SDK_HOME)/Tools/Build
RENDERER := $(SDK_HOME)/RE2DRender.app/Contents/MacOS/Re2DRender
RM := rm -fr

.PHONY: gui
gui:
	$(RENDERER) GUI2D GUI

.PHONY: build
build:
	PYTHONPATH=$(BUILD_TOOLS) python2 build45.py local45 Testing
	
.PHONY: package
package:
	PYTHONPATH=$(BUILD_TOOLS) python2 build45.py universal45

.PHONY: clean
clean:
	$(RM) *.plist Intermediate-llvm GUI Output

.PHONY: all
all: gui build