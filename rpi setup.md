# Raspberry Pi setup
1. Install Ubuntu 22.04.4
2. Set hostname to `rpi`: (`sudoedit /etc/hostname`)
3. Set up user accounts (`sudo adduser …`)
4. Set up Wi-Fi: Create a .yaml file in `/etc/netplan/` with the following content:

    ```yaml
    network:
        version: 2
        ethernets:
            eth0:
                dhcp4: true
                dhcp6: true
        wifis:
            renderer: networkd
            wlan0:
                access-points:
                    ROS2-AP-24GHz:
                        password: "V3rtA!-5C"
                dhcp4: true
    ```
5. Reboot if necessary for the Wi-Fi connection, or run `netplan apply` (according to <https://netplan.io>)
6. (Update the apt cache (`sudo apt update`))
7. Install `avahi-autoipd` (optional?) and `avahi-daemon` (`sudo apt install avahi-{daemon,autoipd}`)
8. Test if avahi/mDNS is working by pinging `rpi.local`
