#ifndef B4753655_7CF9_43C5_900B_C408CCCDDE9D
#define B4753655_7CF9_43C5_900B_C408CCCDDE9D
// Author Zed Shaw
// Available [eBook]: learncthehardway.pdf#page=110&zoom=100,85,110
#include <cstring>
#include <cstdio>
#include <cerrno>

class NDebug {
public:
    auto clean_errno() {
        return errno == 0 ? "None" : strerror(errno);
    }

    void ndebug(const char *, ...) {
        fprintf(stderr, "FILE::DEBUG: %s:%d:\t", __FILE__, __LINE__);
    }

    void info_out() {
        ndebug(__FILE__, __LINE__);
        clean_errno();
    }
    
    auto debug_check() {
        info_out();
    }
};

#define CHECK_DEBUG_ARRAY(ARGUMENTS, MEMORY, ...) if(!(ARGUMENTS)){NDebug *n;\
    n->ndebug(MEMORY, ##__VA_ARGS__);}

#endif /* B4753655_7CF9_43C5_900B_C408CCCDDE9D */
