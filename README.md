# clog
C Logging library


## Build & Install

```bash
mkdir build
cmake ..
make
make install
```


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
  clog_verbosidy = CLOG_DEBUG;

  /* These functions will append newline */
  DEBUG("Foo %s", "bar"); 
  INFO("Foo %s", "bar"); 
  WARN("Foo %s", "bar"); 
  ERROR("Foo %s", "bar"); 
  FATAL("Foo %s", "bar"); 

  /* These functions will not append newline*/
  DEBUG("Foo %s\n", "bar"); 
  INFO("Foo %s\n", "bar"); 
  WARN("Foo %s\n", "bar"); 
  ERROR("Foo %s\n", "bar"); 
  FATAL("Foo %s", "bar"); 
}
```

## Create debian package

```bash
cd build
cpack
```

After that, `libclog-*.deb` will be generated insode the `build` directory.
