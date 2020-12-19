#if !defined(ASIO_DETAIL_IMPL_READV_IPP)
#define ASIO_DETAIL_IMPL_READV_IPP

#include "asio/detail/config.hpp"
#include "asio/detail/impl/malloc_buffer.ipp"
#include <sys/socket.h>
#include <limits>
#include <cerrno>
#include <algorithm>

using asio::detail::signed_size_type;

signed_size_type readv(int fd, const struct iovec* iov, int count) {
    /* Find the total number of bytes to be read.  */
    size_t bytes = 0;
    for (int i = 0; i < count; ++i) {
        /* Check for ssize_t overflow.  */
        if (std::numeric_limits<signed_size_type>::max() - bytes < iov[i].iov_len) {
            *__errno() = EINVAL;
            return -1;
        }
        bytes += iov[i].iov_len;
    }
    /* Allocate a temporary buffer to hold the data.  We should normally
       use alloca since it's faster and does not require synchronization
       with other threads.  But we cannot if the amount of memory
       required is too large.  */
    asio::detail::malloc_buffer buffer{bytes};
    if (buffer == nullptr)
        return -1;

    /* Read the data.  */
    ssize_t bytes_read = read(fd, buffer, bytes);
    if (bytes_read < 0)
        return -1;
    /* Copy the data from BUFFER into the memory specified by VECTOR.  */
    char* b = buffer;
    bytes = bytes_read;
    for (int i = 0; i < count; ++i) {
        size_t copy = std::min(iov[i].iov_len, bytes);
        (void) memcpy((void*) iov[i].iov_base, (void*) b, copy);
        b += copy;
        bytes -= copy;
        if (bytes == 0)
            break;
    }
    return bytes_read;
}

#endif
