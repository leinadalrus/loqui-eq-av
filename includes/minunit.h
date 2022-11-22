#ifndef C9A9F3B6_43A0_4D3B_B109_F9394380E9B7
#define C9A9F3B6_43A0_4D3B_B109_F9394380E9B7

#pragma GCC diagnostic warning "-Wuninitialized"
#pragma GCC diagnostic warning "-Wconversion"
#pragma GCC diagnostic error "-Wold-style-cast"
#pragma GCC diagnostic push DIAGNOSE_PUSHES(message)
#pragma GCC diagnostic pop DIAGNOSE_POPS(message)

#include "ndbg.h"

// "JTN002 - MinUnit -- a minimal unit testing framework for C"
// Available [online]: https://jera.com/techinfo/jtns/jtn002
/* file: minunit.h */

#define mu_assert(message, test) do { if (!(test)) log_err(message) \
return message; } while (0)
#define mu_run_test(test) do { \
ndebug("%s\t", #test); \
char *message = test(); tests_run++; \
if (message) return message; } while (0)

#define mu_test_start() const char *message_value

extern int tests_run;

#pragma message("Unit Test Starts:\n\t%s:\t%d" __FILE__ __LINE__)
#pragma message(mu_run_test(__FILE__))
#pragma message(tests_run)

#endif /* C9A9F3B6_43A0_4D3B_B109_F9394380E9B7 */
