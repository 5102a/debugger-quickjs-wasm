#!/bin/sh
emcc \
  -g3 \
  main.c \
  ./quickjs/quickjs.c \
  ./quickjs/cutils.c \
  ./quickjs/libregexp.c \
  ./quickjs/libbf.c \
  ./quickjs/libunicode.c \
  ./quickjs/quickjs-debugger-ipc.c \
  -sWASM=1 \
  -sEXPORTED_RUNTIME_METHODS='["ccall", "cwrap","stringToUTF8","stackAlloc"]'  \
  -sMODULARIZE=1  \
  -sINVOKE_RUN=0 \
  -sALLOW_MEMORY_GROWTH=1 \
  --js-library library_a.js \
  -sALLOW_TABLE_GROWTH=1  \
  -sSUPPORT_ERRNO=0 \
  -sIGNORE_MISSING_MAIN=0 \
  -fdebug-compilation-dir='.' \
  --no-entry \
  -sINITIAL_MEMORY=512557056 \
  -sASYNCIFY_STACK_SIZE=24576 \
  -sASYNCIFY_IMPORTS=do_wait,js_transport_read_fully \
  -sAUTO_JS_LIBRARIES=0 \
  -lwebsocket.js \
  -sASYNCIFY \
  -sAUTO_NATIVE_LIBRARIES=0 \
  -sAUTO_ARCHIVE_INDEXES=0 \
  -sDEFAULT_TO_CXX=0 \
  -sLLD_REPORT_UNDEFINED \
  -sALLOW_UNIMPLEMENTED_SYSCALLS=0  \
  -sNODEJS_CATCH_EXIT=0 \
  -O0 -DQTS_DEBUG_MODE  \
  --source-map-base ./debugger-quickjs-wasm \
  -sASSERTIONS=1 \
  -s -D_GNU_SOURCE \
  '-DCONFIG_VERSION="2021-03-27"' \
  -DCONFIG_STACK_CHECK \
  -DCONFIG_BIGNUM \
  -o ../TodoLangEditor/src/main.js
