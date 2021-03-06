# Autostart section
#barM&
#while true; do
#	sh .xsetroot.sh
#	sleep 1m
#done &
/home/user/.local/src/dwm-bar/dwm_bar.sh &
picom --vsync --backend glx &
feh --bg-scale ~/Pictures/pang-yuhao.jpg
exec dwm
