# docker build .
FROM debian
RUN apt-get update && apt-get install --no-install-recommends --yes \
    build-essential \
    clang \
    cmake \
    debhelper \
    devscripts \
    git \
    && rm -rf /var/lib/apt/lists/* # TODO autoremove build deps
COPY . /home/safestringlib
WORKDIR /home/safestringlib
RUN dpkg-buildpackage -us -uc
WORKDIR /home
RUN dpkg -i \
    safestringlib_1.0.0-1_amd64.deb \
    safestringlib-dev_1.0.0-1_amd64.deb
WORKDIR /home/safestringlib/libfuzzer
ARG CFLAGS="-fsanitize=address,fuzzer -lsafestring_shared"
RUN clang $CFLAGS -o fuzz_target.out fuzz_target.cc \
	&& clang $CFLAGS -o wcscat_target.out wcscat_target.cc
