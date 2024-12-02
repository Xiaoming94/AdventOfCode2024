#!/bin/sh

languages=( \
    python \
    ruby \
    rust \
    C \
    C++ \
    C# \
    java \
    kotlin \
    haskell \
    erlang \
    elixir
)

base=${#languages[@]}

langi=$(( (RANDOM) % base))

echo ${languages[$langi]}
