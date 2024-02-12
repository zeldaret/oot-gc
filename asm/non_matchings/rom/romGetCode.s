glabel romGetCode
/* 068C04 8006E1A4 3CC30001 */  addis   r6, r3, 1
/* 068C08 8006E1A8 88A60EAB */  lbz     r5, 0xeab(r6)
/* 068C0C 8006E1AC 38000000 */  li      r0, 0
/* 068C10 8006E1B0 38600001 */  li      r3, 1
/* 068C14 8006E1B4 98A40000 */  stb     r5, 0(r4)
/* 068C18 8006E1B8 88A60EAC */  lbz     r5, 0xeac(r6)
/* 068C1C 8006E1BC 98A40001 */  stb     r5, 1(r4)
/* 068C20 8006E1C0 88A60EAD */  lbz     r5, 0xead(r6)
/* 068C24 8006E1C4 98A40002 */  stb     r5, 2(r4)
/* 068C28 8006E1C8 88A60EAE */  lbz     r5, 0xeae(r6)
/* 068C2C 8006E1CC 98A40003 */  stb     r5, 3(r4)
/* 068C30 8006E1D0 98040004 */  stb     r0, 4(r4)
/* 068C34 8006E1D4 4E800020 */  blr     
