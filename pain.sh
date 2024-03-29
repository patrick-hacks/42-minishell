#!/bin/bash

PATH="$HOME/homebrew/bin:$PATH"

install_cmake () {
  if ! command -v brew &> /dev/null
  then
    echo "installing brew..."
    cd ~ && mkdir ./homebrew && curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C homebrew
    echo 'PATH="$HOME/homebrew/bin:$PATH"' >> ~/.bash_profile
    echo 'PATH="$HOME/homebrew/bin:$PATH"' >> ~/.zshrc
  fi

  if ! command -v cmake &> /dev/null
  then
    echo "installing cmake..."
    brew install cmake
  fi
}

if ! command -v cmake &> /dev/null
then
  echo "cmake not installed"
  if [[ $OSTYPE != 'darwin'* ]]; then
    echo 'please install it manually'
    exit 0
  fi
  read -p "do you want to install it? <y/n>" -r
  if [[ $REPLY =~ ^[Yy]$ ]]
  then
    install_cmake
  else
    exit 1
  fi
fi

brew list readline || brew install readline
cmake -B build
cd build && make -j8