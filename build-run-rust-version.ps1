# RUSTFLAGS could also be set in .cargo/config.toml, but $env:VULKAN_SDK needs to be explicit there:
# .cargo/config.toml:
# [build]
# rustflags = ["-Clink-arg=C:/VulkanSDK/1.3.275.0/Lib/vulkan-1.lib"]

$env:RUSTFLAGS = "-Clink-arg=$env:VULKAN_SDK/Lib/vulkan-1.lib"
cargo clean
cargo run