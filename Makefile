# Set default shell to bash
SHELL := /bin/bash -o pipefail

.PHONY: python-venv
python-venv:
	pip install virtualenv
	virtualenv ci-venv
	source ci-venv/bin/activate
	pip install -r requirements.txt
	pip install ./python

.PHONY: install-dependencies
install-dependencies:
	apt-get update
	apt-get install -y cmake g++ gcc gcovr ggcov git lcov make python-is-python3 python3-pip python3.8-venv tzdata valgrind

.PHONY: compile-moor-ai
compile-moor-ai:
	cmake -DYAML_BUILD_SHARED_LIBS=ON -B build
	make -C ./build -j4

.PHONY: install-moor-ai
install-moor-ai:
	cmake --install ./build/

.PHONY: python-test
python-test:
	source ci-venv/bin/activate
	python -m python.moor_ai.test_api
