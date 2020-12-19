#if !defined(ASIO_DETAIL_WRITEV_HPP)
#define ASIO_DETAIL_WRITEV_HPP

#include "asio/detail/config.hpp"
#include <sys/socket.h>

asio::detail::signed_size_type writev(int fd, const struct iovec* iov, int count);

#if defined(ASIO_HEADER_ONLY)
# include "asio/detail/impl/writev.ipp"
#endif // defined(ASIO_HEADER_ONLY)

#endif // ASIO_DETAIL_WRITEV_HPP
