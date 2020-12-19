#if !defined(ASIO_DETAIL_IMPL_WRITEV_IPP)
#define ASIO_DETAIL_IMPL_WRITEV_IPP

#include "asio/detail/config.hpp"
#include "asio/detail/impl/malloc_buffer.ipp"
#include <sys/socket.h>
#include <algorithm>
#include <limits>

using asio::detail::signed_size_type;

signed_size_type writev(int fd, const struct iovec* iov, int count) {
    /* Find the total number of bytes to be written.  */
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

    /* Copy the data into BUFFER.  */
    size_t to_copy = bytes;
    char* bp = buffer;
    for (int i = 0; i < count; ++i) {
        size_t copy = std::min(iov[i].iov_len, to_copy);
        bp = (char*) memcpy((void*) bp, (void*) iov[i].iov_base, copy);
        to_copy -= copy;
        if (to_copy == 0)
            break;
    }
    ssize_t bytes_written = write(fd, buffer, bytes);
    return bytes_written;
}

#endif
