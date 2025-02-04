# Grenache CLI

![license](https://img.shields.io/github/license/bitfinexcom/grenache-cli.svg)
![GitHub release](https://img.shields.io/github/release/bitfinexcom/grenache-cli/all.svg)
![GitHub release date](https://img.shields.io/github/release-date/bitfinexcom/grenache-cli.svg)
![GitHub last commit](https://img.shields.io/github/last-commit/bitfinexcom/grenache-cli.svg)
![GitHub pull requests](https://img.shields.io/github/issues-pr/bitfinexcom/grenache-cli.svg)
![stability-stable](https://img.shields.io/badge/stability-stable-green.svg)

<img align="right" width="15%" src="https://github.com/bitfinexcom/grenache/raw/master/logos/logo-square.png" />

 - [Introduction](#introduction)
 - [Copying](#copying)
 - [Prerequisites](#prerequisites)
 - [Install](#install)
    - [Verifying the distribution](#verifying-the-distribution)
    - [Install from source](#install-from-source)
 - [Initialize](#initialize)
 - [Store items to the DHT](#store-items-to-the-dht)
    - [Immutable items](#immutable-items)
    - [Mutable items](#mutable-items)
 - [Retreive items from the DHT](#retreive-items-from-the-dht)
 - [Lookup peers](#lookup-peers)
 - [Announce services](#announce-services)
 - [Query services](#query-services)
 - [Maintainers](#maintainers)


## Introduction

The [**Grenache**](https://github.com/bitfinexcom/grenache) **C**ommand **L**ine **I**nterface is a set of tools to use the [grenache-grape](https://github.com/bitfinexcom/grenache-grape) suite directly from your command line. Using this set of tools you can create fancy scripts that communicate directly with the DHT.

All command lines presented in this document are for illustrative purposes only and could make use of tools not available on the user's operating system or provided in a different version, whereby some capabilities may not be available.


## Copying

The [**Grenache**](https://github.com/bitfinexcom/grenache) **C**ommand **L**ine **I**nterface is free software. See the files whose names start with _LICENSE_ (case-insensitive) for copying permission. The manuals, and some of the runtime libraries, are under different terms; see the individual source files for details.

Copyright years on [**Grenache**](https://github.com/bitfinexcom/grenache) **C**ommand **L**ine **I**nterface source files may be listed using range notation, e.g., 2017-2021, indicating that every year in the range, inclusive, is a copyrightable year that could otherwise be listed individually.


## Prerequisites

Be sure that your version of [grenache-grape](https://github.com/bitfinexcom/grenache-grape) supports the mutable items (see pull request [#35](https://github.com/bitfinexcom/grenache-grape/pull/35)).


## Install

The [**Grenache**](https://github.com/bitfinexcom/grenache) **C**ommand **L**ine **I**nterface relies on the [GNU Build System](https://www.gnu.org/software/automake/manual/html_node/GNU-Build-System.html). In the case where source code has been taken directly from this repository, several files related to the build system have to be generated manually; this can be achieved by running:

```bash
./autogen.sh
```

However, this requires a number of development tools that are not needed to run the [**Grenache**](https://github.com/bitfinexcom/grenache) **C**ommand **L**ine **I**nterface and are, usually, unlikely to be already installed on the user's operating system. Refer to the [official documentation](https://www.gnu.org/software/automake/manual/html_node/Autotools-Introduction.html) for all the required tools as well as the operating system literature on how to install them.

The preferred method of installing the [**Grenache**](https://github.com/bitfinexcom/grenache) **C**ommand **L**ine **I**nterface is to download the distribution archives, available under the [Releases](https://github.com/bitfinexcom/grenache-cli/releases) section of this repository. The download of the several files can be automated using something similar, which will always fetch all assets of the [latest release](https://github.com/bitfinexcom/grenache-cli/releases/latest) available:

```bash
parallel --color --no-run-if-empty 'wget --no-verbose --continue' < <( \
  jq --raw-output 'try(.assets[]) | .browser_download_url // empty' < <( \
    curl --silent 'https://api.github.com/repos/bitfinexcom/grenache-cli/releases/latest' \
  ) \
)
```

Although it is not required, it is worth verifying all the assets before taking any other action; refer to the [Verifying the distribution](#verifying-the-distribution) section for more details.

### Verifying the distribution

Unless already done in the past, it is required to import the [GnuPG](https://www.gnupg.org/) key of the packaging system in order to verify the authenticity of the distribution. Starting with version [0.8.0](https://github.com/bitfinexcom/grenache-cli/releases/tag/0.8.0), every released asset is signed using the key [94282D2E89053665952D3E7034C1AE501F0C2C6F](https://keys.openpgp.org/vks/v1/by-fingerprint/94282D2E89053665952D3E7034C1AE501F0C2C6F); older versions may have been signed with a different key, however, the same procedure applies.

To import the packaging system key within the local keyring, something like this is enough:

```bash
gpg --keyserver 'hkps://keys.openpgp.org' --recv-keys '94282D2E89053665952D3E7034C1AE501F0C2C6F'
```

Optionally, the packaging system key can be marked as *trusted* within the local keyring, such as via `--lsign-key`, making the verification process straightforward. However, in cases where this does not meet a user's security standards and the version of [GnuPG](https://www.gnupg.org/) in use is fairly recent, setting a [TOFU](https://www.gnupg.org/documentation/manuals/gnupg/GPG-Configuration-Options.html#index-trust_002dmodel) trust policy might be a suitable trade-off:

```bash
gpg --tofu-policy 'good' '94282D2E89053665952D3E7034C1AE501F0C2C6F'
```

In order to verify the authenticity of downloaded assets, something similar can be used:

```bash
parallel --color 'gpg --trust-model "tofu+pgp" --verify' ::: *.asc
```

Finally, in case the downloaded release provides a list of file checksums, this can be verified using something like this:

```bash
parallel --color --match '(\w+)sums\.asc$' \
  'gpg  --trust-model "tofu+pgp" --decrypt "{}" | cksum --algorithm "{1.1}" --check --ignore-missing' \
::: *sums.asc
```

### Install from source

Regardless of either source code has been taken directly from this repository or the sources archive has been unpacked, the shell command:

```bash
./configure && make && make install
```

should configure, build and install the [**Grenache**](https://github.com/bitfinexcom/grenache) **C**ommand **L**ine **I**nterface.

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


## Query services

The `grenache-request` command sends a request to a service in the DHT. To query the [rest:ext:helpdesk:foo](https://github.com/bitfinexcom/bfx-ext-helpdesk-js) service, simply run something like this:

```bash
grenache-request 'rest:ext:helpdesk:foo' 'getDepartments'
```

Action arguments are optional and can be omitted altogether. However, to pass an argument to an action, use the `-a` switch or its long form `--arg`; to query the [rest:net:util](https://github.com/bitfinexcom/bfx-util-net-js) service in order to get information about IP _208.67.222.222_, simply run something like this:

```bash
grenache-request -a '"208.67.222.222"' 'rest:util:net' 'getIpInfo'
```

To send multiple arguments, simply repeat the `-a` switch or its long form `--arg` as many times as needed; arguments will be passed to the service action in the same order as they were supplied on the command line. To query the [rest:ext:gpg](https://github.com/bitfinexcom/bfx-ext-gpg-js) service in order to get a signature for the _hello_ message, simply run something like this:

```bash
grenache-request -a '"68656c6c6f"' -a '{"userId":1}' 'rest:ext:gpg' 'getDigitalSignature'
```

Arguments are treated as _JSON_-encoded text; sometimes, when dealing with plain strings, this can be somewhat cumbersome. In such cases, the `-s` switch or its long form `--string` can be used to pass a string as-is or `-n` or its long form `--numeric` when accepting an option that is intended to be treated as a numeric value.

Typically, the output is a _JSON_-encoded text. Sometimes, filtering this text can be useful; in such cases, output can be selected using the `-q` switch or its long form `--query`, as shown below:

```bash
grenache-request -q 'map(select(.active_members > 3))' 'rest:ext:helpdesk:bar' 'getTeams'
```

The query is passed as-is to [jq](https://jqlang.github.io/jq/) and will be applied directly to the third position of the response array; refer to the official [filter documentation](https://jqlang.github.io/jq/manual/#basic-filters) for more details on the syntax to be used. However, there are cases where a plain string written directly to the standard output is preferable rather than formatted as a _JSON_ string with quotes, perhaps when pipe the output to another command; in such cases, the `-r` switch or its long form `--raw` can be used, as shown below:

```bash
grenache-request -q '.[1].timezone' -r -s '208.67.222.222' 'rest:util:net' 'getIpGeo'
```

Under normal circumstances, workflow is to look up the service via [grenache-lookup](#lookup-peers) and then send the request to the worker. There might be cases, perhaps when dealing with a system without a running [grape](https://github.com/bitfinexcom/grenache-grape), where it would be useful to query a service without looking it up first; in such cases, the `-w` switch or its long form `--worker` can be used, as shown below:

```bash
grenache-request -r -s '776f726c64' -a '{"userId":8}' -w '10.0.0.1:1337' 'rest:ext:gpg' 'getDigitalSignature'
```

Those are the main options; see

```bash
grenache-request --help
```

to retrieve the complete options list.


## Maintainers

Current maintainers:

- [Davide Scola](https://github.com/davide-scola)
