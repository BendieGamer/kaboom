#include "utils.h"

#include <stdio.h>
#include <quickjs.h>

static JSValue js_print(
	JSContext *ctx,
	int argc,
	JSValue *argv,
	FILE *output
) {

	for(int i = 0; i < argc; i++) {
		if (i != 0) {
			fprintf(output, " ");
		}
		const char *str = JS_ToCString(ctx, argv[i]);
		if (!str) {
			return JS_EXCEPTION;
		}
		fprintf(output, "%s", str);
		JS_FreeCString(ctx, str);
	}

	fprintf(output, "\n");

	return JS_UNDEFINED;

}

static JSValue console_log(
	JSContext *ctx,
	JSValue this_val,
	int argc,
	JSValue *argv
) {
	return js_print(ctx, argc, argv, stdout);
}

static JSValue console_error(
	JSContext *ctx,
	JSValue this_val,
	int argc,
	JSValue *argv
) {
	return js_print(ctx, argc, argv, stderr);
}

static const JSCFunctionListEntry console_fields[] = {
	JS_CFUNC_DEF("log", 1, console_log),
	JS_CFUNC_DEF("error", 1, console_error),
};

void console_init(JSContext *ctx) {
	JSValue console = JS_NewObject(ctx);
	JS_SetPropertyFunctionList(ctx, console, console_fields, countof(console_fields));
	JSValue gobj = JS_GetGlobalObject(ctx);
	JS_SetPropertyStr(ctx, gobj, "console", console);
}
