#!/bin/bash

# Initialize variables
CONFIGURE=false
BUILD=false
MODULE_NAME=""
ARCHIVE=false

# Parse command line options
while getopts "Cbm:i" opt; do
  case $opt in
    C)
      CONFIGURE=true
      ;;
    b)
      BUILD=true
      ;;
    m)
      MODULE_NAME=$OPTARG
      ;;
    i)
      ARCHIVE=true
      BUILD=true
      ;;
    *)
      echo "Usage: $0 [-C] [-b] [-m MODULE_NAME] [-i]"
      exit 1
      ;;
  esac
done

# Full CMake reconfiguration if -C is given
if [ "$CONFIGURE" = true ]; then
  echo "Running full CMake reconfiguration..."
  rm -rf build
  mkdir build
  cd build
  cmake ..
  cd ..
fi

# Build step if -b is given
if [ "$BUILD" = true ]; then
  echo "Running build step..."
  cd build

  if [ -n "$MODULE_NAME" ]; then
    echo "Building module: $MODULE_NAME"
    make $MODULE_NAME
  else
    make
  fi

  cd ..

  # Archive bin folder if -i is given and build is successful
  if [ "$ARCHIVE" = true ]; then
    echo "Archiving bin folder to artifacts/advanced-cpp.tar.gz..."
    mkdir -p artifacts
    tar -czvf artifacts/advanced-cpp.tar.gz bin
  fi
fi
