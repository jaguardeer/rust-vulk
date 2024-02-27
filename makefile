run: test.exe
	test.exe

test.exe: test.c vulk.c
	cl /nologo -I $(VULKAN_SDK)/Include ./test.c /link $(VULKAN_SDK)/lib/vulkan-1.lib /nologo