#!/bin/sh
# Install DOSBox-X without root, for CI runners that have no sudo. It lets apt
# download DOSBox-X and the libraries it needs, unpacks them under
# ~/.local/dosbox-x, and writes a launcher to ~/.local/bin/dosbox-x. Only
# Ubuntu 24.04 and Debian 13 or newer package DOSBox-X. Safe to run again.
set -eu
prefix=${DOSBOX_X_PREFIX:-$HOME/.local}
root=$prefix/dosbox-x
if command -v dosbox-x >/dev/null 2>&1 || [ -x "$prefix/bin/dosbox-x" ]; then
    exit 0
fi
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
mkdir -p "$work/state/lists/partial" "$work/cache/archives/partial" "$root" "$prefix/bin"
apt="apt-get -o Dir::State=$work/state -o Dir::Cache=$work/cache -o Dir::State::status=/var/lib/dpkg/status"
$apt update -qq
# The packages apt would install here, minus the C library, which must stay
# the one the runner already has.
if ! plan=$($apt -s install dosbox-x 2>&1); then
    echo "install_dosbox_x: apt can't install dosbox-x on this system (needs Ubuntu 24.04 or Debian 13 or newer)" >&2
    exit 1
fi
pkgs=$(echo "$plan" | sed -n 's/^Inst \([^ ]*\) .*/\1/p' | grep -v -E '^(libc6|libc-bin|locales)$')
cd "$work"
$apt download $pkgs
for deb in ./*.deb; do
    dpkg-deb -x "$deb" "$root"
done
libs=
for d in $(find "$root" \( -type f -o -type l \) -name '*.so*' -exec dirname {} \; | sort -u); do
    libs="$libs:$d"
done
cat > "$prefix/bin/dosbox-x" <<EOF
#!/bin/sh
LD_LIBRARY_PATH="${libs#:}\${LD_LIBRARY_PATH:+:\$LD_LIBRARY_PATH}" exec "$root/usr/bin/dosbox-x" "\$@"
EOF
chmod +x "$prefix/bin/dosbox-x"
