#ifndef CPR_WRITEHANDLER_H
#define CPR_WRITEHANDLER_H

#include <functional>

namespace cpr {

class WriteHandler {
	public:
		std::function<size_t(void*,size_t,size_t,void*)> userCallback;
		void* userData = nullptr;

		WriteHandler() = default;
		WriteHandler(const WriteHandler& rhs) = default;
		WriteHandler(WriteHandler&& rhs) = default;
		WriteHandler& operator=(const WriteHandler& rhs) = default;
		WriteHandler& operator=(WriteHandler&& rhs) = default;

		WriteHandler(const std::function<size_t(void*,size_t,size_t,void*)>& callback, void* userdata = nullptr) : userCallback(callback), userData(userdata) {}
		WriteHandler(std::function<size_t(void*,size_t,size_t,void*)>&& callback, void* userdata = nullptr) : userCallback(std::move(callback)), userData(userdata) {}

		static size_t writeFunction(void* ptr, size_t size, size_t nmemb, void* data) {
			WriteHandler* self = static_cast<WriteHandler*>(data);
			return self->userCallback(ptr, size, nmemb, self->userData);
		}
};


} // namespace cpr

#endif
