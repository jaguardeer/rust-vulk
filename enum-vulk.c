#include <vulkan/vulkan.h>

#include <stdio.h>

int main() {
	uint32_t api_version;
	VkResult query_result = vkEnumerateInstanceVersion(&api_version);
	if(query_result == VK_SUCCESS) {
		uint32_t major = VK_API_VERSION_MAJOR (api_version);
		uint32_t minor = VK_VERSION_MINOR (api_version);
		uint32_t patch = VK_API_VERSION_PATCH (api_version);
		printf("Vulkan query succeeded. Version is %i.%i.%i\n", major, minor, patch);
	}
	else {
		printf("Failed to query Vulkan version.\n");
	}
	return 0;
}