# Test Report -

## 1. Executive Summary

| Field                    | Value                                          |
| ------------------------ | ---------------------------------------------- |
| **Suite**          | `{suite.name}` v `{suite.version}`         |
| **Environment**    | `{env.name}` (`{env.os}` / `{env.arch}`) |
| **Started**        | `{run.started_at}` (UTC)                     |
| **Finished**       | `{run.finished_at}` (UTC)                    |
| **Duration**       | `{run.duration_ms}` ms                       |
| **Overall Result** | `{run.status}` ✅ / ❌ / ⚠️                |

---

## 2. Result Snapshot

```
Total     {stats.total}
Passed    {stats.passed}       ({stats.pass_rate}%)
Failed    {stats.failed}
Skipped   {stats.skipped}
Duration  {run.duration_ms} ms
```

---

## 3. Test Suites Breakdown

| Suite / Module      | Total         | ✅ Pass        | ❌ Fail        | ⚠️ Skip       | Duration             |
| ------------------- | ------------- | -------------- | -------------- | --------------- | -------------------- |
| `{suite[0].name}` | …            | …             | …             | …              | … ms                |
| `{suite[1].name}` | …            | …             | …             | …              | … ms                |
| `{suite[N].name}` | …            | …             | …             | …              | … ms                |
| **Total**     | {stats.total} | {stats.passed} | {stats.failed} | {stats.skipped} | {run.duration_ms} ms |

---

## 4. Failed Tests

> This section is **omitted** if `{stats.failed} == 0`.

### 4.1 Failure Summary

| # | Test Name               | Suite / Module      | Error Type               | Duration |
| - | ----------------------- | ------------------- | ------------------------ | -------- |
| 1 | `{fail[0].test_name}` | `{fail[0].suite}` | `{fail[0].error_type}` | … ms    |
| 2 | `{fail[1].test_name}` | `{fail[1].suite}` | `{fail[1].error_type}` | … ms    |

---

#### ❌ `{fail[0].test_name}`

- **Suite:** `{fail[0].suite}`
- **File:** `{fail[0].file_path}:{fail[0].line}`
- **Duration:** `{fail[0].duration_ms}` ms
- **Retries:** `{fail[0].retry_count}`
- **Error Message:**

```
{fail[0].error_message}
```

**Stack Trace:**

```
{fail[0].stack_trace}
```

**Expected vs. Actual:**

```diff
- Expected: {fail[0].expected}
+ Actual:   {fail[0].actual}
```

**Logs / Captured Output:**

```
{fail[0].stdout}
```

> _Repeat block for each failure._

---

## 5. Skipped Tests

> This section is **omitted** if `{stats.skipped} == 0`.

| Test Name               | Suite               | Reason               |
| ----------------------- | ------------------- | -------------------- |
| `{skip[0].test_name}` | `{skip[0].suite}` | `{skip[0].reason}` |

---

## 6. Performance Benchmarks

> Included only when benchmark tests are part of the suite (`{benchmarks.enabled}`).

| Benchmark Name      | Baseline                | Current                | Delta                | Status  |
| ------------------- | ----------------------- | ---------------------- | -------------------- | ------- |
| `{bench[0].name}` | `{bench[0].baseline}` | `{bench[0].current}` | `{bench[0].delta}` | ✅ / ❌ |

---

## 7. Environment & Dependencies

### Runtime

| Property        | Value                                       |
| --------------- | ------------------------------------------- |
| OS              | `{env.os}` `{env.os_version}`           |
| Architecture    | `{env.arch}`                              |
| Runtime / SDK   | `{env.runtime}` `{env.runtime_version}` |
| CI Runner       | `{env.ci_runner}`                         |
| Container Image | `{env.docker_image}`                      |

---

### Key Dependency Versions

| Package / Library | Version              |
| ----------------- | -------------------- |
| `{dep[0].name}` | `{dep[0].version}` |
| `{dep[1].name}` | `{dep[1].version}` |

---

## 8. Artifact Links

| Artifact             | Link / Path                   |
| -------------------- | ----------------------------- |
| Full Log             | `{artifacts.full_log_path}` |
| Coverage HTML Report | `{artifacts.coverage_html}` |
| JUnit XML            | `{artifacts.junit_xml}`     |
| Screenshots / Videos | `{artifacts.media_dir}`     |
| Profiling Data       | `{artifacts.profile_path}`  |

---
