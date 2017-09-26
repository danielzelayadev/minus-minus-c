# --C

--C is a compiler for a subset of the C language. The code generated compiles to MIPS32 which will run on a runtime environment called VMIPSSOC. --C supports only `int`s, `char`s and arrays for each. It supports functions, almost all of the C statements (except for Switch and Do...While statements), and most of the C expressions.

## Getting Started

### Prerequisites

- linux
- g++
- make
- flex
- bison

### Build the Compiler

```
make
```

### Make the Scripts Executable

```
chmod +x compile.sh
chmod +x run.sh
chmod +x snap.sh
chmod +x test.sh
```

## Usage

#### Compile to VMIPSSOC

```
./compile.sh samples/HelloWorld.c
```

#### Compile to Custom Destination

```
./compile.sh samples/HelloWorld.c ~/Desktop/here.s
```

#### Run VMIPSSOC

```
./run.sh
```

#### Compile and Run VMIPSSOC

```
./run.sh samples/ForTest.c
```

#### Compile and Run VMIPSSOC for Every Sample

```
./run.sh --all
```

## Running the tests

This project uses snapshot tests. This means that the output code of the compiler will be tested against its corresponding snapshot in the `./snapshots` folder. The snapshot is the expected code, and the compiled code is the actual code. If they do not match, the test fails, otherwise, it succeeds. </br></br>
Whenever you get the expected code from the compiler, create a snapshot of it so it can be used as a test case for future changes to the compiler code. Snapshots must be updated as the expected code changes. 

### Creating a New Snapshot

This will create a snapshot from the compiled code of the sample and store it in the `./snapshots` directory.  It can then be used for testing.

```
./snap.sh samples/ArithOperators.c
```

### Run a Snapshot Test


```
./test.sh samples/RelOperators.c
```

### Run All Snapshot Tests

```
./test.sh
```