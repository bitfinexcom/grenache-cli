# Grenache CLI

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

 * [Introduction](#introduction)
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

The **Grenache** **C**ommand **L**ine **I**nterface is a set of tools to use the [grenache-grape](https://github.com/bitfinexcom/grenache-grape) suite directly from your command line. Using this set of tools you can create fancy scripts that communicate directly with the DHT.


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

The `grenache-get` command reads a data record from the DHT (see [BEP 44](http://bittorrent.org/beps/bep_0044.html) for more information). There is no differences in retreiving a _mutable_ or an _immutable_ item; on both cases the key returned by the *PUT* request must be provided. In any case, `grenache-get` validates the payload it receive; this will ensure that the _key_ provided really match the payload and, in case of a _mutable_ item, that the signature is correct. This will protect you from evil nodes on the network. To read an item from the DHT simply run something like this:

```bash
grenache-get '81c2a8157780989af9a16661324fafbd7803877d'
```

For example, you can format the previously stored available memory amount using something like this:

```bash
numfmt --from=auto --to=iec-i < <(
   grenache-get '81c2a8157780989af9a16661324fafbd7803877d'
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

Coming soon...


## Maintainers

Current maintainers:

* Davide Scola - davide@bitfinex.com
