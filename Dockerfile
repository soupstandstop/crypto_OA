FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y cmake g++ make git build-essential
RUN git clone https://github.com/jbeder/yaml-cpp.git && \
    cd yaml-cpp && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && make install && \
    ldconfig && \
    cd ../../ && \
    rm -rf yaml-cpp

WORKDIR /crypto_oa
COPY . /crypto_oa
RUN mkdir -p build && \
    cd build && \
    cmake -DCMAKE_CXX_STANDARD=11 .. && \
    make && \
    mv lookup-cli /usr/local/bin
CMD [ "bash" ]