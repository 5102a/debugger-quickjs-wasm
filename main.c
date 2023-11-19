#include "../quickjs/quickjs.h"
#include "./ffi.h"
#include "quickjs/quickjs-debugger-ipc.h"
#include <emscripten.h>
#include <emscripten/console.h>
#include <string.h>

#ifndef EM_PORT_API
#if defined(__EMSCRIPTEN__)
#if defined(__cplusplus)
#define EM_PORT_API(rettype) extern "C" rettype EMSCRIPTEN_KEEPALIVE
#else
#define EM_PORT_API(rettype) rettype EMSCRIPTEN_KEEPALIVE
#endif
#else
#if defined(__cplusplus)
#define EM_PORT_API(rettype) extern "C" rettype
#else
#define EM_PORT_API(rettype) rettype
#endif
#endif
#endif

#define EXTERN_C

typedef void (*CallbackFunc)(const char *str);

void post_message(const char *str, JSContext *ctx) { request(str, ctx); }


EM_PORT_API(void)
js_post_message(const char *str, JSContext *ctx)
{
  JSDebuggerInfo *info = js_debugger_info(JS_GetRuntime(ctx));
  info->message_buffer = (char *)str;
  info->message_buffer_length = strlen(str);
  info->buffer_is_full = 1;
}

// 导出 api 供 js 调用
EM_PORT_API(const char *)
eval(const char *str)
{
  // 运行时环境
  JSRuntime *runtime = JS_NewRuntime();

  // 获取运行上下文
  JSContext *ctx = JS_NewContext(runtime);

  // 在此上下文中eval 执行js 代码
  JSValue result =
      JS_Eval(ctx, str, strlen(str), "d:\\hub\\quickjs\\test2.js", JS_EVAL_TYPE_GLOBAL);
  // post_message(str, ctx);

  // 异常情况
  if (JS_IsException(result))
  {
    JSValue realException = JS_GetException(ctx);
    return JS_ToCString(ctx, realException);
  }

  JSValue json = JS_JSONStringify(ctx, result, JS_UNDEFINED, JS_UNDEFINED);

  // 释放内存
  JS_FreeValue(ctx, result);

  return JS_ToCString(ctx, json);
}
