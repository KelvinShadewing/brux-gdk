. /etc/os-release
case $ID in
  manjaro|garuda|endeavouros|arco|arcolinux)
    echo "Let's get started!"
    sudo pacman -Sy yay
    ;;
  *)
if [[ ! -f /usr/bin/yay ]]
then
  echo "You are using Arch and there's no yay in this repository."
fi
      ;;
esac
if [[ ! -f /usr/bin/yay ]]
then
echo "Chaotic AUR installation guide is available at 'https://aur.chaotic.cx/'"
elif [[ -f /usr/bin/yay ]]
then
    echo "Installing build dependencies for AGAME (Arch/Garuda/ArcoLinux/Manjaro/EndeavourOS)..."
    sudo pacman -Sy sdl2 sdl2_image sdl2_mixer sdl2_net sdl2_gfx physfs
    echo "Let's build a Squirrel!"
    yay -S squirrel
fi