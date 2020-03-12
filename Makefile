.DEFAULT_GOAL := help

.venv: ## creating virtual environment
	@python3 -m venv $@
	# updating package managers
	@$@/bin/pip --no-cache install --upgrade \
		pip \
		setuptools \
		wheel
	@$@/bin/pip --no-cache install -r requirements.txt
	
PYINC := $(shell python3-config --includes)

.PHONY: build
build: ## builds the c++ example extension
	g++ -shared -fPIC ${PYINC} sim4life.cpp -o sim4life.so
	## export LD_LIBRARY_PATH=${PWD}

.PHONY: build-example
build-example: ## builds the c++ example extension
	cd example && g++ -shared -fPIC ${PYINC} example.cpp -o example.so
	## export LD_LIBRARY_PATH=${PWD}/example

# MISC ---------------------------------------------------------------

.PHONY: help
help: ## help on rule's targets
	@awk --posix 'BEGIN {FS = ":.*?## "} /^[[:alpha:][:space:]_-]+:.*?## / {printf "\033[36m%-25s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST)
