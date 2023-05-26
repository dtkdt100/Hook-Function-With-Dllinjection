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

#### How do we know that its CreateFileW and not CreateFileA?
Open Notepad.exe with IDA, got to imports (all of the imported functions). Search for CreateFile and check what version they are using

### 3. Replacing original function
We now have the address of the original CreateFileW function, this address needs to be saved outside (in a const var that will not be changed), because we
will have to call it after out hooked function will be called.

Our hooked function will be called: NewCreateFileW. Its return value and params will be EXACTLY the same as CreateFileW (we need to be exactly like the function
thet we are trying to hook).

Finally, after we have NewCreateFileW and CreateFileW addresses, we can replace the CreateFileW IAT address to our function!! We will to it by change the permission to write - `VirtualProtect`.

## Run the code
1. Clone the project using `git clone`
2. Open the folder in VisualStudio
3. Build the dll file (should create a dll file)
4. Edit the dll file location in `Main.cpp` to your own dll (step 3)
5. Open notepad.exe
6. Run main!

## Debugging
How will I know that it really was hooked? Maybe I want to hook another function?

Few tools that you need:
* IDA - investigate the exe that its functions will be hooked
* [WinDbg preview](https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/debugger-download-tools) - should be default on a Windows computer, will be used to most of the debugging
* [PE-bear](https://github.com/hasherezade/pe-bear/releases/) - visually parse the PE of the exe

Useful code snaps:
* (CPP) __debugbreak() - break point (int 3h). Use it in the dllFIle code

### Debug code (viewing local varibles and more) with WinDbg
1. Open notepad (or any other process, I will use notepad as an example)
2. Open WinDbg, F6, choose Notepad.exe
3. Edit the dll file code and put the `__debugbreak()` function where ever you want the debugger to stop
4. Build dll, and run the code
5. Go to WinDbg and you will see that the running has stopped, tap F5 to continue

### Get IAT table address
1. Open notepad (or any other process, I will use notepad as an example)
2. Open WinDbg, F6, choose Notepad.exe
3. We need now to put a break point on the original CreateFileW, in order to do it we will write in WinDbg: `bp KERNEL32!CreateFileW`
4. Continue (even though there are breaks on the KERNEL32!CreateFileW, ignore them for now because those are without good stack, I mean without a stack that we can understand fully)
5. Write something and save the file. After the bp has been called, type `k` (shows the stack). Should be something like this: ![image](https://github.com/dtkdt100/Hook-Function-With-Dllinjection/assets/63166757/54dd0742-2257-4d8d-acfe-6db7d5bbbec6)
6. Notice the `Notepad+0x1c547`. Put a bp on this (`bp Notepad+0x1c547`)
7. Save the file again (save as or whatever)
8. When the break point is called, chack out what address has been called, this the IAT adrress1!![image](https://github.com/dtkdt100/Hook-Function-With-Dllinjection/assets/63166757/ef4b4a63-e930-48fc-8fb6-926dc8aa4846)
9. `dq 7FF6E26B2460h` in order to see the addresses there, the first will be the one for CreateFileW, the address that we are changing. You can put a bp before the hook and after and watched the address change in live

