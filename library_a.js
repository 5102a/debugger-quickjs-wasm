
mergeInto(LibraryManager.library, {
  request: function (str, ctx) {
    if (globalThis.onDebuggerMessage) {
      globalThis.onDebuggerMessage(UTF8ToString(str), ctx)
    }
  },
  js_log: function (str) {
    console.log('js_log:', str);
  },
});