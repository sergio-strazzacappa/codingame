FROM debian:trixie-slim

RUN apt-get update && apt-get install -y    \
    curl                                    \
    build-essential                         \
    python3                                 \
    python3-pip                             \
    nodejs

RUN curl -fsSL https://opencode.ai/install | bash

WORKDIR /codingame
COPY . /codingame
