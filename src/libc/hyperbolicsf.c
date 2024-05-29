#include "dolphin/types.h"
#include "intrinsics.h"

// Referenced by a some unused function in this file
// bug? wrong return type (f64 instead of f32)
f64 fabsf__Ff(f32 x) { return __fabs((f64)x); }
