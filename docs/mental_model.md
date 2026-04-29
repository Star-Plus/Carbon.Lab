# Carbon Mental Design

## Problems to solve

### File system setup

#### Description

The need to always create a samples of files and modifying it mid test. Then cleaning up after. Also naming tests and saving them.

#### Solution

- A predefined function that names a root folder with the name of the test suite + name of test case + date of execution `testsuite/testcase/datenow/UUID/`
- With a `config.c14` configuration file users can

  - create a root fs for the test `carbon = Carbon.init("config.c14")`
  - use the root directory of the created environment `rootPath = carbon.fs.root()`
  - write/delete any file at any step (regarding the files that checked to be auto written on setup) `carbon.fs.write("file_name in the config file")`

### Unavailable/Affected services

#### Description

If a piece of code relies or uses an external unmanagable service, this service should be on and configured on the exact state the test case assumes it's on. Even though if the previous problem is solved, the side effects on that service for just a piece of code can be expensive or confusing to rollback.

#### Solution

- Vritual Gateway

  - If the user has a Web Api, IPC call, etc. He can just spin up a temporary web server to forward requests on the entered url to a virtual local service that returns fixed responses that the user provides.
- For app integrations (Like databases), User can provide a docker image of the app, then Carbon would spin up a Docker container, run setup scripts (if provided) finally run the termination script and optionally tears it up or keep it if wanted.

### Environment Variables

#### Description

Missing environment variables or use different values depending on the test case

#### Solution

- Easy. Configure your variables at the config file or choose a .env file to load.
- Carbon will attach variables only to the test process not global os.
