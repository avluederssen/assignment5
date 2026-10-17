# assignment5 - SLM

## Description

SLM is a C++ program that generates text based on a training text file. It uses k-gram frequencies and transition probabilities to generate new text. Some might call it an *Artificial Idiot*.

## Requirements

* A C++ compiler, such as `g++`
* `make`

## Compilation

Compile the program from the project root directory by running:

make

This creates the executable `slm`.

## Usage

./slm [-a alpha] k filename length


The parameter `-a alpha` is optional. If not specified, the default value is `0.0`.

## Parameters

* `-a alpha`: Optional smoothing parameter. The default value is `0.0`.
* `k`: The length of each k-gram. Must be a positive integer.
* `filename`: The path to the training text file.
* `length`: The requested length of the generated text. Must be at least `k`.

## Examples

Generate 100 characters using k-grams of length 2:

./slm 2 training.txt 100

Generate 100 characters with a smoothing parameter of 0.5:

./slm -a 0.5 2 training.txt 100


## Cleaning

Remove the compiled executable by running:

make clean
