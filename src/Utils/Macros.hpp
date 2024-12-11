#ifndef MACROS_HPP
#define MACROS_HPP

#if defined(DEBUG) || defined(NDEBUG) || defined(USE_VALIDATION_LAYERS)
#define CHECK_BUILD_CONFIG 1
#else
#define CHECK_BUILD_CONFIG 0
#endif

#endif
