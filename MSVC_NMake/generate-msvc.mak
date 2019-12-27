# NMake Makefile portion for code generation and
# intermediate build directory creation
# Items in here should not need to be edited unless
# one is maintaining the NMake build files.

# Create the build directories
vs$(VSVER)\$(CFG)\$(PLAT)\gendef	\
vs$(VSVER)\$(CFG)\$(PLAT)\cairomm	\
vs$(VSVER)\$(CFG)\$(PLAT)\cairomm-ex	\
vs$(VSVER)\$(CFG)\$(PLAT)\cairomm-tests:
	@-mkdir $@

# Generate .def files
vs$(VSVER)\$(CFG)\$(PLAT)\cairomm\cairomm.def: $(GENDEF) vs$(VSVER)\$(CFG)\$(PLAT)\cairomm $(cairomm_OBJS)
	vs$(VSVER)\$(CFG)\$(PLAT)\gendef.exe $@ $(CAIROMM_LIBNAME) vs$(VSVER)\$(CFG)\$(PLAT)\cairomm\*.obj
