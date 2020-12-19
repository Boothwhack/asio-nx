#if !defined(ASIO_DETAIL_READV_HPP)
#define ASIO_DETAIL_READV_HPP

#include "asio/detail/config.hpp"
#include <sys/socket.h>

asio::detail::signed_size_type readv(int fd, const struct iovec* iov, int count);

#if defined(ASIO_HEADER_ONLY)
# include "asio/detail/impl/readv.ipp"
#endif // defined(ASIO_HEADER_ONLY)

#endif // ASIO_DETAIL_READV_HPP
