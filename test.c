#include "vulk.c"

#include <stdio.h>

enum test_result {
	TEST_SUCCESS = 0,
	TEST_FAILURE = 1,
};

enum test_result test_enumerate_instance_version(void) {
	uint32_t api_version;
	VkResult query_result = vkEnumerateInstanceVersion(&api_version);
	if(query_result == VK_SUCCESS) {
		uint32_t major = VK_API_VERSION_MAJOR (api_version);
		uint32_t minor = VK_VERSION_MINOR (api_version);
		uint32_t patch = VK_API_VERSION_PATCH (api_version);
		printf("Vulkan query succeeded. Version is %i.%i.%i\n", major, minor, patch);
		return TEST_SUCCESS;
	}
	else {
		printf("Failed to query Vulkan version.\n");
		return TEST_FAILURE;
	}
}

enum test_result test_create_vulkan_instance(void) {
	printf("Testing create_vulkan_instance: ");
	struct result_create_vulkan_instance result = create_vulkan_instance();
	if(result.result == APP_SUCCESS) {
		printf("succeeded\n");
	}
	else {
		printf("failed\n");
	}
	return result.result;
}

enum test_result test_query_instance_layer_properties(void) {
	struct result_layer_properties result = query_instance_layer_properties();
	if(result.result == APP_SUCCESS) {
		for(uint32_t i = 0 ; i < result.num_properties ; i++) {
			printf("%i: %s\n", i, result.properties[i].layerName);
			printf("%s\n", result.properties[i].description);
		}
		return TEST_SUCCESS;
	}
	else {
		printf("Failed to query Vulkan layer properties");
		return TEST_FAILURE;
	}
}

enum test_result test_query_instance_extensions(void) {
	struct result_query_extensions result = query_instance_extensions(NULL);
	if(result.result == APP_SUCCESS) {
		for(uint32_t i = 0 ; i < result.num_extensions ; i++) {
			printf("%i: %s\n", i, result.extensions[i].extensionName);
		}
		return TEST_SUCCESS;
	}
	else {
		printf("Failed to query Vulkan layer properties");
		return TEST_FAILURE;
	}
}

enum test_result test_vulkan_error(void) {
	return TEST_FAILURE;
}

enum test_result print_vulkan_info(void) {
	struct result_layer_properties result = query_instance_layer_properties();
	if(result.result == APP_SUCCESS) {
		for(uint32_t i = 0 ; i < result.num_properties ; i++) {
			const char *layer_name = result.properties[i].layerName;
			printf("%i: %s\n", i, layer_name);
			printf("%s\n", result.properties[i].description);
			struct result_query_extensions extensions = query_instance_extensions(layer_name);
			if(extensions.result == APP_SUCCESS) {
				for(uint32_t j = 0 ; j < extensions.num_extensions ; j++) {
					printf("\t\t%s\n", extensions.extensions[j].extensionName);
				}
			}
			else {
				printf("\t\tUnable to query extensions");
			}
		}
		return TEST_SUCCESS;
	}
	else {
		printf("Failed to query Vulkan layer properties");
		return TEST_FAILURE;
	}	
}

int main() {
	test_enumerate_instance_version();
	test_create_vulkan_instance();
	return 0;
	test_query_instance_layer_properties();
	test_query_instance_extensions();
	print_vulkan_info();
	return 0;
}