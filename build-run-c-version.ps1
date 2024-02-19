$vs_id = C:"\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -property instanceId
Enter-VsDevShell -VsInstanceId $vs_id -Arch amd64 -SkipAutomaticLocation
cl -I $env:VULKAN_SDK/Include .\enum-vulk.c /link $env:VULKAN_SDK/lib/vulkan-1.lib
if ($?) {
    ./enum-vulk.exe
}