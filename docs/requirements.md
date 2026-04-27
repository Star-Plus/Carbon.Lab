## What was the problem that inspired me?

Testing splitvcs is tedious, setting up an environment, generating files manually, and cleaning up environment and databases. And making test units independent makes those steps repeated.

## First intuition of Carbon

Carbon can be created to help testers for this kind of test where code is not natively independent and essentially uses external sources for data fetching, writing, or deletion.

### Features I intend to develop

#### 1. Test unit naming

#### 2. Files setup

- Auto file creation

  - Random content creation: Input(savePath, filetype, size in smallest unit of the file data (characters, pixels, etc))
  - User content creation: Input(savePath, filetype, user-written content)
  - User file upload: Input(savePath, filepath)
- Auto modification

  - Same as creation but modifies files if exists at any step of the code.

#### 3. Environment auto-load

- Writing environment variable manually
- Load a .env file

#### 4. Dummy database instances.

- Choose the supported database u need. (Returns a link or a context of the instance)
- Filling database upfront

#### 5. Cleanup

- Optionally, u can keep or remove the testing side effects (test folder, environment, stores).

#### 6. Fixtures/Presents

- Testing profiles that can be used for many test units.

#### 6. CLI

#### 7. SDKs (C++, Go, .NET, etc)
