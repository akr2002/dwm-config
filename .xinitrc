# Statusbar loop
#while true; do
#	xsetroot -name "$( date +"%F %R" )"
#	sleep 1m	# Update time every minute
#done &
#dwmstatus 2>&1 >/dev/null
# Autostart section
while true; do
	sh .xsetroot.sh
	sleep 1m
done &
picom --vsync --backend glx &
feh --bg-scale ~/Pictures/pang-yuhao.jpg
exec dwm
#barM 2>&1 >/dv/null
