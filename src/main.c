#define OK_COLOR_IMPLEMENTATION

#include <janet.h>
#include "ok_color.h"

static float idx_getfloat(JanetView idx, int index) {
  if (index >= idx.len) {
    janet_panicf("index %d outside of range [0, %d)", idx.len);
  }
  if (!janet_checktype(idx.items[index], JANET_NUMBER)) {
    janet_panicf("expected number, got %v", idx.items[index]);
  }
  return (float) janet_unwrap_number(idx.items[index]);
}

static HSL jokcolor_gethsl(const Janet *argv, int32_t n) {
  Janet x = argv[n];
  const Janet *els = NULL;
  int32_t len = 0;
  if (janet_indexed_view(x, &els, &len)) {
    if (len == 3) {
      JanetView idx = janet_getindexed(argv, n);
      return (HSL) {
        idx_getfloat(idx, 0),
        idx_getfloat(idx, 1),
        idx_getfloat(idx, 2),
      };
    } else {
      janet_panicf("expected 3 color components, got %d", len);
    }
  } else {
    janet_panic("expected vec to be an indexed type");
  }
}

static RGB jokcolor_getrgb(const Janet *argv, int32_t n) {
  Janet x = argv[n];
  const Janet *els = NULL;
  int32_t len = 0;
  if (janet_indexed_view(x, &els, &len)) {
    if (len == 3) {
      JanetView idx = janet_getindexed(argv, n);
      return (RGB) {
        idx_getfloat(idx, 0),
        idx_getfloat(idx, 1),
        idx_getfloat(idx, 2),
      };
    } else {
      janet_panicf("expected 3 color components, got %d", len);
    }
  } else {
    janet_panic("expected vec to be an indexed type");
  }
}

static HSV jokcolor_gethsv(const Janet *argv, int32_t n) {
  Janet x = argv[n];
  const Janet *els = NULL;
  int32_t len = 0;
  if (janet_indexed_view(x, &els, &len)) {
    if (len == 3) {
      JanetView idx = janet_getindexed(argv, n);
      return (HSV) {
        idx_getfloat(idx, 0),
        idx_getfloat(idx, 1),
        idx_getfloat(idx, 2),
      };
    } else {
      janet_panicf("expected 3 color components, got %d", len);
    }
  } else {
    janet_panic("expected vec to be an indexed type");
  }
}

static LCh jokcolor_getlch(const Janet *argv, int32_t n) {
  Janet x = argv[n];
  const Janet *els = NULL;
  int32_t len = 0;
  if (janet_indexed_view(x, &els, &len)) {
    if (len == 3) {
      JanetView idx = janet_getindexed(argv, n);
      return (LCh) {
        idx_getfloat(idx, 0),
        idx_getfloat(idx, 1),
        idx_getfloat(idx, 2),
      };
    } else {
      janet_panicf("expected 3 color components, got %d", len);
    }
  } else {
    janet_panic("expected vec to be an indexed type");
  }
}

static Lab jokcolor_getlab(const Janet *argv, int32_t n) {
  Janet x = argv[n];
  const Janet *els = NULL;
  int32_t len = 0;
  if (janet_indexed_view(x, &els, &len)) {
    if (len == 3) {
      JanetView idx = janet_getindexed(argv, n);
      return (Lab) {
        idx_getfloat(idx, 0),
        idx_getfloat(idx, 1),
        idx_getfloat(idx, 2),
      };
    } else {
      janet_panicf("expected 3 color components, got %d", len);
    }
  } else {
    janet_panic("expected vec to be an indexed type");
  }
}

static Janet cfun_okhsl_to_srgb(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  HSL hsl = jokcolor_gethsl(argv, 0);
  RGB rgb = okhsl_to_srgb(hsl);
  JanetArray *array = janet_array(3);
  array->count = 3;
  array->data[0] = janet_wrap_number(rgb.r);
  array->data[1] = janet_wrap_number(rgb.g);
  array->data[2] = janet_wrap_number(rgb.b);
  return janet_wrap_array(array);
}

static Janet cfun_srgb_to_okhsl(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  RGB rgb = jokcolor_getrgb(argv, 0);
  HSL hsl = srgb_to_okhsl(rgb);
  JanetArray *array = janet_array(3);
  array->count = 3;
  array->data[0] = janet_wrap_number(hsl.h);
  array->data[1] = janet_wrap_number(hsl.s);
  array->data[2] = janet_wrap_number(hsl.l);
  return janet_wrap_array(array);
}

static Janet cfun_okhsv_to_srgb(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  HSV hsv = jokcolor_gethsv(argv, 0);
  RGB rgb = okhsv_to_srgb(hsv);
  JanetArray *array = janet_array(3);
  array->count = 3;
  array->data[0] = janet_wrap_number(rgb.r);
  array->data[1] = janet_wrap_number(rgb.g);
  array->data[2] = janet_wrap_number(rgb.b);
  return janet_wrap_array(array);
}

static Janet cfun_srgb_to_okhsv(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  RGB rgb = jokcolor_getrgb(argv, 0);
  HSV hsv = srgb_to_okhsv(rgb);
  JanetArray *array = janet_array(3);
  array->count = 3;
  array->data[0] = janet_wrap_number(hsv.h);
  array->data[1] = janet_wrap_number(hsv.s);
  array->data[2] = janet_wrap_number(hsv.v);
  return janet_wrap_array(array);
}

static Janet cfun_oklab_to_srgb(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  Lab lab = jokcolor_getlab(argv, 0);
  RGB rgb = oklab_to_srgb(lab);
  JanetArray *array = janet_array(3);
  array->count = 3;
  array->data[0] = janet_wrap_number(rgb.r);
  array->data[1] = janet_wrap_number(rgb.g);
  array->data[2] = janet_wrap_number(rgb.b);
  return janet_wrap_array(array);
}

static Janet cfun_srgb_to_oklab(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  RGB rgb = jokcolor_getrgb(argv, 0);
  Lab lab = srgb_to_oklab(rgb);
  JanetArray *array = janet_array(3);
  array->count = 3;
  array->data[0] = janet_wrap_number(lab.L);
  array->data[1] = janet_wrap_number(lab.a);
  array->data[2] = janet_wrap_number(lab.b);
  return janet_wrap_array(array);
}

static Janet cfun_oklch_to_srgb(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  LCh lch = jokcolor_getlch(argv, 0);
  RGB rgb = oklch_to_srgb(lch);
  JanetArray *array = janet_array(3);
  array->count = 3;
  array->data[0] = janet_wrap_number(rgb.r);
  array->data[1] = janet_wrap_number(rgb.g);
  array->data[2] = janet_wrap_number(rgb.b);
  return janet_wrap_array(array);
}

static Janet cfun_srgb_to_oklch(int32_t argc, Janet *argv) {
  janet_fixarity(argc, 1);
  RGB rgb = jokcolor_getrgb(argv, 0);
  LCh lch = srgb_to_oklch(rgb);
  JanetArray *array = janet_array(3);
  array->count = 3;
  array->data[0] = janet_wrap_number(lch.L);
  array->data[1] = janet_wrap_number(lch.C);
  array->data[2] = janet_wrap_number(lch.h);
  return janet_wrap_array(array);
}

static JanetReg core_cfuns[] = {
  {"okhsl-to-srgb", cfun_okhsl_to_srgb,
    "(okhsl-to-srgb okhsl)\n\n"
    "Convert OkHSL to sRGB"
  },
  {"srgb-to-okhsl", cfun_srgb_to_okhsl,
    "(srgb-to-okhsl srgb)\n\n"
    "Convert sRGB to OkHSL"
  },
  {"okhsv-to-srgb", cfun_okhsv_to_srgb,
    "(okhsv-to-srgb okhsv)\n\n"
    "Convert OkHSV to sRGB"
  },
  {"srgb-to-okhsv", cfun_srgb_to_okhsv,
    "(srgb-to-okhsv srgb)\n\n"
    "Convert sRGB to OkHSV"
  },
  {"oklab-to-srgb", cfun_oklab_to_srgb,
    "(oklab-to-srgb oklab)\n\n"
    "Convert OkLab to sRGB"
  },
  {"srgb-to-oklab", cfun_srgb_to_oklab,
    "(srgb-to-oklab srgb)\n\n"
    "Convert sRGB to OkLab"
  },
  {"oklch-to-srgb", cfun_oklch_to_srgb,
    "(oklch-to-srgb oklch)\n\n"
    "Convert OkLCh to sRGB"
  },
  {"srgb-to-oklch", cfun_srgb_to_oklch,
    "(srgb-to-oklch srgb)\n\n"
    "Convert sRGB to OkLCh"
  },
};

JANET_MODULE_ENTRY(JanetTable *env) {
  janet_cfuns(env, "jokcolor", core_cfuns);
}
