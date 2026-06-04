package symbols

// These vars start as nil and are populated once by the loader at runtime
// via purego.RegisterLibFunc. After that they behave like normal Go function calls.
//
// Signatures mirror capi.h exactly:
//
//   CarbonHandle init_carbon(const char* config_path, char* errBuf, int errBufSize)
//   void         free_carbon(CarbonHandle handle)
//   int          carbon_fs_write(CarbonHandle, const char*, unsigned long long, char*, int)
//   int          carbon_fs_trunc(CarbonHandle, const char*, unsigned long long, char*, int)
//   int          carbon_fs_root(CarbonHandle, char*, int)

var (
	// FnInitCarbon maps to init_carbon.
	// Returns a non-nil uintptr handle on success, 0 on failure (errBuf is populated).
	FnInitCarbon func(configPath string, errBuf *byte, errBufSize int32) uintptr

	// FnFreeCarbon maps to free_carbon. Always call this when done with a handle.
	FnFreeCarbon func(handle uintptr)

	// FnCarbonFsWrite maps to carbon_fs_write. Returns 0 on success, non-zero on error.
	FnCarbonFsWrite func(handle uintptr, filename string, delay uint64, errBuf *byte, errBufSize int32) int32

	// FnCarbonFsTrunc maps to carbon_fs_trunc. Returns 0 on success, non-zero on error.
	FnCarbonFsTrunc func(handle uintptr, filename string, delay uint64, errBuf *byte, errBufSize int32) int32

	// FnCarbonFsRoot maps to carbon_fs_root. Returns 0 on success, non-zero on error.
	// The root path is written into outBuf.
	FnCarbonFsRoot func(handle uintptr, outBuf *byte, outLen int32) int32
)
