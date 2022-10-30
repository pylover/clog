# clog
C Logging library


## Usage

Link the following example with `-lclog`.

```C
#include <clog.h>


void main() {
  /* Set logging verbosidy */
  // clog_verbosidy = CLOG_SILENT;
  // clog_verbosidy = CLOG_FATAL;
  // clog_verbosidy = CLOG_ERROR;
  // clog_verbosidy = CLOG_WARNING;
  // clog_verbosidy = CLOG_INFO;
  clog_verbosity = CLOG_DEBUG;

  /* These functions will append newline at the end of expression*/
  DEBUG("Foo %s", "bar"); 
  INFO("Foo %s", "bar"); 
  WARN("Foo %s", "bar"); 
  ERROR("Foo %s", "bar"); 
  FATAL("Foo %s", "bar"); 

  /* These functions will not append newline at the end of expression*/
  DEBUGN("Foo %s\n", "bar"); 
  INFON("Foo %s\n", "bar"); 
  WARNN("Foo %s\n", "bar"); 
  ERRORN("Foo %s\n", "bar"); 
  FATALN("Foo %s", "bar"); 
}
```

## Build & Install

```bash
mkdir build
cd build
cmake ..
make
```

### Install with makefile

```bash
cd build
make install
```


### Create debian package

```bash
cd build
cpack
```

After that, `libclog-*.deb` will be generated insode the `build` directory.

#### Install using debian package

```bash
cd build
sudo dpkg -i libclog-*.deb
```

##### Uninstall

```bash
sudo dpkg -P libclog
```

Or

```bash
sudo apt remove libclog
```
