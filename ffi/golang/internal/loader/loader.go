package loader

import (
	"fmt"
	"io"
	"net/http"
	"os"
	"path/filepath"
	"runtime"
	"strings"
	"sync"
)

const Version = "v1.1.2"

const githubRepo = "Star-Plus/Carbon.Lab"

var once sync.Once

func EnsureLoaded() error {
	var loadErr error
	once.Do(func() {
		path, err := ensureNative()
		if err != nil {
			loadErr = fmt.Errorf("carbon: failed to prepare native binary: %w", err)
			return
		}
		if err := loadSymbols(path); err != nil {
			loadErr = fmt.Errorf("carbon: failed to load symbols: %w", err)
		}
	})
	return loadErr
}

func ensureNative() (string, error) {
	filename, err := platformFilename()
	if err != nil {
		return "", err
	}

	// Cache location: e.g. ~/.cache/carbon-go/v1.0.0/libCarbon.so
	cacheDir, err := os.UserCacheDir()
	if err != nil {
		return "", fmt.Errorf("could not determine user cache dir: %w", err)
	}
	outDir := filepath.Join(cacheDir, "carbon", Version)
	outPath := filepath.Join(outDir, filename)

	// Already cached — nothing to do.
	if _, err := os.Stat(outPath); err == nil {
		return outPath, nil
	}

	if err := os.MkdirAll(outDir, 0755); err != nil {
		return "", fmt.Errorf("could not create cache dir: %w", err)
	}

	if err := download(outPath, filename); err != nil {
		os.Remove(outPath)
		return "", err
	}

	return outPath, nil
}

func download(outPath, filename string) error {
	url := fmt.Sprintf(
		"https://github.com/%s/releases/download/%s/%s",
		githubRepo, Version, filename,
	)

	fmt.Fprintf(os.Stderr, "carbon: downloading native binary %s %s\n", filename, Version)

	resp, err := http.Get(url)
	if err != nil {
		return fmt.Errorf("download failed for %q: %w", url, err)
	}
	defer resp.Body.Close()

	if resp.StatusCode != http.StatusOK {
		return fmt.Errorf("download failed for %q: HTTP %d", url, resp.StatusCode)
	}

	f, err := os.OpenFile(outPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0755)
	if err != nil {
		return fmt.Errorf("could not create output file %q: %w", outPath, err)
	}
	defer f.Close()

	pr := &progressReader{
		r:     resp.Body,
		total: resp.ContentLength,
	}

	if _, err := io.Copy(f, pr); err != nil {
		return fmt.Errorf("could not write binary to disk: %w", err)
	}

	// Print a final newline to move past the progress bar line.
	fmt.Fprintln(os.Stderr)

	return nil
}

type progressReader struct {
	r          io.Reader
	total      int64 // -1 if unknown
	downloaded int64
	barWidth   int
}

func (p *progressReader) Read(buf []byte) (int, error) {
	if p.barWidth == 0 {
		p.barWidth = 40
	}

	n, err := p.r.Read(buf)
	p.downloaded += int64(n)

	if p.total > 0 {
		p.printBar()
	} else {
		fmt.Fprintf(os.Stderr, "\r  downloading... %s", formatBytes(p.downloaded))
	}

	return n, err
}

func (p *progressReader) printBar() {
	percent := float64(p.downloaded) / float64(p.total)
	filled := int(percent * float64(p.barWidth))
	if filled > p.barWidth {
		filled = p.barWidth
	}

	bar := strings.Repeat("█", filled) + strings.Repeat("░", p.barWidth-filled)

	fmt.Fprintf(os.Stderr, "\r  [%s] %3.0f%%  %s / %s",
		bar,
		percent*100,
		formatBytes(p.downloaded),
		formatBytes(p.total),
	)
}

func formatBytes(b int64) string {
	switch {
	case b >= 1024*1024:
		return fmt.Sprintf("%.1f MB", float64(b)/1024/1024)
	case b >= 1024:
		return fmt.Sprintf("%.1f KB", float64(b)/1024)
	default:
		return fmt.Sprintf("%d B", b)
	}
}

func platformFilename() (string, error) {
	switch runtime.GOOS {
	case "linux":
		return "libCarbon_linux_amd64.so", nil
	case "windows":
		return "Carbon_windows_amd64.dll", nil
	default:
		return "", fmt.Errorf("unsupported platform: %s/%s", runtime.GOOS, runtime.GOARCH)
	}
}
