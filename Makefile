# Set default shell to bash
SHELL := /bin/bash -o pipefail

.PHONY: python-venv
python-venv:
	pip install -r requirements.txt

.PHONY: install-dependencies
install-dependencies:
	apt-get update
	apt-get install -y clang-format cmake g++ gcc gcovr ggcov git iwyu lcov make python-is-python3 python3-pip python3.8-venv tzdata uncrustify valgrind

.PHONY: compile-moor-ai
compile-moor-ai:
	cmake -DYAML_BUILD_SHARED_LIBS=ON -B build
	make -C ./build -j4

.PHONY: install-moor-ai
install-moor-ai:
	cmake --install ./build/

.PHONY: python-test
python-test:
	pip install ./python
	python -m python.moor_ai.test_api
