# common_float_tables.c
.include "macros.inc"

.section .data, "wa"

.balign 8

/* 000F0F10 800F3E90 0020 */
glabel __sincos_on_quadrant
    .float 0.0, 1.0, 1.0, 0.0, 0.0, -1.0, -1.0, 0.0

/* 000F0F30 800F3EB0 0028 */
glabel __sincos_poly
    .float 3.52876168108e-6, 3.08974705376e-7, -0.000325936503941, -3.65723499272e-5, 0.0158543232828, 0.00249039311893, -0.30842512846, -0.080745510757
    .float 1.0, 0.785398185253
