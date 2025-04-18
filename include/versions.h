#ifndef _VERSIONS_H
#define _VERSIONS_H

// The VERSION macro will be set to one of these version numbers.
#define MQ_J 1
#define MQ_U 2
#define MQ_E 3
#define CE_J 4
#define CE_U 5
#define CE_E 6
#define MM_J 7
#define MM_U 8
#define MM_E 9

#define IS_OOT_JP (VERSION == MQ_J || VERSION == CE_J)
#define IS_OOT_US (VERSION == MQ_U || VERSION == CE_U)
#define IS_OOT_EU (VERSION == MQ_E || VERSION == CE_E)
#define IS_OOT (IS_OOT_JP || IS_OOT_US || IS_OOT_EU)

#define IS_MM_JP (VERSION == MM_J)
#define IS_MM_US (VERSION == MM_U)
#define IS_MM_EU (VERSION == MM_E)
#define IS_MM (IS_MM_JP || IS_MM_US || IS_MM_EU)

#define IS_MQ_JP (VERSION == MQ_J)
#define IS_MQ_US (VERSION == MQ_U)
#define IS_MQ_EU (VERSION == MQ_E)
#define IS_MQ (IS_MQ_JP || IS_MQ_US || IS_MQ_EU)

#define IS_CE_JP (VERSION == CE_J || VERSION == MM_J)
#define IS_CE_US (VERSION == CE_U || VERSION == MM_U)
#define IS_CE_EU (VERSION == CE_E || VERSION == MM_E)
#define IS_CE (IS_CE_JP || IS_CE_US || IS_CE_EU)

#define IS_JP (IS_OOT_JP || IS_MM_JP)
#define IS_US (IS_OOT_US || IS_MM_US)
#define IS_EU (IS_OOT_EU || IS_MM_EU)

#endif
