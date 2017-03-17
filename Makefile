# Makefile for compatibility with both Serial and OTA uploads

SRC_DIR = ${PWD}/src
BUILD_DIR = ${PWD}/build
MAIN_FILE = main.ino
TOOLS = ${PWD}/tools

PACKAGE = esp8266
ARCH = esp8266
BOARD = nodemcuv2
PARAMETER = CpuFrequency=160,FlashSize=4M3M,UploadSpeed=921600

ARG = --board ${PACKAGE}:${ARCH}:${BOARD}:${PARAMETER} --verbose-build --pref build.path=${BUILD_DIR}

# Define default serial port
ifndef SERIAL
	SERIAL=/dev/ttyUSB0
endif

ifndef IP
	IP=192.168.0.106
endif
ifndef PORT
	PORT=5222
endif

all:
	arduino --verify ${ARG} ${SRC_DIR}/${MAIN_FILE}

flash:
	arduino --upload ${ARG} ${SRC_DIR}/${MAIN_FILE} --port ${SERIAL}

clean:
	rm -rf ${BUILD_DIR}

upload: all
	${TOOLS}/espota.py --debug --progress -i ${IP} -p ${PORT} -f ${BUILD_DIR}/${MAIN_FILE}.bin

run: all upload


# Make examples:
# make flash SERIAL=/dev/ttyUSBx
# make upload IP=192.168.0.103
