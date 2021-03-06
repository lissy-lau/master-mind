
.PHONY: all install clean cleanlib cleanall

#==============================================================================
# Module Name 
#==============================================================================

CATEGORY := Analyzer
MODULE   := FrequencyAnalyzer

include $(RULES_ROOT)/defs.$(TARGET)
include $(RULES_ROOT)/macros.default

#==============================================================================
# Module Defines
#==============================================================================

DEF_MOD := 


#==============================================================================
# Assembler, Compiler and Linker Options for the Module
#==============================================================================

OPT_ASM_MOD :=

OPT_CC_MOD  :=

OPT_CXX_MOD :=

OPT_LD_MOD  := \
            -lCharFrequency


#==============================================================================
# Module Include Paths
#================================================= =============================

INCLUDE_MOD :=


#==============================================================================
# List of Objects to Link
#==============================================================================

OBJS_TO_LINK := \
             $(OBJ_DIR)/FrequencyAnalyzer_Ncurses_Main.o
 

#==============================================================================
# External Libraries
#==============================================================================

LIBS_TO_LINK := \
             $(LIB_DIR)/libCharFrequency.so


#==============================================================================
# Include the standard build rules
#==============================================================================

include $(RULES_ROOT)/rules.default


