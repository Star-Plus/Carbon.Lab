package carbon

import (
	"errors"
	"fmt"

	"github.com/Star-Plus/Carbon.Lab/ffi/golang/internal/loader"
	symbols "github.com/Star-Plus/Carbon.Lab/ffi/golang/mod"
)

const errBufSize = 512

// Carbon is the main handle to a loaded Carbon environment.
// Always call Close() when done — it frees the underlying C++ object.
type Carbon struct {
	handle uintptr
}

// Fs is a sub-object backed by the same Carbon handle, exposing filesystem operations.
type Fs struct {
	handle uintptr
}

// Init loads the Carbon environment from a .c14 config file.
// This also triggers the native library to be extracted and loaded on first call.
func Init(configPath string) (*Carbon, error) {
	if err := loader.EnsureLoaded(); err != nil {
		return nil, err
	}

	var errBuf [errBufSize]byte
	handle := symbols.FnInitCarbon(configPath, &errBuf[0], errBufSize)
	if handle == 0 {
		return nil, fmt.Errorf("carbon: init failed: %s", cStr(errBuf[:]))
	}

	return &Carbon{handle: handle}, nil
}

// Close frees the underlying C++ Carbon object. Always defer this after Init.
func (c *Carbon) Close() {
	if c.handle != 0 {
		symbols.FnFreeCarbon(c.handle)
		c.handle = 0
	}
}

// Fs returns the filesystem sub-object for this Carbon instance.
func (c *Carbon) Fs() *Fs {
	return &Fs{handle: c.handle}
}

// Write stages a file write in the virtual filesystem.
// delay is in milliseconds (0 means immediate).
func (f *Fs) Write(filename string, delay uint64) error {
	var errBuf [errBufSize]byte
	rc := symbols.FnCarbonFsWrite(f.handle, filename, delay, &errBuf[0], errBufSize)
	if rc != 0 {
		return fmt.Errorf("carbon: fs.Write failed: %s", cStr(errBuf[:]))
	}
	return nil
}

// Trunc truncates a file in the virtual filesystem.
// delay is in milliseconds (0 means immediate).
func (f *Fs) Trunc(filename string, delay uint64) error {
	var errBuf [errBufSize]byte
	rc := symbols.FnCarbonFsTrunc(f.handle, filename, delay, &errBuf[0], errBufSize)
	if rc != 0 {
		return fmt.Errorf("carbon: fs.Trunc failed: %s", cStr(errBuf[:]))
	}
	return nil
}

// Root returns the virtual root path of the filesystem.
func (f *Fs) Root() (string, error) {
	var outBuf [1024]byte
	rc := symbols.FnCarbonFsRoot(f.handle, &outBuf[0], int32(len(outBuf)))
	if rc != 0 {
		return "", errors.New("carbon: fs.Root failed")
	}
	return cStr(outBuf[:]), nil
}

// cStr converts a null-terminated byte slice from C into a Go string.
func cStr(b []byte) string {
	for i, c := range b {
		if c == 0 {
			return string(b[:i])
		}
	}
	return string(b)
}
