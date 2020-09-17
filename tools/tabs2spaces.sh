#!/bin/bash
for filename in asm/*.s; do
    expand -t 4 "$filename" > /tmp/e && mv /tmp/e "$filename"
done
