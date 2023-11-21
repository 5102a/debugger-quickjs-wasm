
mergeInto(LibraryManager.library, {
  cPostMessage: function (ctx, str) {
    if (globalThis.onDebuggerMessage) {
      globalThis.onDebuggerMessage(ctx, UTF8ToString(str))
    }
  },
});