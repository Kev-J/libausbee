CD=cd
DOXYGEN=doxygen
RM_RF=rm -rf

SRC_PATH=$(LIBAUSBEE_PATH)/src

# Include files
INCLUDES+=-I"include/"
INCLUDES+=-I$(STD_PERIPH_INCLUDES_DIR)
INCLUDES+=-I$(DEVICE_INCLUDES_DIR)
INCLUDES+=-I$(CMSIS_INCLUDES_DIR)

# Add source files
LIBAUSBEE_SRC_FILES+=$(wildcard src/drivers/*.c)
LIBAUSBEE_SRC_FILES+=$(wildcard src/control_system/*.c)
LIBAUSBEE_SRC_FILES+=$(wildcard src/control_system/controller/*.c)
LIBAUSBEE_SRC_FILES+=$(wildcard src/control_system/filters/*.c)

# Object files list
LIBAUSBEE_OBJ_FILES=$(LIBAUSBEE_SRC_FILES:.c=.o)

# Add the object files to the global object files
OBJ_FILES+=$(LIBAUSBEE_OBJ_FILES)

all:libausbee.a

libausbee.a: $(LIBAUSBEE_OBJ_FILES)
	$(AR) -q $@ $^

# Build objects
$(LIBAUSBEE_OBJ_FILES): %.o :%.c
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) $(SYSTEM_INCLUDES_DIR) -D$(DEVICE) -c $<

.PHONY: clean doc

doc:
	$(CD) documentation ; \
	$(DOXYGEN) Doxyfile

clean:
	$(RM_RF) $(LIBAUSBEE_OBJ_FILES)

mrpropper: clean
	$(RM_RF) libausbee.a
