# CBPro

An interface to the Coinbase/CoinbasePro API

![GitHub last commit](https://img.shields.io/github/last-commit/cjhead/cbpro)
![GitHub](https://img.shields.io/github/license/cjhead/cbpro)
![GitHub issues](https://img.shields.io/github/issues/cjhead/cbpro)
![GitHub pull requests](https://img.shields.io/github/issues-pr/cjhead/cbpro)

## Table of Contents
- [Introduction](#introduction)
- [Requirements](#requirements)
- [Usage](#usage)
- [Configuration](#configuration)

## Introduction

- Currently a work in progress.
- I'm using this project to help further my understanding of the C language so there will be many, many changes as I progress, but hopefully there will be something you can take away.
- The src/main.c file is meant as a test implementation.
- If there's anything you want to see added, please let me know!

## Requirements

- [openssl](https://github.com/openssl/openssl)
- [libcurl](https://github.com/curl/curl)

## Usage

- My goal was to make the process as easy as possible. To begin, create a
  Client

```c
int main(void) {
    struct Client *client = client_create();
}
```

- Not every call requires user authentication. To get you started, you can
  try something like this:

```c
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

## Configuration

- For the functions that require authorization, you'll need to put your
  credentials in a text file similar to this:
```
secret_key ****************
api_key *************
passphrase *********
```
