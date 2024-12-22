#ifndef MACROS_HPP
#define MACROS_HPP

#if defined(DEBUG) || defined(NDEBUG) || defined(USE_VALIDATION_LAYERS)
#define CHECK_BUILD_CONFIG 1
#else
#define CHECK_BUILD_CONFIG 0
#endif

#define TRY_EXECVK(fn, errorMsg, successMsg)	\
if (fn != VK_SUCCESS)							\
{												\
	throw std::runtime_error(errorMsg);			\
}												\
LOG_SUCCESS(successMsg)	

#endif
