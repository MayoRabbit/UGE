
#include <vulkan/vulkan.hpp>
#include "main.hpp"

namespace vulkanLib
{

VkInstance instance;

} // namespace vulkanLib

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Initializes Vulkan library and resources.
 */

uint8_t libInit(SDL_Window *window)
{
	VkApplicationInfo appInfo
	{
		VK_STRUCTURE_TYPE_APPLICATION_INFO,
		NULL,
		"Hello World",
		VK_MAKE_VERSION(0, 0, 1),
		"Unnamed Engine",
		VK_MAKE_VERSION(0, 0, 1),
		VK_API_VERSION_1_2
	};

    VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	VkResult result = vkCreateInstance(&createInfo, nullptr, &vulkanLib::instance);

	if(!result)
		return 0;
}

/**
 * Destroys Vulkan resources.
 */

void libQuit()
{
	vkDestroyInstance(vulkanLib::instance, NULL);
}

#ifdef __cplusplus
}
#endif
