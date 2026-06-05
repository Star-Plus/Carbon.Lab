package carbon

import (
	"errors"
	"fmt"

	"github.com/Star-Plus/Carbon.Lab/ffi/golang/internal/loader"
	symbols "github.com/Star-Plus/Carbon.Lab/ffi/golang/mod"
)

const errBufSize = 512

type Carbon struct {
	handle uintptr
}

type Fs struct {
	handle uintptr
}

type Apps struct {
	handle uintptr
}

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

func (c *Carbon) Close() {
	if c.handle != 0 {
		symbols.FnFreeCarbon(c.handle)
		c.handle = 0
	}
}

func (c *Carbon) Fs() *Fs {
	return &Fs{handle: c.handle}
}

func (c *Carbon) Apps() *Apps {
	return &Apps{handle: c.handle}
}

func (f *Fs) Write(filename string, delay uint64) error {
	var errBuf [errBufSize]byte
	rc := symbols.FnCarbonFsWrite(f.handle, filename, delay, &errBuf[0], errBufSize)
	if rc != 0 {
		return fmt.Errorf("carbon: fs.Write failed: %s", cStr(errBuf[:]))
	}
	return nil
}

func (f *Fs) Trunc(filename string, delay uint64) error {
	var errBuf [errBufSize]byte
	rc := symbols.FnCarbonFsTrunc(f.handle, filename, delay, &errBuf[0], errBufSize)
	if rc != 0 {
		return fmt.Errorf("carbon: fs.Trunc failed: %s", cStr(errBuf[:]))
	}
	return nil
}

func (f *Fs) Root() (string, error) {
	var outBuf [1024]byte
	rc := symbols.FnCarbonFsRoot(f.handle, &outBuf[0], int32(len(outBuf)))
	if rc != 0 {
		return "", errors.New("carbon: fs.Root failed")
	}
	return cStr(outBuf[:]), nil
}

func cStr(b []byte) string {
	for i, c := range b {
		if c == 0 {
			return string(b[:i])
		}
	}
	return string(b)
}

func (a *Apps) Connect(appName string) (string, error) {
	var errBuf [errBufSize]byte
	var outBuf [1024]byte
	rc := symbols.FnCarbonAppConnect(a.handle, appName, &outBuf[0], int32(len(outBuf)), &errBuf[0], errBufSize)
	if rc != 0 {
		return "", fmt.Errorf("carbon: apps.Connect failed: %s", cStr(errBuf[:]))
	}
	return cStr(outBuf[:]), nil
}
