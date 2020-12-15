## What's this?
This is a imprementation of IKERUKANA.  
IKERUKANA is a function of a game MOMOTARO DENTETSU(https://www.konami.com/games/momotetsu/teiban/).  
This repository aims to make solver program of IKERUKANA and test it.  

## Directory structure
root/    
├ maps  
├ src  
├ test  
└README.md  

maps: Data of maps  
src: Programs. Solver, Library, etc..  
test: Test programs of IKERUKANA solver  

## How to use

```bash
$ git clone {This repository}

# Execute IKERUKANA program
$ cd Imprementation_of_IKERUKANA/test/normal_ikerukana/
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./run_normal_ikerukana_test

# Execute IKERUKANA_with_BONBI program
$ cd ../../ikerukana_with_BONBI
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./run_ikerukana_with_BONBI_test
```

## Dependencies
This project uses GTest library.
You have to install it.
