#######################################################################################################
# Copyright (C) Heap of Battle 2024                                                                   #
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   21.12.2023  Gaina Stefan               Initial version.                                           #
#   19.01.2024  Gaina Stefan               Added SDL2_mixer dependencies.                             #
#   19.01.2024  Gaina Stefan               Added libwebp7 dependencies.                               #
# Description: This Makefile is used to install third party binaries/assets to install directory.     #
#######################################################################################################

INSTALL_PATH = ../$(INSTALL_DIRECTORY)

### INSTALL ###
install:
	cp -r assets                                    $(INSTALL_PATH)
	install Plog/$(LIB)/libplog.so                  $(INSTALL_PATH)/$(LIB)
	install Plog/plog.conf                          $(INSTALL_PATH)
	install SDL2/$(LIB)/libSDL2-2.0.so              $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2-2.0.so.0            $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2-2.0.so.0.18.2       $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_image.so            $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_image-2.0.so        $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_image-2.0.so.0      $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_image-2.0.so.0.2.3  $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_mixer.so            $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_mixer-2.0.so        $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_mixer-2.0.so.0      $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_mixer-2.0.so.0.2.2  $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_ttf.so              $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_ttf-2.0.so          $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_ttf-2.0.so.0        $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libSDL2_ttf-2.0.so.0.18.0   $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libdecor-0.so               $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libdecor-0.so.0             $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libdecor-0.so.0.100.0       $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libfluidsynth.so.3          $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libfluidsynth.so.3.0.5      $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libinstpatch-1.0.so.2       $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libinstpatch-1.0.so.2.2.0   $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libmodplug.so               $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libmodplug.so.1             $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libmodplug.so.1.0.0         $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libopusfile.so              $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libopusfile.so.0            $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libopusfile.so.0.4.2        $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libwayland-egl.so           $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libwayland-egl.so.1         $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libwayland-egl.so.1.20.0    $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libwayland-cursor.so        $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libwayland-cursor.so.0      $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libwayland-cursor.so.0.20.0 $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libxkbcommon.so             $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libxkbcommon.so.0           $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libxkbcommon.so.0.0.0       $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libjpeg.so                  $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libjpeg.so.8                $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libjpeg.so.8.2.2            $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libtiff.so                  $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libtiff.so.5                $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libtiff.so.5.7.0            $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libwebp.so                  $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libwebp.so.7                $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libwebp.so.7.1.3            $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libvorbisfile.so            $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libvorbisfile.so.3          $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libvorbisfile.so.3.3.8      $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libmpg123.so                $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libmpg123.so.0              $(INSTALL_PATH)/$(LIB)
	install SDL2/$(LIB)/libmpg123.so.0.46.7         $(INSTALL_PATH)/$(LIB)
	install Run-Script/Heap-of-Battle.sh            $(INSTALL_PATH)

### UNINSTALL ###
uninstall:
	rm -rf $(INSTALL_PATH)
