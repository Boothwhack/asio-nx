pkgname=switch-asio
pkgver=1.18.0
pkgrel=1
pkgdesc="Switch port of ASIO"
arch=("any")
makedepends=("devkitpro-pkgbuild-helpers")

package() {
    source /opt/devkitpro/switchvars.sh

    install -d "$pkgdir"$PORTLIBS_PREFIX/include
    cp $startdir/asio/include/asio.hpp "$pkgdir"$PORTLIBS_PREFIX/include
    cp -r $startdir/asio/include/asio "$pkgdir"$PORTLIBS_PREFIX/include
}
