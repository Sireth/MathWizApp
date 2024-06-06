FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    gcc-9 \
    g++-9 \
    ninja-build \
    cmake

RUN apt-get install -y valgrind

RUN apt-get install -y --install-recommends libboost-all-dev

RUN apt-get install -y bison flex

RUN mkdir /math_wiz_app

WORKDIR /math_wiz_app
COPY . /math_wiz_app/

