#######################################################################################################
# Copyright (C) Heap of Battle 2024                                                                   #
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   21.12.2023  Gaina Stefan               Initial version.                                           #
#   19.01.2024  Gaina Stefan               Added SDL2_mixer dependencies.                             #
# Description: This Makefile is used to install third party binaries/assets to install directory.     #
#######################################################################################################

INSTALL_PATH = ../$(INSTALL_DIRECTORY)

### INSTALL ###
install:
	cp -r assets                                   $(INSTALL_PATH)
	install Plog/$(LIB)/libplog.so                 $(INSTALL_PATH)/$(LIB)
	install Plog/plog.conf                         $(INSTALL_PATH)
	install SDL2/$(LIB)/libSDL2-2.0.so             $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2-2.0.so.0           $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2-2.0.so.0.18.2      $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_image.so           $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_image-2.0.so       $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_image-2.0.so.0     $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_image-2.0.so.0.2.3 $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_mixer.so           $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_mixer-2.0.so       $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_mixer-2.0.so.0     $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_mixer-2.0.so.0.2.2 $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libdecor-0.so              $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libdecor-0.so.0            $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libdecor-0.so.0.100.0      $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libfluidsynth.so.3         $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libfluidsynth.so.3.0.5     $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libinstpatch-1.0.so.2      $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libinstpatch-1.0.so.2.2.0  $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libmodplug.so              $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libmodplug.so.1            $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libmodplug.so.1.0.0        $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libopusfile.so             $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libopusfile.so.0           $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libopusfile.so.0.4.2       $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_ttf.so             $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_ttf-2.0.so         $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_ttf-2.0.so.0       $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_ttf-2.0.so.0.18.0  $(INSTALL_PATH)/$(LIB)
	install Run-Script/Heap-of-Battle.sh           $(INSTALL_PATH)

### UNINSTALL ###
uninstall:
	rm -rf $(INSTALL_PATH)
