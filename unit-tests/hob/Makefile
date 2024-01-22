#######################################################################################################
# Copyright (C) Heap of Battle 2024                                                                   #
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   21.01.2024  Gaina Stefan               Initial version.                                           #
#   22.01.2024  Gaina Stefan               Added Component and Music.                                 #
# Description: This Makefile is used to invoke the Makefiles in the subdirectories.                   #
#######################################################################################################

all:
	$(MAKE) -C hob_Component
	$(MAKE) -C hob_Music
	$(MAKE) -C hob_Sound
	$(MAKE) -C hob_Texture
	$(MAKE) -C hob_Window

### RUN TESTS ###
run_tests:
	$(MAKE) run_tests -C hob_Component
	$(MAKE) run_tests -C hob_Music
	$(MAKE) run_tests -C hob_Sound
	$(MAKE) run_tests -C hob_Texture
	$(MAKE) run_tests -C hob_Window

### CLEAN ###
clean:
	$(MAKE) clean -C hob_Component
	$(MAKE) clean -C hob_Music
	$(MAKE) clean -C hob_Sound
	$(MAKE) clean -C hob_Texture
	$(MAKE) clean -C hob_Window
