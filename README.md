# Grenache CLI

![license](https://img.shields.io/github/license/bitfinexcom/grenache-cli.svg)
![GitHub (pre-)release](https://img.shields.io/github/release/bitfinexcom/grenache-cli/all.svg)
![GitHub (Pre-)Release Date](https://img.shields.io/github/release-date-pre/bitfinexcom/grenache-cli.svg)
![GitHub last commit](https://img.shields.io/github/last-commit/bitfinexcom/grenache-cli.svg)
![GitHub pull requests](https://img.shields.io/github/issues-pr/bitfinexcom/grenache-cli.svg)
![stability-unstable](https://img.shields.io/badge/stability-unstable-yellow.svg)

<img align="right" width="15%" src="https://github.com/bitfinexcom/grenache/raw/master/logos/logo-square.png" />

 * [Introduction](#introduction)
 * [Copying](#copying)
 * [Prerequisites](#prerequisites)
 * [Install](#install)
 * [Initialize](#initialize)
 * [Store items to the DHT](#store-items-to-the-dht)
   * [Immutable items](#immutable-items)
   * [Mutable items](#mutable-items)
 * [Retreive items from the DHT](#retreive-items-from-the-dht)
 * [Lookup peers](#lookup-peers)
 * [Announce services](#announce-services)
 * [Maintainers](#maintainers)


## Introduction

The [**Grenache**](https://github.com/bitfinexcom/grenache) **C**ommand **L**ine **I**nterface is a set of tools to use the [grenache-grape](https://github.com/bitfinexcom/grenache-grape) suite directly from your command line. Using this set of tools you can create fancy scripts that communicate directly with the DHT.


## Copying

The [**Grenache**](https://github.com/bitfinexcom/grenache) **C**ommand **L**ine **I**nterface is free software. See the files whose names start with _LICENSE_ (case-insensitive) for copying permission. The manuals, and some of the runtime libraries, are under different terms; see the individual source files for details.

Copyright years on [**Grenache**](https://github.com/bitfinexcom/grenache) **C**ommand **L**ine **I**nterface source files may be listed using range notation, e.g., 2017-2021, indicating that every year in the range, inclusive, is a copyrightable year that could otherwise be listed individually.


## Prerequisites

Be sure that your version of [grenache-grape](https://github.com/bitfinexcom/grenache-grape) supports the mutable items (see pull request [#35](https://github.com/bitfinexcom/grenache-grape/pull/35)).


## Install

Briefly, the shell command

```bash
./configure && make && make install
```

should configure, build and install this package.


## Initialize

Before start using this set of tools you need to initialize the `granache-cli` environment; use:

```bash
grenache-keygen
```

This will also generate your key pair that will be used when _mutable_ items are stored to the DHT. This is a one time only task but you can regenerate your key pair at any time if you want to.


## Store items to the DHT

The `grenache-put` command writes an arbitrary payload to the DHT (see [BEP 44](http://bittorrent.org/beps/bep_0044.html) for more information). There are two types of items you can store to the DHT; the _immutable_ items and the _mutable_ ones. In any case, you will get the key under which the item has been stored.

### Immutable items

_Immutable_ items cannot be modified, thus there is no need to authenticate the origin of them. This makes _immutable_ items simple. To write an _immutable_ item to the DHT simply run something like this:

```bash
grenache-put "$(uname -n)"
```

### Mutable items

_Mutable_ items can be updated, without changing their DHT keys. In order to create your key pair, see `grenache-keygen`. To write a _mutable_ item to the DHT simply run something like this:

```bash
grenache-put --mutable "$(uptime -p)"
```

In order to support a single key being used to store separate items in the DHT, an optional salt can be specified in the put request of _mutable_ items:

```bash
grenache-put --mutable --salt 'sys:mem:available' "$(awk '/^MemAvailable:/ { print $2 "Ki" }' < /proc/meminfo)"
```

Note that `grenache-put` is agnostic and it will treat your payload as a **single string**. Other useful options are `-n` or `--number` that will let you set the _sequence number_ to use in your request and `-c` or `--cas` that let you use the _compare and swap_ feature. See

```bash
grenache-put --help
```

to retrieve the complete options list.


## Retreive items from the DHT

The `grenache-get` command reads a data record from the DHT (see [BEP 44](http://bittorrent.org/beps/bep_0044.html) for more information). There is no differences in retreiving a _mutable_ or an _immutable_ item; in both cases the key returned by the *PUT* request must be provided. Furthermore, starting from version _[0.9.6](https://github.com/bitfinexcom/grenache-grape/commit/efbfc11)_ of [grenache-grape](https://github.com/bitfinexcom/grenache-grape), the _salt_ specified during the *PUT* operation must be provided if used. In any case, `grenache-get` validates the payload it receive; this will ensure that the _key_ provided really match the payload and, in case of a _mutable_ item, that the signature is correct. This will protect you from evil nodes on the network. To read an item from the DHT simply run something like this:

```bash
grenache-get '81c2a8157780989af9a16661324fafbd7803877d'
```

For example, you can format the previously stored available memory amount using something like this:

```bash
numfmt --from=auto --to=iec-i < <(
   grenache-get --salt 'sys:mem:available' '633def0b4349e2ed5bfbe0a5a1bb34e622f8c20d'
)
```

You can also retrieve the raw packet received from the network using the `-r` switch or its long form `--raw`. See

```bash
grenache-get --help
```

to retrieve the complete options list.


## Lookup peers

The `grenache-lookup` command finds peers that expose the supplied _service_ identifier. To find a random peer that provides the [rest:net:util](https://github.com/bitfinexcom/bfx-util-net-js) service simply run something like this:

```bash
grenache-lookup 'rest:net:util'
```

For example, you can check the [platform status](https://docs.bitfinex.com/v2/reference#rest-public-platform-status) on each peer that exposes the _rest:api:v2_ service using something like this:

```bash
for authority in $(grenache-lookup --all 'rest:api:v2'); \
do \
  curl --write-out '\n' "http://${authority}/v2/platform/status"; \
done
```

You can also pick the first peer in list using the `-f` switch or its long form `--first`. See

```bash
grenache-lookup --help
```

to retrieve the complete options list.


## Announce services

The `grenache-announce` command announces the given services in order to be stored in the DHT. To announce the [rest:net:util](https://github.com/bitfinexcom/bfx-util-net-js) service on port _31337_, simply run something like this:

```bash
grenache-announce 'rest:net:util,31337'
```

If no services are specified, `grenache-announce` enters the _streaming_ mode, reading the standard input. All comments (marked by a **#** or **;**) and blank lines are ignored. For example, a list of services can be announced using something like this:

```bash
grenache-announce <services.lst
```

An _announce service_ can also be created using a named pipe:

```bash
mkfifo --mode=0622 /run/grape/announce && \
  grenache-announce <>/run/grape/announce
```

Storing a service in the DHT now simply requires something like this:

```bash
echo 'rest:net:util,31337' >/run/grape/announce
```

A JSON stream can also be required (perhaps to implement a network service with something like [tcpserver](https://cr.yp.to/ucspi-tcp/tcpserver.html)) using the `-j` switch or its long form `--json`. The JSON document must contain a `data` array in which the _first position_ is the service name while the _second_ is the port number. Another useful option is `-d` or `--delimiter` which allows you to set the delimiter string between the _service name_ and _port number_ when not using JSON mode. See

```bash
grenache-announce --help
```

to retrieve the complete options list.


## Maintainers

Current maintainers:

* Davide Scola - davide@bitfinex.com
