{
    files = {
        [[src\Resource\UploadBuffer.cpp]]
    },
    values = {
        [[C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\Llvm\x64\bin\clang-cl.exe]],
        {
            "-w",
            "-O2",
            "-fp:fast",
            "-std:c++20",
            "-MD",
            "-Isrc",
            "-D_XM_NO_INTRINSICS_=1",
            "-DNOMINMAX",
            "-DUNICODE",
            "-Dm128_f32=vector4_f32",
            "-Dm128_u32=vector4_u32",
            "/EHsc",
            "/Oy",
            "/GS-",
            "/Gd",
            "/Oi",
            "/Ot",
            "/GT",
            "/Ob2",
            "-DNDEBUG"
        }
    },
    depfiles_cl = "Note: including file: src\\Resource/UploadBuffer.h\
Note: including file:  src\\Resource/Buffer.h\
Note: including file:   src\\Resource/Resource.h\
Note: including file:    src\\stdafx.h\
Note: including file:     C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\windows.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\winapifamily.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\winpackagefamily.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\sdkddkver.h\
Note: including file:      C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\excpt.h\
Note: including file:       C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\vcruntime.h\
Note: including file:        C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\sal.h\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\concurrencysal.h\
Note: including file:        C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\vadefs.h\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\vadefs.h\
Note: including file:      C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\stdarg.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\windef.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\minwindef.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\specstrings.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\specstrings_strict.h\
Note: including file:          C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\specstrings_undef.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\driverspecs.h\
Note: including file:          C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared/sdv_driverspecs.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\winnt.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\ctype.h\
Note: including file:          C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\corecrt.h\
Note: including file:          C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\corecrt_wctype.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\kernelspecs.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\basetsd.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\guiddef.h\
Note: including file:          C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\string.h\
Note: including file:           C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\corecrt_memory.h\
Note: including file:            C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\corecrt_memcpy_s.h\
Note: including file:             C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\errno.h\
Note: including file:             C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\vcruntime_string.h\
Note: including file:           C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\corecrt_wstring.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared/pshpack4.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared/poppack.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack4.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack4.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared/pshpack2.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared/pshpack2.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack2.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared/pshpack8.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared/pshpack1.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared/pshpack1.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\apiset.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\ktmtypes.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\winbase.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\apisetcconv.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\minwinbase.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\apiquery2.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\processenv.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\fileapifromapp.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\fileapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\debugapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\utilapiset.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\handleapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\errhandlingapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\fibersapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\namedpipeapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\profileapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\heapapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\ioapiset.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\synchapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\interlockedapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\processthreadsapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\sysinfoapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\memoryapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\enclaveapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\threadpoollegacyapiset.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\threadpoolapiset.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\jobapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\jobapi2.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\wow64apiset.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\libloaderapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\securitybaseapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\namespaceapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\systemtopologyapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\processtopologyapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\securityappcontainer.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\realtimeapiset.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\winerror.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\timezoneapi.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\wingdi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack1.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack2.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack2.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack4.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack4.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\winuser.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack2.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\tvout.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\winnls.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\datetimeapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\stringapiset.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\winnls.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\wincon.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\wincontypes.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\consoleapi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\consoleapi2.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\consoleapi3.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\winver.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\verrsrc.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\winreg.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\reason.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\winnetwk.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\wnnc.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\stralign.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\winsvc.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\mcx.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\imm.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\ime_cmodes.h\
Note: including file:     C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\stdint.h\
Note: including file:      C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\stdint.h\
Note: including file:     C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\d3d12.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\rpc.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack8.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\rpcdce.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\rpcdcep.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\rpcnsi.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\rpcnterr.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\rpcasync.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack8.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\rpcndr.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack8.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\rpcnsip.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\rpcsal.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um/ole2.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack8.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\objbase.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack8.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\combaseapi.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack8.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\stdlib.h\
Note: including file:          C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\corecrt_malloc.h\
Note: including file:          C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\corecrt_search.h\
Note: including file:           C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\stddef.h\
Note: including file:            C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include/__stddef_max_align_t.h\
Note: including file:          C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\corecrt_wstdlib.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\limits.h\
Note: including file:           C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\limits.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\wtypesbase.h\
Note: including file:          C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared/guiddef.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\unknwnbase.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\objidlbase.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared/guiddef.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\cguid.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\coml2api.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\objidl.h\
Note: including file:          C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um/unknwn.h\
Note: including file:           C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\wtypes.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\propidlbase.h\
Note: including file:          C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um/oaidl.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\urlmon.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um/oleidl.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um/servprov.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um/msxml.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\propidl.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\oleauto.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack8.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um/OCIdl.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\dxgicommon.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\dxgiformat.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um/d3dcommon.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um/d3d12sdklayers.h\
Note: including file:     C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\dxgi.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared/dxgitype.h\
Note: including file:     C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\dxgi1_6.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared/dxgi1_5.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared/dxgi1_4.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared/dxgi1_3.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared/dxgi1_2.h\
Note: including file:     C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\D3Dcompiler.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um/d3d11shader.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um/d3d12shader.h\
Note: including file:     C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\DirectXMath.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\math.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\corecrt_math.h\
Note: including file:      C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\float.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\float.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\assert.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um/DirectXMathConvert.inl\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um/DirectXMathVector.inl\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um/DirectXMathMatrix.inl\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um/DirectXMathMisc.inl\
Note: including file:     src/d3dx12.h\
Note: including file:      C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\list\
Note: including file:       C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\yvals_core.h\
Note: including file:        C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\xkeycheck.h\
Note: including file:       C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\xmemory\
Note: including file:        C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\cstdint\
Note: including file:        C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\cstdlib\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\math.h\
Note: including file:        C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\limits\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\cfloat\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\climits\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\cwchar\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\cstdio\
Note: including file:           C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\stdio.h\
Note: including file:            C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\corecrt_wstdio.h\
Note: including file:             C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\corecrt_stdio_config.h\
Note: including file:          C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\wchar.h\
Note: including file:           C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\corecrt_wconio.h\
Note: including file:           C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\corecrt_wdirect.h\
Note: including file:           C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\corecrt_wio.h\
Note: including file:            C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\corecrt_share.h\
Note: including file:           C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\corecrt_wprocess.h\
Note: including file:           C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\corecrt_wtime.h\
Note: including file:           C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\sys/stat.h\
Note: including file:            C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\sys/types.h\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\intrin0.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\intrin0.inl.h\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\isa_availability.h\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\xstddef\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\cstddef\
Note: including file:           C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\stddef.h\
Note: including file:           C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\xtr1common\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\initializer_list\
Note: including file:        C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\new\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\exception\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\yvals.h\
Note: including file:           C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\crtdbg.h\
Note: including file:            C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\vcruntime_new_debug.h\
Note: including file:             C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\vcruntime_new.h\
Note: including file:           C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\crtdefs.h\
Note: including file:           C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\use_ansi.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\type_traits\
Note: including file:          C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\malloc.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\vcruntime_exception.h\
Note: including file:           C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\eh.h\
Note: including file:            C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\vadefs.h\
Note: including file:            C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\corecrt_terminate.h\
Note: including file:        C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\xatomic.h\
Note: including file:        C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\xutility\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\__msvc_iter_core.hpp\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\utility\
Note: including file:           C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\concepts\
Note: including file:           C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\compare\
Note: including file:            C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\bit\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\cstring\
Note: including file:        C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\tuple\
Note: including file:       C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\xpolymorphic_allocator.h\
Note: including file:      C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\vector\
Note: including file:      C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\string\
Note: including file:       C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\xstring\
Note: including file:        C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\iosfwd\
Note: including file:       C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\cctype\
Note: including file:      C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\memory\
Note: including file:       C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\typeinfo\
Note: including file:        C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\vcruntime_typeinfo.h\
Note: including file:       C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\atomic\
Note: including file:        C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\xatomic_wait.h\
Note: including file:        C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\xthreads.h\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\xtimec.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\ctime\
Note: including file:           C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\time.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\winrt\\wrl/client.h\
Note: including file:       C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\stddef.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\winrt\\weakreference.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\winrt/inspectable.h\
Note: including file:         C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\winrt/hstring.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\winrt\\roapi.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\winrt\\activation.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\winrt\\wrl\\def.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\winrt\\wrl\\internal.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack8.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:     C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\winrt\\wrl.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\winrt\\wrl\\implements.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\winrt\\WinString.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\include\\10.0.22000.0\\ucrt\\new.h\
Note: including file:        C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\crtdefs.h\
Note: including file:       C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\intrin.h\
Note: including file:        C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\x86intrin.h\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\ia32intrin.h\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\immintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\x86gprintrin.h\
Note: including file:           C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\hresetintrin.h\
Note: including file:           C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\uintrintrin.h\
Note: including file:           C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\crc32intrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\mmintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\xmmintrin.h\
Note: including file:           C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\mm_malloc.h\
Note: including file:           C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\emmintrin.h\
Note: including file:            C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\xmmintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\pmmintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\tmmintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\smmintrin.h\
Note: including file:           C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\popcntintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\wmmintrin.h\
Note: including file:           C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\__wmmintrin_aes.h\
Note: including file:           C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\__wmmintrin_pclmul.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\clflushoptintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\clwbintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avxintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx2intrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\f16cintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\bmiintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\bmi2intrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\lzcntintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\fmaintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512fintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512vlintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512bwintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512bitalgintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512cdintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512vpopcntdqintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512vpopcntdqvlintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512vnniintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512vlvnniintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avxvnniintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512dqintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512vlbitalgintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512vlbwintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512vlcdintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512vldqintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512erintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512ifmaintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512ifmavlintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512vbmiintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512vbmivlintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512vbmi2intrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512vlvbmi2intrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512pfintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512bf16intrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512vlbf16intrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\pkuintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\vpclmulqdqintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\vaesintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\gfniintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\rtmintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\xtestintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\shaintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\fxsrintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\xsaveintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\xsaveoptintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\xsavecintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\xsavesintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\cetintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\adxintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\rdseedintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\wbnoinvdintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\cldemoteintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\waitpkgintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\movdirintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\pconfigintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\sgxintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\ptwriteintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\invpcidintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\keylockerintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\amxintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512vp2intersectintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\avx512vlvp2intersectintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\enqcmdintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\serializeintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\tsxldtrkintrin.h\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\mm3dnow.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\prfchwintrin.h\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\prfchwintrin.h\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\ammintrin.h\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\fma4intrin.h\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\xopintrin.h\
Note: including file:          C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\fma4intrin.h\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\tbmintrin.h\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\lwpintrin.h\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\mwaitxintrin.h\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\clzerointrin.h\
Note: including file:         C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\rdpruintrin.h\
Note: including file:        C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\setjmp.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\winrt/roerrorapi.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\restrictedErrorInfo.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack8.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\winrt\\wrl\\module.h\
Note: including file:       C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\lib\\clang\\15.0.1\\include\\intrin.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\winrt\\wrl\\ftm.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\winrt\\wrl\\wrappers\\corewrappers.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\intsafe.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack8.h\
Note: including file:        C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack8.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:      C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\winrt\\wrl\\event.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\winrt\\eventtoken.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\pshpack8.h\
Note: including file:       C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\shared\\poppack.h\
Note: including file:     C:\\Program Files (x86)\\Windows Kits\\10\\\\include\\10.0.22000.0\\\\um\\shellapi.h\
Note: including file:     src\\Metalib.h\
Note: including file:     C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\span\
Note: including file:     C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\array\
Note: including file:    src\\DXRuntime/Device.h\
Note: including file:   src\\Resource/BufferView.h\
Note: including file: src\\DXSampleHelper.h\
Note: including file:  C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\stdexcept\
Note: including file: src\\DXRuntime/FrameResource.h\
Note: including file:  src\\DXRuntime/CommandListHandle.h\
Note: including file:  src\\Resource/ReadBackBuffer.h\
Note: including file:  src\\Resource/DefaultBuffer.h\
Note: including file:  src\\Utility/StackAllocator.h\
Note: including file:  C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\functional\
Note: including file:   C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\unordered_map\
Note: including file:    C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\xhash\
Note: including file:     C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\cmath\
Note: including file:     C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\xbit_ops.h\
Note: including file:     C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\xnode_handle.h\
Note: including file:  src\\Resource/DescriptorHeapView.h\
Note: including file:  src\\DXRuntime/BindProperty.h\
Note: including file:   C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\variant\
Note: including file:    C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\include\\xsmf_control.h\
"
}