# Movie-Seating-Arrangement
# Movie Seating Arrangement Solver

## Description

This repository contains two programs, `wheretosita` and `wheretositb`, developed for the COP 3502C assignment. These programs are designed to solve a complex problem regarding the seating arrangement for a group of people attending a movie, considering specific constraints like seating preferences and popcorn sharing.

- `wheretosita.c` calculates the number of valid seating arrangements.
- `wheretositb.c` identifies and prints the first valid seating arrangement in lexicographical order.

## Features

- Efficiently generates all possible seating arrangements.
- Checks each arrangement for validity based on defined constraints.
- Utilizes command-line arguments to specify input files, enhancing usability and flexibility.

## Installation

To compile the programs, use the following `gcc` commands:

```bash
gcc wheretosita.c -o wheretosita
gcc wheretositb.c -o wheretositb
