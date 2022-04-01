FROM debian as builder
RUN apt-get update && apt-get install -y gcc
COPY example.c .
RUN gcc example.c -static -o /example

FROM scratch
COPY --from=builder /example /example
CMD ['/example', '@@']
