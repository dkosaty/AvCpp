#pragma once

#include <cstring>

extern "C"
{
#include <libavutil/error.h>

#ifdef av_err2str
#undef av_err2str
static inline std::string av_err2str(int errnum)
{
    static char errbuf[AV_ERROR_MAX_STRING_SIZE];
    std::memset(errbuf, 0, sizeof(errbuf));
    return av_make_error_string(errbuf, AV_ERROR_MAX_STRING_SIZE, errnum);
}
#endif
}