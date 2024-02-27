#include <vulkan/vulkan.h>
#include <stdlib.h>

enum app_result {
	APP_SUCCESS = 0,
	APP_FAILURE = 1,
};

struct vulkan_error {
	VkResult vk_result;
	const char* file;
	uint32_t line;
};

struct result_create_vulkan_instance {
	enum app_result result;
	union {
		VkInstance vk_instance;
		struct vulkan_error error;
	};
};


struct result_create_vulkan_instance create_vulkan_instance() {
	// todo: optional layers? debug/release layers?
	const char* required_layers[] = {
		"VK_LAYER_KHRONOS_validation",
	};
	const char* required_extensions[] = {
		"VK_KHR_win32_surface",		// required to draw to a window on Win32
		"VK_KHR_surface",			// required by VK_KHR_win32_surface
	};
	const VkInstanceCreateInfo vulkan_create_info = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.pApplicationInfo = NULL,
		.enabledLayerCount = sizeof(required_layers) / sizeof(*required_layers),
		.ppEnabledLayerNames = &required_layers,
		.enabledExtensionCount = sizeof(required_extensions) / sizeof(*required_extensions),
		.ppEnabledExtensionNames = required_extensions,
	};

	VkInstance vk_instance;
	const VkResult vk_result = vkCreateInstance(&vulkan_create_info, NULL, &vk_instance);

	if(vk_result != VK_SUCCESS) {
		const struct result_create_vulkan_instance failure = {
			.result = APP_FAILURE,
			.error = {
				.vk_result = vk_result,
				.file = __FILE__,
				.line = __LINE__,
			},
		};
		return failure;
	}
	const struct result_create_vulkan_instance success = {
		.result = APP_SUCCESS,
		.vk_instance = vk_instance,
	};
	return success;
}

struct result_layer_properties {
	enum app_result result;
	uint32_t num_properties;
	VkLayerProperties *properties;
};

struct result_layer_properties query_instance_layer_properties() {
	const struct result_layer_properties failure = { APP_FAILURE };
	uint32_t num_properties;
	const VkResult vk_num_result = vkEnumerateInstanceLayerProperties(&num_properties, NULL);
	if(vk_num_result != VK_SUCCESS) {
		return failure;
	}
	VkLayerProperties *properties = malloc(num_properties * sizeof(VkLayerProperties));
	if(properties == NULL) {
		return failure;
	}
	const VkResult vk_properties_result = vkEnumerateInstanceLayerProperties(&num_properties, properties);
	if(vk_properties_result != VK_SUCCESS) {
		return failure;
	}
	const struct result_layer_properties success = {
		.result = APP_SUCCESS,
		.num_properties = num_properties,
		.properties = properties
	};
	return success;
}

struct result_query_extensions {
	enum app_result result;
	uint32_t num_extensions;
	VkExtensionProperties* extensions;
};

struct result_query_extensions query_instance_extensions(const char* layer_name) {
	const struct result_query_extensions failure = { APP_FAILURE };
	uint32_t num_extensions;
	const VkResult vk_num_result = vkEnumerateInstanceExtensionProperties(layer_name, &num_extensions, NULL);
	if(vk_num_result != VK_SUCCESS) {
		return failure;
	}
	VkExtensionProperties *extensions = malloc(num_extensions * sizeof(VkExtensionProperties));
	if(extensions == NULL) {
		return failure;
	}
	const VkResult vk_enumerate_result = vkEnumerateInstanceExtensionProperties(layer_name, &num_extensions, extensions);
	if(vk_enumerate_result != VK_SUCCESS) {
		return failure;
	}
	struct result_query_extensions success = {
		.result = APP_SUCCESS,
		.num_extensions = num_extensions,
		.extensions = extensions,
	};
	return success;
}


/*

// eventually I'll need a surface to draw to
// see https://registry.khronos.org/vulkan/specs/1.3-extensions/html/chap34.html#platformCreateSurface_win32
// and https://registry.khronos.org/vulkan/specs/1.3-extensions/html/chap34.html#VkWin32SurfaceCreateInfoKHR
// this is where the HWND and HINSTANCE meet Vulkan



*/