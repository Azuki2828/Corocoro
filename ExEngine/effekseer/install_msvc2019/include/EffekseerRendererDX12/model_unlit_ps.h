#if 0
//
// Generated by Microsoft (R) HLSL Shader Compiler 9.29.952.3111
//
//
//   fxc /Zpc /Tps_4_0 /Emain /Fh ShaderHeader/model_unlit_ps.h
//    Shader/model_unlit_ps.fx
//
//
// Buffer Definitions: 
//
// cbuffer PS_ConstanBuffer
// {
//
//   float4 _117_fLightDirection;       // Offset:    0 Size:    16 [unused]
//   float4 _117_fLightColor;           // Offset:   16 Size:    16 [unused]
//   float4 _117_fLightAmbient;         // Offset:   32 Size:    16 [unused]
//   float4 _117_fFlipbookParameter;    // Offset:   48 Size:    16 [unused]
//   float4 _117_fUVDistortionParameter;// Offset:   64 Size:    16 [unused]
//   float4 _117_fBlendTextureParameter;// Offset:   80 Size:    16 [unused]
//   float4 _117_fCameraFrontDirection; // Offset:   96 Size:    16 [unused]
//   float4 _117_fFalloffParameter;     // Offset:  112 Size:    16 [unused]
//   float4 _117_fFalloffBeginColor;    // Offset:  128 Size:    16 [unused]
//   float4 _117_fFalloffEndColor;      // Offset:  144 Size:    16 [unused]
//   float4 _117_fEmissiveScaling;      // Offset:  160 Size:    16
//   float4 _117_fEdgeColor;            // Offset:  176 Size:    16 [unused]
//   float4 _117_fEdgeParameter;        // Offset:  192 Size:    16 [unused]
//   float4 _117_softParticleParam;     // Offset:  208 Size:    16
//   float4 _117_reconstructionParam1;  // Offset:  224 Size:    16
//   float4 _117_reconstructionParam2;  // Offset:  240 Size:    16
//   float4 _117_mUVInversedBack;       // Offset:  256 Size:    16
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim Slot Elements
// ------------------------------ ---------- ------- ----------- ---- --------
// sampler_colorTex                  sampler      NA          NA    0        1
// sampler_depthTex                  sampler      NA          NA    1        1
// _colorTex                         texture  float4          2d    0        1
// _depthTex                         texture  float4          2d    1        1
// PS_ConstanBuffer                  cbuffer      NA          NA    1        1
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// TEXCOORD                 0   xyzw        0     NONE  float   xyzw
// TEXCOORD                 1   xy          1     NONE  float   xy  
// TEXCOORD                 2   xyzw        2     NONE  float   xyzw
// SV_Position              0   xyzw        3      POS  float       
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue Format   Used
// -------------------- ----- ------ -------- -------- ------ ------
// SV_Target                0   xyzw        0   TARGET  float   xyzw
//
ps_4_0
dcl_constantbuffer cb1[17], immediateIndexed
dcl_sampler s0, mode_default
dcl_sampler s1, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_resource_texture2d (float,float,float,float) t1
dcl_input_ps linear centroid v0.xyzw
dcl_input_ps linear centroid v1.xy
dcl_input_ps linear v2.xyzw
dcl_output o0.xyzw
dcl_temps 3
sample r0.xyzw, v1.xyxx, t0.xyzw, s0
mul r0.xyzw, r0.xyzw, v0.xyzw
ne r1.x, cb1[13].w, l(0.000000)
if_nz r1.x
  div r1.yzw, v2.xxyz, v2.wwww
  add r1.yz, r1.yyzy, l(0.000000, 1.000000, 1.000000, 0.000000)
  mul r2.x, r1.y, l(0.500000)
  mad r1.y, -r1.z, l(0.500000), l(1.000000)
  mad r2.z, cb1[16].y, r1.y, cb1[16].x
  sample r2.xyzw, r2.xzxx, t1.xyzw, s1
  mad r1.x, r2.x, cb1[14].x, cb1[14].y
  mad r1.yz, r1.xxwx, cb1[15].wwww, -cb1[15].yyyy
  mad r1.xw, -r1.xxxw, cb1[15].zzzz, cb1[15].xxxx
  div r1.xy, r1.yzyy, r1.xwxx
  add r1.x, -r1.x, r1.y
  add r1.y, -r1.y, -cb1[13].z
  div r1.xy, r1.xyxx, cb1[13].xyxx
  min_sat r1.x, r1.y, r1.x
  mul r0.w, r0.w, r1.x
endif 
eq r1.x, r0.w, l(0.000000)
discard r1.x
mul r0.xyz, r0.xyzx, cb1[10].xxxx
mov o0.xyzw, r0.xyzw
ret 
// Approximately 25 instruction slots used
#endif

const BYTE g_main[] =
{
     68,  88,  66,  67,  47, 180, 
    168,  14,  55, 222, 237,  37, 
    164,  20, 158, 240,  35, 180, 
     66, 229,   1,   0,   0,   0, 
    112,   9,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
    184,   4,   0,   0,  64,   5, 
      0,   0, 116,   5,   0,   0, 
    244,   8,   0,   0,  82,  68, 
     69,  70, 124,   4,   0,   0, 
      1,   0,   0,   0,   4,   1, 
      0,   0,   5,   0,   0,   0, 
     28,   0,   0,   0,   0,   4, 
    255, 255,  16,   1,   0,   0, 
     74,   4,   0,   0, 188,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
    205,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0, 222,   0,   0,   0, 
      2,   0,   0,   0,   5,   0, 
      0,   0,   4,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   0,   0,   0, 232,   0, 
      0,   0,   2,   0,   0,   0, 
      5,   0,   0,   0,   4,   0, 
      0,   0, 255, 255, 255, 255, 
      1,   0,   0,   0,   1,   0, 
      0,   0,  13,   0,   0,   0, 
    242,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0, 115,  97, 109, 112, 
    108, 101, 114,  95,  99, 111, 
    108, 111, 114,  84, 101, 120, 
      0, 115,  97, 109, 112, 108, 
    101, 114,  95, 100, 101, 112, 
    116, 104,  84, 101, 120,   0, 
     95,  99, 111, 108, 111, 114, 
     84, 101, 120,   0,  95, 100, 
    101, 112, 116, 104,  84, 101, 
    120,   0,  80,  83,  95,  67, 
    111, 110, 115, 116,  97, 110, 
     66, 117, 102, 102, 101, 114, 
      0, 171, 242,   0,   0,   0, 
     17,   0,   0,   0,  28,   1, 
      0,   0,  16,   1,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 180,   2,   0,   0, 
      0,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
    204,   2,   0,   0,   0,   0, 
      0,   0, 220,   2,   0,   0, 
     16,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
    204,   2,   0,   0,   0,   0, 
      0,   0, 237,   2,   0,   0, 
     32,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
    204,   2,   0,   0,   0,   0, 
      0,   0,   0,   3,   0,   0, 
     48,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
    204,   2,   0,   0,   0,   0, 
      0,   0,  24,   3,   0,   0, 
     64,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
    204,   2,   0,   0,   0,   0, 
      0,   0,  52,   3,   0,   0, 
     80,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
    204,   2,   0,   0,   0,   0, 
      0,   0,  80,   3,   0,   0, 
     96,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
    204,   2,   0,   0,   0,   0, 
      0,   0, 107,   3,   0,   0, 
    112,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
    204,   2,   0,   0,   0,   0, 
      0,   0, 130,   3,   0,   0, 
    128,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
    204,   2,   0,   0,   0,   0, 
      0,   0, 154,   3,   0,   0, 
    144,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
    204,   2,   0,   0,   0,   0, 
      0,   0, 176,   3,   0,   0, 
    160,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    204,   2,   0,   0,   0,   0, 
      0,   0, 198,   3,   0,   0, 
    176,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
    204,   2,   0,   0,   0,   0, 
      0,   0, 214,   3,   0,   0, 
    192,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
    204,   2,   0,   0,   0,   0, 
      0,   0, 234,   3,   0,   0, 
    208,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    204,   2,   0,   0,   0,   0, 
      0,   0,   1,   4,   0,   0, 
    224,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    204,   2,   0,   0,   0,   0, 
      0,   0,  27,   4,   0,   0, 
    240,   0,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    204,   2,   0,   0,   0,   0, 
      0,   0,  53,   4,   0,   0, 
      0,   1,   0,   0,  16,   0, 
      0,   0,   2,   0,   0,   0, 
    204,   2,   0,   0,   0,   0, 
      0,   0,  95,  49,  49,  55, 
     95, 102,  76, 105, 103, 104, 
    116,  68, 105, 114, 101,  99, 
    116, 105, 111, 110,   0, 171, 
    171, 171,   1,   0,   3,   0, 
      1,   0,   4,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     95,  49,  49,  55,  95, 102, 
     76, 105, 103, 104, 116,  67, 
    111, 108, 111, 114,   0,  95, 
     49,  49,  55,  95, 102,  76, 
    105, 103, 104, 116,  65, 109, 
     98, 105, 101, 110, 116,   0, 
     95,  49,  49,  55,  95, 102, 
     70, 108, 105, 112,  98, 111, 
    111, 107,  80,  97, 114,  97, 
    109, 101, 116, 101, 114,   0, 
     95,  49,  49,  55,  95, 102, 
     85,  86,  68, 105, 115, 116, 
    111, 114, 116, 105, 111, 110, 
     80,  97, 114,  97, 109, 101, 
    116, 101, 114,   0,  95,  49, 
     49,  55,  95, 102,  66, 108, 
    101, 110, 100,  84, 101, 120, 
    116, 117, 114, 101,  80,  97, 
    114,  97, 109, 101, 116, 101, 
    114,   0,  95,  49,  49,  55, 
     95, 102,  67,  97, 109, 101, 
    114,  97,  70, 114, 111, 110, 
    116,  68, 105, 114, 101,  99, 
    116, 105, 111, 110,   0,  95, 
     49,  49,  55,  95, 102,  70, 
     97, 108, 108, 111, 102, 102, 
     80,  97, 114,  97, 109, 101, 
    116, 101, 114,   0,  95,  49, 
     49,  55,  95, 102,  70,  97, 
    108, 108, 111, 102, 102,  66, 
    101, 103, 105, 110,  67, 111, 
    108, 111, 114,   0,  95,  49, 
     49,  55,  95, 102,  70,  97, 
    108, 108, 111, 102, 102,  69, 
    110, 100,  67, 111, 108, 111, 
    114,   0,  95,  49,  49,  55, 
     95, 102,  69, 109, 105, 115, 
    115, 105, 118, 101,  83,  99, 
     97, 108, 105, 110, 103,   0, 
     95,  49,  49,  55,  95, 102, 
     69, 100, 103, 101,  67, 111, 
    108, 111, 114,   0,  95,  49, 
     49,  55,  95, 102,  69, 100, 
    103, 101,  80,  97, 114,  97, 
    109, 101, 116, 101, 114,   0, 
     95,  49,  49,  55,  95, 115, 
    111, 102, 116,  80,  97, 114, 
    116, 105,  99, 108, 101,  80, 
     97, 114,  97, 109,   0,  95, 
     49,  49,  55,  95, 114, 101, 
     99, 111, 110, 115, 116, 114, 
    117,  99, 116, 105, 111, 110, 
     80,  97, 114,  97, 109,  49, 
      0,  95,  49,  49,  55,  95, 
    114, 101,  99, 111, 110, 115, 
    116, 114, 117,  99, 116, 105, 
    111, 110,  80,  97, 114,  97, 
    109,  50,   0,  95,  49,  49, 
     55,  95, 109,  85,  86,  73, 
    110, 118, 101, 114, 115, 101, 
    100,  66,  97,  99, 107,   0, 
     77, 105,  99, 114, 111, 115, 
    111, 102, 116,  32,  40,  82, 
     41,  32,  72,  76,  83,  76, 
     32,  83, 104,  97, 100, 101, 
    114,  32,  67, 111, 109, 112, 
    105, 108, 101, 114,  32,  57, 
     46,  50,  57,  46,  57,  53, 
     50,  46,  51,  49,  49,  49, 
      0, 171,  73,  83,  71,  78, 
    128,   0,   0,   0,   4,   0, 
      0,   0,   8,   0,   0,   0, 
    104,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,  15,  15,   0,   0, 
    104,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,   3,   3,   0,   0, 
    104,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,  15,  15,   0,   0, 
    113,   0,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   0, 
      3,   0,   0,   0,   3,   0, 
      0,   0,  15,   0,   0,   0, 
     84,  69,  88,  67,  79,  79, 
     82,  68,   0,  83,  86,  95, 
     80, 111, 115, 105, 116, 105, 
    111, 110,   0, 171, 171, 171, 
     79,  83,  71,  78,  44,   0, 
      0,   0,   1,   0,   0,   0, 
      8,   0,   0,   0,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,  83,  86, 
     95,  84,  97, 114, 103, 101, 
    116,   0, 171, 171,  83,  72, 
     68,  82, 120,   3,   0,   0, 
     64,   0,   0,   0, 222,   0, 
      0,   0,  89,   0,   0,   4, 
     70, 142,  32,   0,   1,   0, 
      0,   0,  17,   0,   0,   0, 
     90,   0,   0,   3,   0,  96, 
     16,   0,   0,   0,   0,   0, 
     90,   0,   0,   3,   0,  96, 
     16,   0,   1,   0,   0,   0, 
     88,  24,   0,   4,   0, 112, 
     16,   0,   0,   0,   0,   0, 
     85,  85,   0,   0,  88,  24, 
      0,   4,   0, 112,  16,   0, 
      1,   0,   0,   0,  85,  85, 
      0,   0,  98,  24,   0,   3, 
    242,  16,  16,   0,   0,   0, 
      0,   0,  98,  24,   0,   3, 
     50,  16,  16,   0,   1,   0, 
      0,   0,  98,  16,   0,   3, 
    242,  16,  16,   0,   2,   0, 
      0,   0, 101,   0,   0,   3, 
    242,  32,  16,   0,   0,   0, 
      0,   0, 104,   0,   0,   2, 
      3,   0,   0,   0,  69,   0, 
      0,   9, 242,   0,  16,   0, 
      0,   0,   0,   0,  70,  16, 
     16,   0,   1,   0,   0,   0, 
     70, 126,  16,   0,   0,   0, 
      0,   0,   0,  96,  16,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   7, 242,   0,  16,   0, 
      0,   0,   0,   0,  70,  14, 
     16,   0,   0,   0,   0,   0, 
     70,  30,  16,   0,   0,   0, 
      0,   0,  57,   0,   0,   8, 
     18,   0,  16,   0,   1,   0, 
      0,   0,  58, 128,  32,   0, 
      1,   0,   0,   0,  13,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  31,   0, 
      4,   3,  10,   0,  16,   0, 
      1,   0,   0,   0,  14,   0, 
      0,   7, 226,   0,  16,   0, 
      1,   0,   0,   0,   6,  25, 
     16,   0,   2,   0,   0,   0, 
    246,  31,  16,   0,   2,   0, 
      0,   0,   0,   0,   0,  10, 
     98,   0,  16,   0,   1,   0, 
      0,   0,  86,   6,  16,   0, 
      1,   0,   0,   0,   2,  64, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 128,  63,   0,   0, 
    128,  63,   0,   0,   0,   0, 
     56,   0,   0,   7,  18,   0, 
     16,   0,   2,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,  63,  50,   0, 
      0,  10,  34,   0,  16,   0, 
      1,   0,   0,   0,  42,   0, 
     16, 128,  65,   0,   0,   0, 
      1,   0,   0,   0,   1,  64, 
      0,   0,   0,   0,   0,  63, 
      1,  64,   0,   0,   0,   0, 
    128,  63,  50,   0,   0,  11, 
     66,   0,  16,   0,   2,   0, 
      0,   0,  26, 128,  32,   0, 
      1,   0,   0,   0,  16,   0, 
      0,   0,  26,   0,  16,   0, 
      1,   0,   0,   0,  10, 128, 
     32,   0,   1,   0,   0,   0, 
     16,   0,   0,   0,  69,   0, 
      0,   9, 242,   0,  16,   0, 
      2,   0,   0,   0, 134,   0, 
     16,   0,   2,   0,   0,   0, 
     70, 126,  16,   0,   1,   0, 
      0,   0,   0,  96,  16,   0, 
      1,   0,   0,   0,  50,   0, 
      0,  11,  18,   0,  16,   0, 
      1,   0,   0,   0,  10,   0, 
     16,   0,   2,   0,   0,   0, 
     10, 128,  32,   0,   1,   0, 
      0,   0,  14,   0,   0,   0, 
     26, 128,  32,   0,   1,   0, 
      0,   0,  14,   0,   0,   0, 
     50,   0,   0,  12,  98,   0, 
     16,   0,   1,   0,   0,   0, 
      6,   3,  16,   0,   1,   0, 
      0,   0, 246, 143,  32,   0, 
      1,   0,   0,   0,  15,   0, 
      0,   0,  86, 133,  32, 128, 
     65,   0,   0,   0,   1,   0, 
      0,   0,  15,   0,   0,   0, 
     50,   0,   0,  12, 146,   0, 
     16,   0,   1,   0,   0,   0, 
      6,  12,  16, 128,  65,   0, 
      0,   0,   1,   0,   0,   0, 
    166, 138,  32,   0,   1,   0, 
      0,   0,  15,   0,   0,   0, 
      6, 128,  32,   0,   1,   0, 
      0,   0,  15,   0,   0,   0, 
     14,   0,   0,   7,  50,   0, 
     16,   0,   1,   0,   0,   0, 
    150,   5,  16,   0,   1,   0, 
      0,   0, 198,   0,  16,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   8,  18,   0,  16,   0, 
      1,   0,   0,   0,  10,   0, 
     16, 128,  65,   0,   0,   0, 
      1,   0,   0,   0,  26,   0, 
     16,   0,   1,   0,   0,   0, 
      0,   0,   0,  10,  34,   0, 
     16,   0,   1,   0,   0,   0, 
     26,   0,  16, 128,  65,   0, 
      0,   0,   1,   0,   0,   0, 
     42, 128,  32, 128,  65,   0, 
      0,   0,   1,   0,   0,   0, 
     13,   0,   0,   0,  14,   0, 
      0,   8,  50,   0,  16,   0, 
      1,   0,   0,   0,  70,   0, 
     16,   0,   1,   0,   0,   0, 
     70, 128,  32,   0,   1,   0, 
      0,   0,  13,   0,   0,   0, 
     51,  32,   0,   7,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     26,   0,  16,   0,   1,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,  56,   0, 
      0,   7, 130,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   1,   0, 
      0,   0,  21,   0,   0,   1, 
     24,   0,   0,   7,  18,   0, 
     16,   0,   1,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  13,   0, 
      4,   3,  10,   0,  16,   0, 
      1,   0,   0,   0,  56,   0, 
      0,   8, 114,   0,  16,   0, 
      0,   0,   0,   0,  70,   2, 
     16,   0,   0,   0,   0,   0, 
      6, 128,  32,   0,   1,   0, 
      0,   0,  10,   0,   0,   0, 
     54,   0,   0,   5, 242,  32, 
     16,   0,   0,   0,   0,   0, 
     70,  14,  16,   0,   0,   0, 
      0,   0,  62,   0,   0,   1, 
     83,  84,  65,  84, 116,   0, 
      0,   0,  25,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,   4,   0,   0,   0, 
     13,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   2,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      4,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0
};