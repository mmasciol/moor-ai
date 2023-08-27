# Set default shell to bash
SHELL := /bin/bash -o pipefail

.PHONY: python-venv
python-venv:
	pip install -r requirements.txt
	cd python && python setup.py bdist_wheel

.PHONY: install-dependencies
install-dependencies:
	apt-get update
	apt-get install -y clang-format cmake g++ gcc gcovr ggcov git iwyu lcov make python-is-python3 python3-pip python3.8-venv tzdata uncrustify valgrind

.PHONY: compile
compile:
	cmake -B build -DMOOR_AI_DEBUG=ON -DMOOR_AI_DOUBLE_PRECISION=ON
	make -C ./build -j4

.PHONY: install
install:
	cmake --install ./build/

.PHONY: python-test
python-test:
	python -m python.moor_ai.test_api

.PHONY: test-exe
test-exe:
	./bin/test/test-entry

.PHONY: test-memory-check
test-memory-check:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --track-origins=yes --error-exitcode=1 --leak-check=full ./bin/test/test-entry
