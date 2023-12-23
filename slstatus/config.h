/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 3000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "-";

/* maximum output string length */
#define MAXLEN 2048

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * cpu_perc            cpu usage in percent            NULL
 * cpu_freq            cpu frequency in MHz            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/")
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * gid                 GID of current user             NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?)
 *                                                     see keyboard_indicators.c
 * keymap              layout (variant) of current     NULL
 *                     keymap
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * swap_free           free swap in GB                 NULL
 * swap_perc           swap usage in percent           NULL
 * swap_total          total swap size in GB           NULL
 * swap_used           used swap in GB                 NULL
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 * uid                 UID of current user             NULL
 * uptime              system uptime                   NULL
 * username            username of current user        NULL
 * vol_perc            OSS/ALSA volume in percent      mixer file (/dev/mixer)
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 */
static const struct arg args[] = {
	/* function format          argument */
	//Sensors
	{ temp,		 	" [TMP:%sc°]", "/sys/class/thermal/thermal_zone1/temp"						   		},
	{ cpu_perc, 	"«[CPU:%s%%]", NULL	       													   		},
	{ ram_perc,	    "«[RAM:%s%%]", NULL	       													   		},
	{ run_command,  "«[SND:%s]",   "amixer sget Master,0 | grep -Eo '[0-9]*%'" 		   		},
	{ battery_perc, "«[BAT:%s%%]", "BAT1",   	    											   		},
	//Network
	{ run_command,  "«[%s|",  	   "ip a | grep -Eo 'w[a-z0-9]*$' || ip a | grep -Eo 'e[a-z0-9]*[0-9]$'"},
	{ wifi_essid, 	"%s",  	  	   "wlan0"    														    },
	{ run_command,  "›%sms]", 	   "ping -c 1 gnu.org | grep -Eo 'e=.*[0-9]' | grep -Eo '[0-9]*'" 		},
	//Time
	{ datetime, 	"«[%s]",  	   "%I:%M" 		 													    },

	//{ datetime, "%s",           "%F %T" },
	//{ wifi_perc, "W: (%3s%% on ", "wlp8s0" },
    //{ netspeed_rx, "%sB/s  ", "enp0s3" },
	//{ temp,		 " [:%sc°]", "/sys/class/thermal/thermal_zone1/temp"},
	//{ cpu_perc, "«[:%s%%]", NULL	        },
	//{ ram_perc, "«[:%s%%]", NULL	        },
	//{ run_command, "«[:%s]",  "amixer sget Master,0 | awk -F\"[][]\" '/%/ { print $2 }' | head -n1" },
	//{ run_command, "«[:%s]", "amixer sget Master,0 | grep -Eo '[0-9][0-9][0-9]?%'" },
	//{ battery_perc, "«[:%s%%]", "BAT1",   	    },
	//{ run_command, "«[%s|", "ip a | grep -Eo 'w[a-z0-9]*$' || ip a | grep -Eo 'e[a-z0-9]*[0-9]$'" },
	//{ wifi_essid, "%s",  "wlan0" 	    },
	//{ run_command, "›%sms]", "ping -c 1 gnu.org | grep -oP 'time=\\K.*'[0-9]" },
	//{ datetime, "«[%s] ",          "%a/%d %I:%M"  },
};
