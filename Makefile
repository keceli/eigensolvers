#ELEMDIR=/usr/local/conf
include $(ELEM_DIR)/ElVars

x.elemental_GHEP: elemental_GHEP.cpp
	${CXX} -std=c++11 ${EL_COMPILE_FLAGS} $< -o  $@  ${EL_LINK_FLAGS} ${EL_LIBS}
