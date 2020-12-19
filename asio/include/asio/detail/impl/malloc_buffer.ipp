#if !defined(ASIO_DETAIL_MALLOC_BUFFER)
#define ASIO_DETAIL_MALLOC_BUFFER

namespace asio {
    namespace detail {
        struct malloc_buffer {
            void* ptr;

            malloc_buffer(size_t size) : ptr(malloc(size)) {}

            ~malloc_buffer() {
                free(ptr);
            }

            template<typename T>
            operator T*() {
                return (T*) ptr;
            }

            bool operator==(nullptr_t) const {
                return ptr == nullptr;
            }
        };
    }
}

#endif // ASIO_DETAIL_MALLOC_BUFFER
