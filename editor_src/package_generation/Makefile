.DEFAULT_GOAL := generate_package

EDITOR_SOURCE_DIR := ..
PROJECT_SOURCE_DIR := ../..

RESOURCES_DIR := $(EDITOR_SOURCE_DIR)/resources
MAPS_DIR := $(PROJECT_SOURCE_DIR)/maps/
CONFIG_DIR := $(PROJECT_SOURCE_DIR)/config/
BIN_FILE := $(EDITOR_SOURCE_DIR)/build/wolfenstein3d-editor

PACKAGE_NAME := wolfenstein3d-editor
VERSION := 0.1
REVISION := 1

PACKAGE_DIR := ./$(PACKAGE_NAME)_$(VERSION)
PACKAGE_FILENAME := $(PACKAGE_DIR).deb

define DEBFILE_BODY
Package: $(PACKAGE_NAME)
Version: $(VERSION)
Section: base
Priority: optional
Architecture: amd64
Depends: qt5-default
Maintainer: Taller de programación I [75.42] - Grupo 8
Description: Wolfenstein3D
 Remake de Wolfenstein3D
endef
export DEBFILE_BODY

generate_package: build_all copy_files create_control_file
	dpkg-deb --build $(PACKAGE_DIR)
	rm -rf $(PACKAGE_DIR)
	rm -rf ../build

build_all:
	cd .. && \
	rm -rf build && \
	mkdir build && \
	cd build && \
	cmake .. && \
	make -j 4 && \
	cd .. && \
	cd package_generation

create_package_dirs: clean
	mkdir $(PACKAGE_DIR)
	mkdir $(PACKAGE_DIR)/usr
	mkdir $(PACKAGE_DIR)/usr/local
	mkdir $(PACKAGE_DIR)/usr/local/bin
	mkdir $(PACKAGE_DIR)/usr/local/share
	mkdir $(PACKAGE_DIR)/usr/local/share/wolfenstein3d-editor
	mkdir $(PACKAGE_DIR)/usr/local/share/wolfenstein3d-editor/routing
	mkdir $(PACKAGE_DIR)/DEBIAN

create_control_file: create_package_dirs
	echo "$$DEBFILE_BODY" > $(PACKAGE_DIR)/DEBIAN/control

copy_files: create_package_dirs
	cp -rf $(RESOURCES_DIR) $(PACKAGE_DIR)/usr/local/share/wolfenstein3d-editor
	cp -rf $(MAPS_DIR) $(PACKAGE_DIR)/usr/local/share/wolfenstein3d-editor
	cp -rf $(CONFIG_DIR) $(PACKAGE_DIR)/usr/local/share/wolfenstein3d-editor
	cp -f $(BIN_FILE) $(PACKAGE_DIR)/usr/local/bin

install: generate_package
	sudo dpkg --install $(PACKAGE_FILENAME)

remove:
	sudo apt-get remove ${PACKAGE_NAME}	

clean: 
	rm -rf $(PACKAGE_DIR) $(PACKAGE_FILENAME)