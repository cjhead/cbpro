# CBPro

An interface to the Coinbase/CoinbasePro API

## Requirements

- openssl
- libcurl
- cjson (if you want to follow a similar approach to what's in src/main.c)

## Usage

- Currently a work in progress.
- I'm using this project to help further my understanding of the C language so there will be many, many changes as I progress, but hopefully there will be something you can take away.
- The src/main.c file is meant as a test implementation.
- I'm currently trying to decide if it's best to leave structure creation up to the caller or create them on my end.

## Configuration

- For the functions that require authorization, you'll need to put your
  credentials in a text file similar to this:
```
secret_key ****************
api_key *************
passphrase *********
```
