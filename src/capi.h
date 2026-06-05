#ifdef __cplusplus
extern "C" {
#endif

typedef void*CarbonHandle;

CarbonHandle init_carbon(const char* config_path, char* errBuf, int errBufSize);
void free_carbon(CarbonHandle handle);

int carbon_fs_write(CarbonHandle handle, const char* filename, unsigned long long delay, char* errBuf, int errBufSize);
int carbon_fs_trunc(CarbonHandle handle, const char* filename, unsigned long long delay, char* errBuf, int errBufSize);
int carbon_fs_root(CarbonHandle handle, char* outBuf, int outLen);

int carbon_app_connect(CarbonHandle handle, char* appName, char* outBuf, int outLen, char* errBuf, int errBufSize);

#ifdef __cplusplus
}
#endif