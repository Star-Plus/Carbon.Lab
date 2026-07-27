#include "CarbonExport.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void*CarbonHandle;

CARBON_EXPORT CarbonHandle init_carbon(const char* config_path, char* errBuf, int errBufSize);
CARBON_EXPORT void free_carbon(CarbonHandle handle);

CARBON_EXPORT int carbon_fs_write(CarbonHandle handle, const char* filename, unsigned long long delay, char* errBuf, int errBufSize);
CARBON_EXPORT int carbon_fs_trunc(CarbonHandle handle, const char* filename, unsigned long long delay, char* errBuf, int errBufSize);
CARBON_EXPORT int carbon_fs_root(CarbonHandle handle, char* outBuf, int outLen);

CARBON_EXPORT int carbon_app_connect(CarbonHandle handle, char* appName, char* port, char* outBuf, int outLen, char* errBuf, int errBufSize);

#ifdef __cplusplus
}
#endif