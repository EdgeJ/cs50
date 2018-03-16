# Questions

## What's `stdint.h`?

A header file supplying BMP-related data types

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

To easily create data types that conform the the BMP standard with a handy shorthand.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

8 bits, 32 bits (unsigned), 32 bits (signed), 16 bits

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

`BM`

## What's the difference between `bfSize` and `biSize`?

`bfSize` is the number of bytes in the file, `biSize` is the number of bytes in the structure.

## What does it mean if `biHeight` is negative?

The bitmap is a top-down DIB and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

`biBitCount`

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

File permissions could prevent either the opening or writing of the file.

## Why is the third argument to `fread` always `1` in our code?

We only want to read the number of bytes once.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

Moves to a position within the file.

## What is `SEEK_CUR`?

`SEEK_CUR` instructs `fseek` to seek from n bytes from current position in the file.