//go:build windows

package loader

import (
	"fmt"
	"syscall"

	"github.com/ebitengine/purego"

	symbols "github.com/starpg/carbon/mod"
)

func loadSymbols(path string) error {
	// syscall.NewLazyDLL does LoadLibrary under the hood.
	// We still use purego.RegisterLibFunc for consistent symbol binding across platforms.
	dll, err := syscall.LoadDLL(path)
	if err != nil {
		return fmt.Errorf("LoadLibrary failed for %q: %w", path, err)
	}

	handle := uintptr(dll.Handle)

	purego.RegisterLibFunc(&symbols.FnInitCarbon, handle, "init_carbon")
	purego.RegisterLibFunc(&symbols.FnFreeCarbon, handle, "free_carbon")
	purego.RegisterLibFunc(&symbols.FnCarbonFsWrite, handle, "carbon_fs_write")
	purego.RegisterLibFunc(&symbols.FnCarbonFsTrunc, handle, "carbon_fs_trunc")
	purego.RegisterLibFunc(&symbols.FnCarbonFsRoot, handle, "carbon_fs_root")

	return nil
}
