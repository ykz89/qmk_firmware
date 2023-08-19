// ハードウェアライブラリのアサーションを無効にする
#ifdef PARAM_ASSERTIONS_ENABLED
#undef PARAM_ASSERTIONS_ENABLED
#endif
#define PARAM_ASSERTIONS_ENABLED(x) 0

