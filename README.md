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
The Portable Executable (PE) format is a file format for executables, object code, DLLs and others used in 32-bit and 64-bit versions of Windows operating systems.[2] The PE format is a data structure that encapsulates the information necessary for the Windows OS loader to manage the wrapped executable code. [Wikipedia](https://en.wikipedia.org/wiki/Portable_Executable)

We will get the start of the PE address using `GetModuleHandleA(NULL);`, this will be our imagebase. Then, we need to get to the IAT, in order to this we need to 
get the dosHeaders, ntHeaders, imageOptionalHeaders, imageDirEntryImport. We will get this using this image: http://www.openrce.org/reference_library/files/reference/PE%20Format.pdf.

After we have the address of the IAT, we will loop threw it (all the dll files that are imported by the process), and for each library, we loop
threw their imported functions and find out where CreateFileW is stored.

### 3. Replacing original function
We now have the address of the original CreateFileW function, this address needs to be saved outside (in a const var that will not be changed), because we
will have to call it after out hooked function will be called.

Our hooked function will be called: NewCreateFileW. Its return value and params will be EXACTLY the same as CreateFileW (we need to be exactly like the function
thet we are trying to hook).

Finally, after we have NewCreateFileW and CreateFileW addresses, we can replace the CreateFileW IAT address to our function!! We will to it by change the permission to write - `VirtualProtect`.

## Debugging
