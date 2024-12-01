#!/bin/sh

languages=( \
    python \
    ruby \
    rust \
    C \
    C++ \
    java \
    kotlin \
    haskell \
)

base=${#languages[@]}

langi=$(( (RANDOM) % base))

echo ${languages[$langi]}
