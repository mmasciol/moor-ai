FROM ubuntu:20.04

ENV TZ=US
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

COPY Makefile Makefile
COPY ./python/requirements.txt requirements.txt

RUN apt-get update && apt-get -y install make
RUN make install-dependencies
RUN make python-venv

RUN rm -rf Makefile requirements.txt