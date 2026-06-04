//go:build linux

package loader

import (
	"fmt"

	"github.com/ebitengine/purego"
	symbols "github.com/starpg/carbon/mod"
)

func loadSymbols(path string) error {
	handle, err := purego.Dlopen(path, purego.RTLD_NOW|purego.RTLD_GLOBAL)
	if err != nil {
		return fmt.Errorf("dlopen failed for %q: %w", path, err)
	}

	purego.RegisterLibFunc(&symbols.FnInitCarbon, handle, "init_carbon")
	purego.RegisterLibFunc(&symbols.FnFreeCarbon, handle, "free_carbon")
	purego.RegisterLibFunc(&symbols.FnCarbonFsWrite, handle, "carbon_fs_write")
	purego.RegisterLibFunc(&symbols.FnCarbonFsTrunc, handle, "carbon_fs_trunc")
	purego.RegisterLibFunc(&symbols.FnCarbonFsRoot, handle, "carbon_fs_root")

	return nil
}
