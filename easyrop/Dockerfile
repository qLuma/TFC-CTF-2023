FROM ubuntu:22.04

RUN apt update && apt install -y socat

RUN mkdir /home/ctf
ADD . /home/ctf
RUN chmod -R 755 /home/ctf

RUN useradd -s /bin/bash ctf
USER ctf
WORKDIR /home/ctf

CMD socat TCP-LISTEN:42002,fork,reuseaddr EXEC:/home/ctf/easyrop,stderr
