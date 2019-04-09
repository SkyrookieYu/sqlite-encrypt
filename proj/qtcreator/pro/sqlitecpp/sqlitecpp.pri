
TARGET = sqlitecpp
TEMPLATE = lib
VERSION = 3.15.1

include(../sqlite_encrypt_common.pri)

CONFIG -= qt

DEFINES += SQLITE_HAS_CODEC

SQLITE_SRC_PATH = $$PWD/../../../../src/sqlite
SQLITE_ENCRYPT_SRC_PATH = $$PWD/../../../../src/sqlite_encrypt
SRC_ROOT = $$PWD/../../../../src/sqlitecpp

INCLUDEPATH += $${SQLITE_SRC_PATH}

HEADERS += \
    $$files($${SQLITE_SRC_PATH}/*.h, true) \
    $$files($${SQLITE_ENCRYPT_SRC_PATH}/*.h, true) \
    $$files($${SRC_ROOT}/*.h, true)

# HACK "sqlite3.c" 被包含在了 "codecext.c" 中
SOURCES += \
    $${SQLITE_SRC_PATH}/shell.c \
    $$files($${SQLITE_ENCRYPT_SRC_PATH}/*.c*, true) \
    $$files($${SRC_ROOT}/*.c*, true)

# 链接库
mac {
    LIBS += -lc++
} else: unix {
    LIBS += -lrt
} else: win32 {
    LIBS += -lpthread
}

# nut
INCLUDEPATH += $${NUT_PATH}/src
LIBS += -L$$OUT_PWD/../nut$${OUT_TAIL}
win32: LIBS += -lnut1
else: LIBS += -lnut