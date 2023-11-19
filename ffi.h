#include "quickjs/quickjs.h"
extern const char *request(const char *str, JSContext *ctx);

extern void js_log(const char *str);

void post_message(const char *str, JSContext *ctx);
