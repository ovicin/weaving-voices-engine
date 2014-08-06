
+ NetAddr {
	*getBroadcastIp {
		^"ifconfig".unixCmdGetStdOut
		.findAllRegexp("broadcast [0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+")
		.first.first[1]
		.replace("broadcast ", "");
	}

	*getLocalIp {
		^"ifconfig".unixCmdGetStdOut
		.findAllRegexp("inet [0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+")	
		.first.detect({ | ip |
			ip[1] != "inet 127.0.0.1"
		})
		.at(1).replace("inet ", "")
	}
}
