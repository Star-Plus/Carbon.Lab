#include "capi.h"

#include "carbon.h"
#include <string.h>

CarbonHandle init_carbon(const char* config_path, char* errBuf, int errBufSize) {
    try {

        Carbon* carbon = new Carbon(Carbon::init(config_path));
        return (CarbonHandle)carbon;
    } catch (const std::exception& e) {
        if (errBuf && errBufSize > 0) {
            strncpy_s(errBuf, errBufSize, e.what(), errBufSize - 1);
            errBuf[errBufSize - 1] = '\0';
        }
        return nullptr;
    }
}

void free_carbon(CarbonHandle handle) {
    if (handle) {
        Carbon* carbon = (Carbon*)handle;
        delete carbon;
    }
}

int carbon_fs_write(CarbonHandle handle, const char* filename, unsigned long long delay, char* errBuf, int errBufSize) {
    if (!handle) {
        if (errBuf && errBufSize > 0) {
            strncpy_s(errBuf, errBufSize, "Invalid Carbon handle", errBufSize - 1);
            errBuf[errBufSize - 1] = '\0';
        }
        return -1;
    }

    Carbon* carbon = (Carbon*)handle;
    try {
        carbon->fs->write(filename, delay);
        return 0;
    } catch (const std::exception& e) {
        if (errBuf && errBufSize > 0) {
            strncpy_s(errBuf, errBufSize, e.what(), errBufSize - 1);
            errBuf[errBufSize - 1] = '\0';
        }
        return -1;
    }
}

int carbon_fs_trunc(CarbonHandle handle, const char* filename, unsigned long long delay, char* errBuf, int errBufSize) {
    if (!handle) {
        if (errBuf && errBufSize > 0) {
            strncpy_s(errBuf, errBufSize, "Invalid Carbon handle", errBufSize - 1);
            errBuf[errBufSize - 1] = '\0';
        }
        return -1;
    }

    Carbon* carbon = (Carbon*)handle;
    try {
        carbon->fs->trunc(filename, delay);
        return 0;
    } catch (const std::exception& e) {
        if (errBuf && errBufSize > 0) {
            strncpy_s(errBuf, errBufSize, e.what(), errBufSize - 1);
            errBuf[errBufSize - 1] = '\0';
        }
        return -1;
    }
}

int carbon_fs_root(CarbonHandle handle, char* outBuf, int outLen) {
    if (!handle) {
        return -1;
    }

    Carbon* carbon = (Carbon*)handle;
    try {
        auto root = carbon->fs->root();
        if (outBuf && outLen > 0) {
            strncpy_s(outBuf, outLen, root.string().c_str(), outLen - 1);
            outBuf[outLen - 1] = '\0';
        }
        return 0;
    } catch (const std::exception& e) {
        return -1;
    }
}

int carbon_apps_connect(CarbonHandle handle, char* appName, char* outBuf, int outLen) {
    if (!handle) {
        return -1;
    }

    Carbon* carbon = (Carbon*)handle;
    try {
        auto root = carbon->dockerApps->connect(appName);
        if (outBuf && outLen > 0) {
            strncpy_s(outBuf, outLen, root.c_str(), outLen - 1);
            outBuf[outLen - 1] = '\0';
        }
        return 0;
    } catch (const std::exception& e) {
        return -1;
    }
}