# Hook Function With Dllinjection

The example will be with Notepad, we will hook the function CreateFile, so everytime the user saves a file, you can change its name.

## How is this working?
In order to hook function within a proccess you need to be "inside" of it, be in the same chunck of memory. In oder to do it we will
inject a dll using Dllinjection, understand where is the import for CreateFile (usually in kernel32) and change its pointer to our function.
### 1. Dllinjection
We will do it in the usual way:<br />
* GetProcAddress - used to load a DLL into the process memory. [MSDN](https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getprocaddress)
* VirtualAllocEx - used to allocate space from the target process virtual memory. [MSDN](https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualallocex)
* WriteProcessMemory - used to write the path of the DLL file into the allocated memory. [MSDN](https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-writeprocessmemory)
* CreateRemoteThread - used to creates a thread in the virtual memory area of a process. [MSDN](https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createremotethread)
 
Thanks to [ZeroMemoryEx](https://github.com/ZeroMemoryEx/Dll-Injector) for the explanation.
### 2. PE parser

### 3. Replacing original function


## Debugging
