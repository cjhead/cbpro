# CBPro

A library to interface with the Coinbase/CoinbasePro API

![GitHub last commit](https://img.shields.io/github/last-commit/cjhead/cbpro)
![GitHub](https://img.shields.io/github/license/cjhead/cbpro)
![GitHub issues](https://img.shields.io/github/issues/cjhead/cbpro)
![GitHub pull requests](https://img.shields.io/github/issues-pr/cjhead/cbpro)

![GitHub Repo stars](https://img.shields.io/github/stars/cjhead/cbpro?style=social)
![GitHub forks](https://img.shields.io/github/forks/cjhead/cbpro?style=social)
![GitHub watchers](https://img.shields.io/github/watchers/cjhead/cbpro?style=social)

## Table of Contents
- [Introduction](#introduction)
- [Dependencies](#dependencies)
- [Install](#install)
- [Usage](#usage)
- [Configuration](#configuration)

## Introduction
- Currently a work in progress.
- I'm using this project to help further my understanding of the C language so there will be many, many changes as I progress, but hopefully there will be something you can take away.
- The src/main.c file is meant as a test implementation.
- If there's anything you want to see added, please let me know!

## Dependencies
- [openssl](https://github.com/openssl/openssl)
- [libcurl](https://github.com/curl/curl)

## Optional Dependencies
- [cJSON](https://github.com/DaveGamble/cJSON) - To format and parse the output.

## Install

```
git clone https://github.com/cjhead/cbpro.git
cd cbpro
make
```

To create and run a simple test program:

```
make test
test/bin/get_product
```

## Usage
- My goal was to make the process as easy as possible.
- The src/main.c file can be used as a simple template; just uncomment what you need.
- To begin from scratch, create a Client:

```c
#include "path/to/cbpro.h"

int main(void) {
    struct Client *client = client_create();
}
```

- Not every call requires user authentication. To get you started, you can
  try something like this:

```c
#include "path/to/cbpro.h"

int main(void) {
    // Create the client
    struct Client *client = client_create();

    // Get all available currencies
    get_all_products(client);

    // Print results to stdout
    printf("%s\n", client->data->buffer);

    // Cleanup
    client_cleanup(client);
    curl_global_cleanup();

    return EXIT_SUCCESS;
}
```

- Some API calls will require the user to be authenticated. Simply copy
  your API credentials to a locally saved file that you supply in your
code.
- The file should look like this:

```
secret_key ****************
api_key *************
passphrase *********
```

- **NOTE: This is most likely not very secure.**

- You should then be able to use the functions requiring authentication.

```c
#include "path/to/cbpro.h"

int main(void) {
    // Create the client
    struct Client *client = client_create();

    // Authenticate the client
    const char *cred_file = "creds.txt";
    authorize_client(cred_file, client);

    // Get all accounts belonging to the user
    get_accounts(client);

    // Print results to stdout
    printf("%s\n", client->data->buffer);

    // Cleanup
    client_cleanup(client);
    curl_global_cleanup();

    return EXIT_SUCCESS;
}
```

- When ready to compile, make sure to link to the library
`-Llib/ -lcbpro`

## Configuration

- For the functions that require authorization, you'll need to put your
  credentials in a text file with a format like to this:
```
secret_key ****************
api_key *************
passphrase *********
```
