#!/user/bin/env make

TARGET_NAME = sqlite
SRC_ROOT = ../../src/${TARGET_NAME}

# Preface rules
include ${NUT_PATH}/proj/makefile/preface_rules.mk

# Includes
CPPFLAGS += -I${SRC_ROOT} -I${NUT_PATH}/src

# Defines

# C/C++ standard
CFLAGS += -std=c11

# Libraries

# TARGET
TARGET = ${OUT_DIR}/lib${TARGET_NAME}.${DL_SUFFIX}

.PHONY: all clean rebuild

all: ${TARGET}

clean:
	rm -rf ${OBJS} ${DEPS} ${TARGET}

rebuild:
	$(MAKE) -f sqlite.mk clean
	$(MAKE) -f sqlite.mk all

# NOTE shell.c 含有 main() 函数，应该去除
OBJS := ${OBJ_ROOT}/sqlite3.o
DEPS := ${OBJ_ROOT}/sqlite3.d

# Rules
include ${NUT_PATH}/proj/makefile/common_rules.mk
include ${NUT_PATH}/proj/makefile/shared_lib_rules.mk
