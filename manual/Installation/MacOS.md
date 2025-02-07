# Installing Manticore on MacOS

## Via Homebrew package manager

```bash
brew install manticoresearch
```

For [indexing](../Creating_an_index/Local_indexes/Plain_index.md) the additional dependencies that can be installed using brew are `mysql@5.7`, `libpq`, `unixodbc`.

Afterwards you can start Manticore as a brew service:

```bash
brew services start manticoresearch
```

Manticore configuration file is `/usr/local/etc/manticoresearch/manticore.conf`.

## From tarball with binaries

Download it [from the website](https://manticoresearch.com/install/) and unpack to a folder:

```bash
mkdir manticore

cd manticore

wget https://repo.manticoresearch.com/repository/manticoresearch_macos/release/manticore-5.0.2-220530-348514c86-main.tar.gz

tar -xf manticore-5.0.2-220530-348514c86-main.tar.gz

wget https://repo.manticoresearch.com/repository/manticoresearch_macos/release/manticore-columnar-lib-1.15.4-220522-2fef34e-osx10.14.4-x86_64.tar.gz

tar -xf manticore-columnar-lib-1.15.4-220522-2fef34e-osx10.14.4-x86_64.tar.gz

# Start Manticore
FULL_SHARE_DIR=./share/manticore ./bin/searchd -c ./etc/manticoresearch/manticore.conf

# Run indexer
FULL_SHARE_DIR=./share/manticore ./bin/indexer -c ./etc/manticoresearch/manticore.conf
```

Manticore configuration file is `./etc/manticoresearch/manticore.conf` after you unpack the archive.
