#include "EventHub.h"

std::unordered_map<std::string, std::vector<std::function<void(const std::vector<void*>&)>>> EventHub::listeners;