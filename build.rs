use std::env;
use std::path::Path;

fn main() {
    let vulkan_sdk = env::var_os("VULKAN_SDK").unwrap();
    let vulkan_lib_path = String::from(Path::new(&vulkan_sdk).join("Lib").to_str().unwrap());
    println!("cargo:rerun-if-env-changed=VULKAN_SDK");
    println!("cargo:rustc-link-search={}", vulkan_lib_path);
    println!("cargo:rustc-link-lib=vulkan-1");
}