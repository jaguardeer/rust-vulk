Enter-VsDevShell -VsInstanceId 6db2c180 -Arch amd64 -SkipAutomaticLocation
cl -I $env:VULKAN_SDK/Include .\enum-vulk.c /link $env:VULKAN_SDK/lib/vulkan-1.lib
if ($?) {
    ./enum-vulk.exe
}