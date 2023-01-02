# Set default shell to bash
SHELL := /bin/bash -o pipefail

.PHONY: python-venv
python-venv:
	pip install virtualenv
	virtualenv .ci-venv
	source .ci-venv/bin/activate
	.ci-venv/bin/pip install -r requirements.txt
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

# .PHONY: test-memory-check
# test-memory-check:
# 	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --track-origins=yes --error-exitcode=1 --leak-check=full ./bin/

# .PHONY: coverage-report
# coverage-report: test-execution
# 	mkdir --parents .coverage/
# 	gcovr --xml-pretty --exclude-unreachable-branches --print-summary -o coverage.xml --root ./
# 	gcov -o ./build/src/yaml-fortran/CMakeFiles/yaml-interface.dir/*.f90.* ./src/yaml-wrapper/*.f90
# 	mv ./build/src/yaml-fortran/CMakeFiles/yaml-interface.dir/*.gcda .coverage
# 	mv ./build/src/yaml-fortran/CMakeFiles/yaml-interface.dir/*.gcno .coverage
# 	lcov --gcov-tool gcov --capture --directory . --output-file .coverage/cov.info
# 	genhtml --output-directory .coverage .coverage/cov.info

# .PHONY: documentation
# documentation:
# 	mkdocs build --strict --config-file ./mkdocs.yml
